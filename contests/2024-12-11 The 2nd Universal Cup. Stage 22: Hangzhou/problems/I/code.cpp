#pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;
#define LS(x) (x+m-1)%m
#define RS(x) (x+1)%m
const int N=1e5+5,M=6,mod=1e9+7;

int rd(){
	char c=getchar();
	int tot=0;
	while(!isdigit(c)) c=getchar();
	while(isdigit(c)) tot=(tot<<1)+(tot<<3)+(c^'0'),c=getchar();
	return tot;
}
void gmod(int &x){
	x+=x>>31 & mod;
}

int ksm(int a,int x){
	int tot=1;
	while(x){
		if(x & 1) tot=1ll*tot*a%mod;
		a=1ll*a*a%mod;
		x>>=1;
	}
	return tot;
}

bool gauss(int a[M*2][M*2],int b[M*2],int n){
	for(int k=1;k<=n;k++){
		int st=0;
		for(int i=k;i<=n;i++){
			if(a[i][k]){
				st=i;
				break;
			}
		}
		if(!st) assert(0);
		if(st!=k){
			for(int j=1;j<=n;j++) swap(a[k][j],a[st][j]);
			swap(b[k],b[st]);
		}
		for(int i=k+1;i<=n;i++){
			int w=1ll*a[i][k]*ksm(a[k][k],mod-2)%mod;
			for(int j=1;j<=n;j++) gmod(a[i][j]-=1ll*a[k][j]*w%mod);
			gmod(b[i]-=1ll*b[k]*w%mod);
		}
	}
	
	for(int k=n;k>=1;k--){
		b[k]=1ll*b[k]*ksm(a[k][k],mod-2)%mod;
		for(int i=1;i<k;i++) gmod(b[i]-=1ll*a[i][k]*b[k]%mod);
	}
	return 1;
}

int n,m,q;
int L[N][M],R[N][M],U[N][M],D[N][M];
int A[M*2][M*2],B[M*2],id;

struct mat{
	int B[M*2][M*2];
	mat(int x=0){
		memset(B,0,sizeof(B));
		for(int i=0;i<=m*2;i++) B[i][i]=x;
	}
};
mat operator +(mat X,mat Y){
	for(int i=0;i<=m*2;i++)
		for(int j=0;j<=m*2;j++)
			gmod(X.B[i][j]+=Y.B[i][j]-mod);
	return X;
}
mat operator *(mat X,mat Y){
	mat T(0);
	for(int j=0;j<m;j++)
		for(int i=0;i<m;i++){
			if(!X.B[i][j]) continue;
			for(int k=0;k<=m*2;k++)
				gmod(T.B[i][k]+=1ll*X.B[i][j]*Y.B[j][k]%mod-mod);
		}
	
	for(int j=0;j<m;j++)
		for(int k=0;k<m;k++){
			if(!Y.B[j][k]) continue;
			for(int i=m;i<=m*2;i++)
				gmod(T.B[i][k]+=1ll*X.B[i][j]*Y.B[j][k]%mod-mod);
		}
	
	for(int j=0;j<m;j++)
		for(int i=m;i<=m*2;i++)
			for(int k=m;k<=m*2;k++)
				gmod(T.B[i][k]+=1ll*X.B[i][j]*Y.B[j][k]%mod-mod);
	for(int j=m;j<=m*2;j++)
		for(int i=0;i<=m*2;i++)
			for(int k=0;k<=m*2;k++)
				gmod(T.B[i][k]+=1ll*X.B[i][j]*Y.B[j][k]%mod-mod);
	return T;
}

mat P[N],Q[N],F[N*4],G[N*4];
void pushup(int o){
	int ls=o<<1,rs=o<<1|1;
	F[o]=F[rs]*F[ls];
	G[o]=G[rs]*G[ls];
}
void build(int l,int r,int o){
	if(l==r){
		F[o]=P[l],G[o]=Q[l];
		return ;
	}
	int mid=(l+r)>>1;
	build(l,mid,o<<1);
	build(mid+1,r,o<<1|1);
	pushup(o);
}
void modify(int l,int r,int o,int k){
	if(l==r){
		F[o]=P[l],G[o]=Q[l];
		return ;
	}
	int mid=(l+r)>>1;
	if(k<=mid) modify(l,mid,o<<1,k);
	else modify(mid+1,r,o<<1|1,k);
	pushup(o);
}
mat queryf(int l,int r,int o,int L,int R){
	if(L>R) return mat(1);
	if(L<=l && r<=R) return F[o];
	int mid=(l+r)>>1;
	if(L<=mid && R>mid) return queryf(mid+1,r,o<<1|1,L,R)*queryf(l,mid,o<<1,L,R);
	else if(L<=mid) return queryf(l,mid,o<<1,L,R);
	else return queryf(mid+1,r,o<<1|1,L,R);
}
mat queryg(int l,int r,int o,int L,int R){
	if(L>R) return mat(1);
	if(L<=l && r<=R) return G[o];
	int mid=(l+r)>>1;
	if(L<=mid && R>mid) return queryg(mid+1,r,o<<1|1,L,R)*queryg(l,mid,o<<1,L,R);
	else if(L<=mid) return queryg(l,mid,o<<1,L,R);
	else return queryg(mid+1,r,o<<1|1,L,R);
}

void upd(int i){
	if(i<2 || i>n-1) return ;
	for(int j=0;j<m;j++) P[i].B[j][j+m]=1;
	P[i].B[m*2][m*2]=1;
	
	for(int j=0;j<m;j++){
		int invd=ksm(D[i-1][j],mod-2);
		P[i].B[j+m][j]=mod-1ll*U[i-1][j]*invd%mod;
		P[i].B[j+m][j+m]=invd;
		P[i].B[j+m][LS(j)+m]=mod-1ll*L[i-1][j]*invd%mod;
		P[i].B[j+m][RS(j)+m]=mod-1ll*R[i-1][j]*invd%mod;
	}
	
	memcpy(&Q[i],&P[i],sizeof(P[i]));
	for(int j=0;j<m;j++){
		int invd=ksm(D[i-1][j],mod-2);
		Q[i].B[j+m][m*2]=mod-invd;
	}
}

void pass(int f[2][M][M*2],int g[2][M][M*2],mat& F,mat& G,int ct){
	for(int i=0;i<m;i++){
		for(int j=0;j<m;j++){
			for(int t=1;t<=ct;t++){
				gmod(g[0][i][t]+=(1ll*f[0][j][t]*F.B[i][j]%mod+1ll*f[1][j][t]*F.B[i][j+m]%mod)%mod-mod);
				gmod(g[1][i][t]+=(1ll*f[0][j][t]*F.B[i+m][j]%mod+1ll*f[1][j][t]*F.B[i+m][j+m]%mod)%mod-mod);
			}
			gmod(g[0][i][0]+=(1ll*f[0][j][0]*G.B[i][j]%mod+1ll*f[1][j][0]*G.B[i][j+m]%mod)%mod-mod);
			gmod(g[1][i][0]+=(1ll*f[0][j][0]*G.B[i+m][j]%mod+1ll*f[1][j][0]*G.B[i+m][j+m]%mod)%mod-mod);
		}
		gmod(g[0][i][0]+=G.B[i][2*m]-mod);
		gmod(g[1][i][0]+=G.B[i+m][2*m]-mod);
	}
}
int f[2][M][M*2]; // (0,1)
int g[2][M][M*2]; // (tx,tx+1)
int h[2][M][M*2]; // (n-2,n-1)
int s[2][M][M*2]; // (sx-1,sx)
//0: constant; 1~2m: row 1/2; 2m+1: (tx+1,ty)

signed main(){
	int inv100=ksm(100,mod-2);
	n=rd(),m=rd();
	
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			L[i][j]=1ll*rd()*inv100%mod;
		
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			R[i][j]=1ll*rd()*inv100%mod;
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			U[i][j]=1ll*rd()*inv100%mod;
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			D[i][j]=1ll*rd()*inv100%mod;
	
	for(int i=2;i<n;i++) upd(i);
	build(2,n-1,1);
	
	q=rd();
	while(q--){
		int opt=rd();
		if(opt==1){
			int x=rd(),y=rd();
			L[x][y]=1ll*rd()*inv100%mod;
			R[x][y]=1ll*rd()*inv100%mod;
			U[x][y]=1ll*rd()*inv100%mod;
			D[x][y]=1ll*rd()*inv100%mod;
			upd(x+1);
			modify(2,n-1,1,x+1);
		}
		else{
			int sx=rd(),sy=rd(),tx=rd(),ty=rd();
			for(int i=0;i<2;i++)
				for(int j=0;j<m;j++)
					for(int t=0;t<=m*2+1;t++)
						f[i][j][t]=g[i][j][t]=h[i][j][t]=s[i][j][t]=0;
			int ct=2*m;
			for(int j=0;j<m;j++){
				f[0][j][j+1]=f[1][j][j+1+m]=1;
			}
			
			if(tx==n-1){
				mat LF=queryf(2,n-1,1,2,n-1),LG=queryg(2,n-1,1,2,n-1);
				pass(f,h,LF,LG,ct);
				memcpy(g[0],h[1],sizeof(h[1]));
			}
			else{
				mat LF=queryf(2,n-1,1,2,tx+1),LG=queryg(2,n-1,1,2,tx+1);
				mat RF=queryf(2,n-1,1,tx+2,n-1),RG=queryg(2,n-1,1,tx+2,n-1);
				
				pass(f,g,LF,LG,ct);
				if(tx!=0){
					for(int t=0;t<=ct;t++) g[1][ty][t]=0;
					g[1][ty][++ct]=1;
				}
				pass(g,h,RF,RG,ct);
			}
			
			id=0;
			
			id++;
			for(int t=1;t<=ct;t++) A[id][t]=g[0][ty][t];
			B[id]=mod-g[0][ty][0];
			
			for(int j=0;j<m;j++){
				if(tx==0 && ty==j) continue;
				id++;
				for(int t=1;t<=ct;t++){
					A[id][t]=1ll*(
						1ll*f[0][j][t]
						+mod-1ll*D[0][j]*f[1][j][t]%mod
						+mod-1ll*U[0][j]*h[1][j][t]%mod
						+mod-1ll*L[0][j]*f[0][LS(j)][t]%mod
						+mod-1ll*R[0][j]*f[0][RS(j)][t]%mod
					)%mod;
				}
				B[id]=1ll*(
						mod-1ll*f[0][j][0]
						+1ll*D[0][j]*f[1][j][0]%mod
						+1ll*U[0][j]*h[1][j][0]%mod
						+1ll*L[0][j]*f[0][LS(j)][0]%mod
						+1ll*R[0][j]*f[0][RS(j)][0]%mod
						+1
					)%mod;
			}
			
			for(int j=0;j<m;j++){
				if(tx==n-1 && ty==j) continue;
				id++;
				for(int t=1;t<=ct;t++){
					A[id][t]=1ll*(
						1ll*h[1][j][t]
						+mod-1ll*D[n-1][j]*f[0][j][t]%mod
						+mod-1ll*U[n-1][j]*h[0][j][t]%mod
						+mod-1ll*L[n-1][j]*h[1][LS(j)][t]%mod
						+mod-1ll*R[n-1][j]*h[1][RS(j)][t]%mod
					)%mod;
				}
				B[id]=1ll*(
						mod-1ll*h[1][j][0]
						+1ll*D[n-1][j]*f[0][j][0]%mod
						+1ll*U[n-1][j]*h[0][j][0]%mod
						+1ll*L[n-1][j]*h[1][LS(j)][0]%mod
						+1ll*R[n-1][j]*h[1][RS(j)][0]%mod
						+1
					)%mod;
			}
			
			// cout<<"equal? "<<id<<" "<<ct<<endl;
			gauss(A,B,id);
			
			if(!sx) memcpy(s[1],f[0],sizeof(f[0]));
			else if(sx<=tx){
				mat SF=queryf(2,n-1,1,2,sx),SG=queryg(2,n-1,1,2,sx);
				pass(f,s,SF,SG,ct);
			}
			else{
				mat SF=queryf(2,n-1,1,tx+2,sx),SG=queryg(2,n-1,1,tx+2,sx);
				pass(g,s,SF,SG,ct);
			}
			
			int ans=s[1][sy][0];
			for(int t=1;t<=ct;t++){
				gmod(ans+=1ll*s[1][sy][t]*B[t]%mod-mod);
			}
			printf("%d\n",ans);
		}
	}
}

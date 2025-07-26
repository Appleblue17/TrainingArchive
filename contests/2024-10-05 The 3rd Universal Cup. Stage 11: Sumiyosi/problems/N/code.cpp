// 写都写了，交一发吧！ 

#include <bits/stdc++.h>
using namespace std;
// #define int long long
const int N=7,M=5e5+5,mod=1e9+7;
int n,m;
int a[N][N],b[N][N];
int A[N*N][N*N],B[N*N],C[N*N];
int pw[M];

void gmod(int &x){
	if(x>=mod) x-=mod;
}

int ksm(int a,int x){
	int tot=1;
	while(x){
		if(x & 1ll) tot=1ll*tot*a%mod;
		a=1ll*a*a%mod;
		x>>=1ll;
	}
	return tot;
}

void gauss(int a[N*N][N*N],int b[],int c[],int n){
	for(int k=1;k<=n;k++){
		int st=0;
		for(int i=k;i<=n;i++){
			if(a[i][k]){
				st=i;
				break;
			}
		}
		if(!st) return ;
		
		if(st!=k){
			for(int j=1;j<=n;j++) swap(a[k][j],a[st][j]);
			swap(b[k],b[st]);
		}
		
		for(int i=k+1;i<=n;i++){
			int t=1ll*a[i][k]*ksm(a[k][k],mod-2)%mod;
			for(int j=k;j<=n;j++) gmod(a[i][j]+=mod-1ll*a[k][j]*t%mod);
			gmod(b[i]+=mod-1ll*b[k]*t%mod);
		}
	}
	
	for(int k=n;k>=1;k--){
		c[k]=1ll*b[k]*ksm(a[k][k],mod-2)%mod;
		for(int i=1;i<k;i++){
			gmod(b[i]+=mod-1ll*c[k]*a[i][k]%mod);
		}
	}
}

int ID(int x,int y){
	return (x-1)*n+y;
}

struct mat{
	int a[N][N];
	mat(int x=0){
		memset(a, 0, sizeof a);
		for(int i=1;i<=n;i++) a[i][i]=x;
	}
};
inline mat mul(mat x, mat y){
	mat ret;
	memset(ret.a, 0, sizeof ret.a);
	for(int i=0; i<=n; ++i){
		for(int j=0; j<=n; ++j){
			for(int k=0; k<=n; ++k){
				ret.a[i][j]=(1ll*x.a[i][k]*y.a[k][j]%mod+ret.a[i][j])%mod;
			}
		}
	}
	return ret;
}
mat cal(mat A,int x){
	mat T=mat(1ll);
	while(x){
		if(x & 1ll) T=mul(T,A);
		A=mul(A,A);
		x>>=1ll;
	}
	return T;
}


int f[M][N][N];

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			cin>>a[i][j];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			cin>>b[i][j];
	
	pw[0]=1;
	for(int i=1;i<=m;i++) pw[i]=pw[i-1]*2%mod;
	
	mat P;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			P.a[i][j]=b[i][j];
	mat Q=cal(P,m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			f[0][i][j]=Q.a[i][j];
	
//	cout<<endl;
//	for(int i=1;i<=n;i++){
//		for(int j=1;j<=n;j++){
//			cout<<f[0][i][j]<<" ";
//		}
//		cout<<endl;
//	}
//	cout<<endl;
	for(int t=1;t<=m;t++){
//		cout<<t<<": "<<endl;
		memset(A,0,sizeof(A));
		for(int i=1;i<=n;i++){
			for(int k=1;k<=n;k++){
				
				int tot=0;
				for(int j=1;j<=n;j++){
					gmod(A[ID(i,k)][ID(i,j)]+=b[j][k]);
					gmod(A[ID(i,k)][ID(j,k)]+=mod-1ll*b[i][j]*pw[t]%mod);
					
					gmod(tot+=1ll*pw[t-1]*a[i][j]%mod*f[t-1][j][k]%mod);
					gmod(tot+=mod-1ll*pw[m]*a[j][k]%mod*f[t-1][i][j]%mod);
				}
				B[ID(i,k)]=tot;
			}
		}
		
		gauss(A,B,C,n*n);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				f[t][i][j]=C[ID(i,j)];
		
		
//		for(int i=1;i<=n;i++){
//			for(int j=1;j<=n;j++){
//				cout<<f[t][i][j]<<" ";
//			}
//			cout<<endl;
//		}
//		cout<<endl;
	}
	
	for(int t=0;t<=m;t++) cout<<f[t][1][1]<<endl;
}

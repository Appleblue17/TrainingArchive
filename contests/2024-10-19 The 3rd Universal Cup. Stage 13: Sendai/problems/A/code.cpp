#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=6e5+5,mod=998244353;

void gmod(int &x){
	x%=mod;
}

int ksm(int a,int x){
	int tot=1;
	while(x){
		if(x & 1ll) tot=tot*a%mod;
		a=a*a%mod;
		x>>=1ll;
	}
	return tot;
}

int mul[N],inv[N];
void init(int lim){
	mul[0]=inv[0]=1;
	for(int i=1;i<=lim;i++) mul[i]=mul[i-1]*i%mod;
	inv[lim]=ksm(mul[lim],mod-2);
	for(int i=lim-1;i>=1;i--) inv[i]=inv[i+1]*(i+1)%mod;
	
}

int C(int m,int n){
	if(m<0 || n<0 || m<n) return 0;
	return mul[m]*inv[n]%mod*inv[m-n]%mod;
}

namespace NTT{
	int A[N],B[N],C[N];
	int rev[N],pre[N];
	int init(int n){
		int lim=0;
		while((1ll<<lim)<=n) lim++;
		for(int i=0;i<(1<<lim);i++)
			rev[i]=(rev[i>>1] >> 1) | ((i & 1)<<(lim-1));
		int omega=ksm(3,(mod-1)/(1<<lim));
		pre[0]=1;
		for(int i=1;i<=(1<<lim);i++)
			pre[i]=pre[i-1]*omega%mod;
		return lim;
	}
	void ntt(int *f,int n,int opt){
		for(int i=0;i<n;i++){
			if(i<rev[i]) swap(f[i],f[rev[i]]);
		}
		for(int l=1;l<n;l*=2){
			for(int i=0;i<n;i+=l*2){
				int u=n/l/2,nw=(opt==1)?0:n;
				for(int j=0;j<l;j++){
					int x=f[i+j],y=pre[nw]*f[i+j+l]%mod;
					gmod(f[i+j]=x+y),gmod(f[i+j+l]=x+mod-y);
					nw+=opt*u;
				}
			}
		}
		if(opt==-1){
			int t=ksm(n,mod-2);
			for(int i=0;i<n;i++) f[i]=f[i]*t%mod;
		}
	}
	void solve(int *s,int *f,int *g,int n,int m){
		int lim=init(n+m);
		for(int i=0;i<=n;i++) A[i]=f[i];
		for(int i=0;i<=m;i++) B[i]=g[i];
		for(int i=n+1;i<(1<<lim);i++) A[i]=0;
		for(int i=m+1;i<(1<<lim);i++) B[i]=0;
		ntt(A,1<<lim,1);
		ntt(B,1<<lim,1);
		for(int i=0;i<(1<<lim);i++) s[i]=A[i]*B[i]%mod;
		ntt(s,(1<<lim),-1);
	}
}

int n,m;
int F[N],G[N],H[N];
signed main(){
	init(N-5);
	cin>>n>>m;
	
	int s2=(C(n-1+m-1,n-1)*C(n-1+m-1,n-1)%mod+mod-C(n-2+m,n-2)*C(n+m-2,n)%mod)%mod;
//	cout<<s2<<endl;
	
	int s1=0;
	for(int i=1;i<n;i++){
		gmod(s1+=(C(n-i+m,n-i)*C(n-i-1+m-1,n-i-1)%mod+mod-C(n-i+m-1,n-i)*C(n-i-1+m,n-i-1)%mod)%mod);
	}
	swap(n,m);
	int s4=0;
	for(int i=1;i<n;i++){
		gmod(s4+=(C(n-i+m,n-i)*C(n-i-1+m-1,n-i-1)%mod+mod-C(n-i+m-1,n-i)*C(n-i-1+m,n-i-1)%mod)%mod);
	}
//	cout<<s1<<" "<<s4<<endl;
	
	int s5=0;
	for(int d=1;d<n;d++){
		int c=n-1-d;
		gmod(s5+=(C(d-1+m,m)*C(d-1+m,m)%mod+mod-C(d+m,m)*C(d-2+m,m)%mod)%mod*c%mod);
	}
	
	swap(n,m);
	int s7=0;
	for(int d=1;d<n;d++){
		int c=n-1-d;
		gmod(s7+=(C(d-1+m,m)*C(d-1+m,m)%mod+mod-C(d+m,m)*C(d-2+m,m)%mod)%mod*c%mod);
	}
	swap(n,m);
	
	
	int s3=0;
	memset(F,0,sizeof(F));
	memset(G,0,sizeof(G));
	for(int i=1;i<n;i++) F[i]=inv[i]*inv[i-1]%mod;
	for(int i=1;i<m;i++) G[i]=inv[i]*inv[i-1]%mod;
	NTT::solve(H,F,G,n-1,m-1);
	for(int i=2;i<=n+m-2;i++)
		gmod(s3+=H[i]*(mul[i]%mod*mul[i-2]%mod+mod-mul[i-1]%mod*mul[i-1]%mod));
	int s9=s3;
	
	int ans=s2;
	gmod(ans+=(s1+s4)%mod*2%mod);
	gmod(ans+=(s5+s7)%mod);
	gmod(ans+=(s3+s9)%mod);
	cout<<(ans+2)%mod;
}

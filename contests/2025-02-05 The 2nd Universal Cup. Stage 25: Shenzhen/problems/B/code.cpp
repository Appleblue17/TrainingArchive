#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=3e5+5,mod=998244353,inv2=(mod+1)/2;

int ksm(int a,int x){
    int tot=1;
    while(x){
        if(x & 1ll) tot=tot*a%mod;
        a=a*a%mod;
        x>>=1ll;
    }
    return tot;
}

void gmod(int &x) { x%=mod; }
namespace NTT{
    int A[N],B[N],C[N],rev[N];
    int init(int n){
		int lim=0;
		while((1<<lim)<=n) lim++;
		for(int i=0;i<=(1<<lim)-1;i++)
			rev[i]=(rev[i>>1]>>1) | ((i & 1)<<(lim-1));
		return lim;
	}
	void ntt(int *f,int n,int opt){
		for(int i=0;i<=n-1;i++)
			if(i<rev[i]) swap(f[i],f[rev[i]]);
		for(int l=1;l<n;l<<=1){
			int tmp=ksm(3,(mod-1)/(l*2));
			if(opt==-1) tmp=ksm(tmp,mod-2);
			for(int i=0;i<=n-1;i+=l<<1){
				int omegf=1;
				for(int j=0;j<l;j++){
					int x=f[i+j],y=omegf*f[i+j+l]%mod;
					f[i+j]=(x+y)%mod,f[i+j+l]=(x-y+mod)%mod;
					omegf=omegf*tmp%mod;
				}
			}
		}
		if(opt==-1){
			int t=ksm(n,mod-2);
			for(int i=0;i<n;i++)
				f[i]=f[i]*t%mod;
		}
	}
    void solve(int *s,int* f,int* g,int n,int m){
        if(n+m<=150){
            for(int i=0;i<=n+m;i++) C[i]=0;
            for(int i=0;i<=n;i++)
                for(int j=0;j<=m;j++)
                    gmod(C[i+j]+=f[i]*g[j]%mod);
            for(int i=0;i<=n+m;i++) s[i]=C[i];
            return ;
        }
        int lim=init(n+m);
        for(int i=0;i<(1<<lim);i++) A[i]=B[i]=0;
        for(int i=0;i<=n;i++) A[i]=f[i];
        for(int i=0;i<=m;i++) B[i]=g[i];
        ntt(A,(1<<lim),1);
        ntt(B,(1<<lim),1);
        for(int i=0;i<(1<<lim);i++) C[i]=A[i]*B[i]%mod;
        ntt(C,(1<<lim),-1);
        for(int i=0;i<=n+m;i++) s[i]=C[i];
    }
}

namespace INV{
	int A[N],B[N],S[N];
	void solve(int *s,int *f,int n){
		S[0]=ksm(f[0],mod-2);
		S[1]=0;
		for(int len=2;len/2<=n;len<<=1){
			int lim=len<<1;
			for(int i=0;i<len;i++) A[i]=f[i],B[i]=S[i];
			for(int i=len;i<lim;i++) A[i]=B[i]=0;
			NTT::init(lim-1);
			NTT::ntt(A,lim,1);
			NTT::ntt(B,lim,1);
			for(int j=0;j<lim;j++)
				S[j]=(2*B[j]%mod+mod-A[j]*B[j]%mod*B[j]%mod)%mod;
			NTT::ntt(S,lim,-1);
			for(int j=len;j<lim;j++) S[j]=0;
		}
		for(int i=0;i<=n;i++) s[i]=S[i];
	}
}

namespace LN{
	int A[N],B[N];
	void solve(int *s,int *f,int n){
		for(int i=0;i<=n;i++) A[i]=f[i],B[i]=0;
		for(int i=1;i<=n;i++) B[i-1]=f[i]*i%mod;

		INV::solve(A,A,n);
		NTT::solve(A,A,B,n,n);

		for(int i=n-1;i>=0;i--) A[i+1]=A[i]*ksm(i+1,mod-2)%mod;
		A[0]=0;

		for(int i=0;i<=n;i++) s[i]=A[i];
	}
}

namespace EXP{
	int A[N],B[N],C[N],S[N];
	void solve(int *s,int *f,int n){
		A[0]=B[0]=C[0]=0;
		S[0]=1;
		for(int len=2;len/2<=n;len<<=1){
			int lim=len<<1;
			for(int i=0;i<len;i++) A[i]=f[i],B[i]=S[i];
			
			LN::solve(C,B,len-1);
			for(int i=0;i<len;i++) C[i]=(mod-C[i]+A[i])%mod;
			C[0]=(C[0]+1)%mod;
			NTT::init(lim-1);
			NTT::ntt(B,lim,1);
			NTT::ntt(C,lim,1);
			for(int j=0;j<lim;j++) S[j]=B[j]*C[j]%mod;
			
			NTT::ntt(S,lim,-1);
			for(int j=len;j<lim;j++) S[j]=0;
		}
		for(int i=0;i<=n;i++) s[i]=S[i];
	}
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

int n;
int A[N],B[N],S[N];
int F[N],G[N],H[N],P[N],Q[N];


signed main(){
    init(N-5);
    
    cin>>n;
    
    for(int i=0;i<=n;i++) A[i]=inv[i+1];
    LN::solve(H,A,n);
    for(int i=1,x=inv2;i<=n;i++,x=x*inv2%mod){
        H[i]=H[i]*x%mod*ksm((1+mod-x)%mod,mod-2)%mod;
    }
    EXP::solve(G,H,n);
    
    // for(int i=0;i<=n;i++) cout<<G[i]<<" "; cout<<endl;
    
    INV::solve(F,G,n);
    for(int i=0;i<=n;i++) B[i]=inv[i]; // e^x
    NTT::solve(P,F,B,n,n);
    
    A[0]=0;
    for(int i=1;i<=n;i++) A[i]=ksm(inv2,i);
    for(int i=0;i<=n;i++) B[i]=P[i]*ksm(2,i*(i-1)/2)%mod;
    NTT::solve(Q,A,B,n,n);
    for(int i=0;i<=n;i++) Q[i]=Q[i]*ksm(inv2,i*(i-1)/2)%mod;
    
    NTT::solve(S,G,Q,n,n);
    cout<<S[n]*mul[n]%mod;
}

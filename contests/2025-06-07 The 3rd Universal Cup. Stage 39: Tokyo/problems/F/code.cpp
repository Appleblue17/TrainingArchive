#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=4.4e6+5,mod=998244353,inv2=(mod+1)/2;

int ksm(int a,int x){
    x%=mod-1;
    int tot=1;
    while(x){
        if(x & 1ll) tot=tot*a%mod;
        a=a*a%mod;
        x>>=1ll;
    }
    return tot;
}

void gmodn(int &x){ x+=x>>31 & mod; }
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
			for(int i=0;i<=n-1;i++)
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

int n,m;
int s[N];
int ID(int x){
    return (x & 1ll)?mod-1:1;
}
int S2(int x){
    return x*(x-1)/2;
}

int muliq[N],inviq[N];
int f[N],g[N],w[N],y[N];
int F[N],G[N],P[N],Q[N],R[N];

signed main(){
    cin>>n;
    n--;
    m=n*2;
    for(int i=0;i<=n;i++){
        int z=ksm(3,i);
        int val=(z+ksm(z,mod-2))%mod*inv2%mod;
        printf("%lld %lld\n",1,ksm(val,mod-2));
    }
    fflush(stdout);
                                                                                                                                                                                                                                           
    for(int k=0;k<=n;k++){
        int z=ksm(3,k);
        int x; scanf("%lld",&x);
        s[n+k]=x*ksm(3,n*(n+k))%mod;
        s[n-k]=x*ksm(3,n*(n-k))%mod;
    }
    // cout<<"s "; for(int i=0;i<=m;i++) cout<<s[i]<<" "; cout<<endl;
    
    int q=3;
    
    f[0]=1;
    for(int i=1;i<=m;i++) f[i]=f[i-1]*(ksm(q,i)+mod-1)%mod;
    
    // \sum_{i=0}^m (x-x^i)
    int iq=ksm(q,mod-2);
    muliq[0]=inviq[0]=1;
    for(int i=1;i<=m+1;i++) muliq[i]=muliq[i-1]*(ksm(iq,i)+mod-1)%mod*ksm(iq-1,mod-2)%mod;
    for(int i=1;i<=m+1;i++) inviq[i]=ksm(muliq[i],mod-2);
    for(int i=0;i<=m+1;i++){
        g[i]=ID(m+1+i)*ksm(q,S2(m+1)-S2(i))%mod*muliq[m+1]%mod*inviq[i]%mod*inviq[m+1-i]%mod;
    }
    
    // cout<<"f "; for(int i=0;i<=m;i++) cout<<f[i]<<" "; cout<<endl;
    // cout<<"g "; for(int i=0;i<=m+1;i++) cout<<g[i]<<" "; cout<<endl;
    
    for(int i=0;i<=m;i++){
        w[i]=ksm(q,S2(i)+i*(m-i))*ID(m-i)%mod*f[i]%mod*f[m-i]%mod;
    }
    // cout<<"w "; for(int i=0;i<=m;i++) cout<<w[i]<<" ";
    // cout<<endl;
    
    for(int i=0;i<=m;i++) y[i]=s[i]*ksm(w[i],mod-2)%mod*ksm(iq,i)%mod;
    
    for(int i=0;i<=m;i++) P[m-i]=y[i]*ksm(q,S2(i))%mod;
    for(int i=0;i<=m*2;i++) Q[i]=ksm(iq,S2(i))%mod;
    NTT::solve(R,P,Q,m,m*2);
    for(int i=0;i<=m;i++) F[i]=(mod-R[m+i]*ksm(q,S2(i))%mod)%mod;
    
    // cout<<"F "; for(int i=0;i<=m;i++) cout<<F[i]<<" ";
    // cout<<endl;
    
    NTT::solve(G,F,g,m,m);
    // cout<<"G "; for(int i=0;i<=m;i++) cout<<G[i]*2%mod<<" ";
    // cout<<endl;
    
    printf("%lld\n",G[n]);
    for(int i=n+1;i<=m;i++) printf("%lld\n",G[i]*ksm(q,(i-n)*n)%mod*2%mod);
    fflush(stdout);
}

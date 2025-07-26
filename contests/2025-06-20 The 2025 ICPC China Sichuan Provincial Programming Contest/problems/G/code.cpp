#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+5,mod=998244353;

int ksm(int a,int x){
    int tot=1;
    while(x){
        if(x & 1ll) tot=tot*a%mod;
        x>>=1ll;
        a=a*a%mod;
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


namespace Evaluation{
	int tmp[N];
	vector <int> P[N],Q[N],Qn[N];
	int lenp[N],lenq[N];
	void init(int o,int l,int r){
		int len=r-l+1,mid=(l+r)>>1ll;
		lenp[o]=len;
		lenq[o]=len-1;
		P[o].resize(2*lenp[o]+2);
		Q[o].resize(2*lenq[o]+2);
		if(l==r) return ;
		init(o<<1,l,mid);
		init(o<<1|1,mid+1,r);
	}
	
	void solve1(int *a,int o,int l,int r){	
		if(l==r){
			P[o]={1,(mod-a[l])%mod};
			return ;
		}
		int mid=(l+r)>>1;
		solve1(a,o<<1,l,mid);
		solve1(a,o<<1|1,mid+1,r);
		NTT::solve(P[o].data(),P[o<<1].data(),P[o<<1|1].data(),lenp[o<<1],lenp[o<<1|1]);
	}
	
	void solve2(int *s,int *a,int o,int l,int r){
		if(l==r){
			s[l]=Q[o][0];
			return ;
		}
		int mid=(l+r)>>1;
		int len1=mid-l+1,len2=r-mid;
		
		NTT::solve(tmp,Q[o].data(),P[o<<1|1].data(),lenq[o],lenp[o<<1|1]);
		for(int i=0;i<len1;i++) Q[o<<1][i]=tmp[i+len2];
		
		NTT::solve(tmp,Q[o].data(),P[o<<1].data(),lenq[o],lenp[o<<1]);
		for(int i=0;i<len2;i++) Q[o<<1|1][i]=tmp[i+len1];
		
		solve2(s,a,o<<1,l,mid);
		solve2(s,a,o<<1|1,mid+1,r);
	}
    //f: [0,n]; y: [1,m]
	void solve(int *s,int *f,int *a,int n,int m){
		m=max(n,m);
		n=max(n,m);
		init(1,1,m);
		solve1(a,1,1,m);
        for(int i=0;i<=n/2;i++) swap(f[i],f[n-i]);
		
		INV::solve(P[1].data(),P[1].data(),lenp[1]);
		
		NTT::solve(tmp,f,P[1].data(),n,lenp[1]);
		for(int i=0;i<=m;i++) Q[1][i]=tmp[i];
		
		solve2(s,a,1,1,m);
		for(int i=1;i<=m;i++){
			s[i]=(f[n]+1ll*s[i]*a[i]%mod)%mod;
		}
	}
}


int n,t;
int a[N];

vector <int> P[N*4];
void solve(int l,int r,int o){
    if(l==r){
        P[o]={mod-a[l],1};
        return ;
    }
    int mid=(l+r)>>1;
    solve(l,mid,o<<1);
    solve(mid+1,r,o<<1|1);
    int lenL=P[o<<1].size()-1,lenR=P[o<<1|1].size()-1;
    P[o].resize(lenL+lenR+1);
    NTT::solve(P[o].data(),P[o<<1].data(),P[o<<1|1].data(),lenL,lenR);
}
int F[N],G[N];

signed main(){
    cin>>n>>t;
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    
    int alc=1;
    for(int j=1;j<=n;j++) alc=alc*(t+mod-a[j])%mod;
    
    solve(1,n,1);
    for(int i=0;i<n;i++) F[i]=P[1][i+1]*(i+1)%mod;
    
    Evaluation::solve(G,F,a,n-1,n);
    for(int i=1;i<=n;i++){
        int A=alc*ksm(t+mod-a[i],mod-2)%mod;
        cout<<A*ksm(G[i],mod-2)%mod<<" ";
    }
}

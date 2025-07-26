#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=6e5+5,mod=998244353;

int ksm(int a,int x){
	int tot=1;
	while(x){
		if(x & 1ll) tot=1ll*tot*a%mod;
		a=1ll*a*a%mod;
		x>>=1ll;
	}
	return tot;
}

void gmod(int &x){
    if(x>=mod) x-=mod;
}

namespace NTT{
    void gmod(int &x){
        x+=x>>31 & mod;
    }
    int A[N],B[N],C[N];
    int rev[N],pre[N];
    int init(int n){
        int lim=0;
        while((1ll<<lim)<=n) lim++;
        for(int i=0;i<(1<<lim);i++)
            rev[i]=(rev[i>>1ll]>>1ll) | ((i & 1ll)<<(lim-1));
        int omega=ksm(3,(mod-1)/(1<<lim));
        pre[0]=1;
        for(int i=1;i<=(1<<lim);i++)
            pre[i]=1ll*pre[i-1]*omega%mod;
        return lim;
    }
    void ntt(int *f,int n,int opt){
        for(int i=0;i<n;i++)
            if(i<rev[i]) swap(f[i],f[rev[i]]);
        for(int l=1;l<n;l*=2){
            for(int i=0;i<n;i+=l*2){
                int u=n/l/2,nw=(opt==1)?0:n;
                for(int j=0;j<l;j++){
                    int x=f[i+j],y=1ll*pre[nw]*f[i+j+l]%mod;
                    f[i+j]=(x+y)%mod;
                    f[i+j+l]=(x-y+mod)%mod;
                    nw+=opt*u;
                }
            }
        }
        if(opt==-1){
            int t=ksm(n,mod-2);
            for(int i=0;i<=n-1;i++)
                f[i]=1ll*f[i]*t%mod;
        }
    }
    void solve(int *s,int* f,int* g,int n,int m){
        if(n+m<=150){
            for(int i=0;i<=n+m;i++) C[i]=0;
            for(int i=0;i<=n;i++){
                for(int j=0;j<=m;j++){
                    gmod(C[i+j]+=1ll*f[i]*g[j]%mod-mod);
                }
            }
            for(int i=0;i<=n+m;i++) s[i]=C[i];
            return ;
        }
        int lim=init(n+m);
        for(int i=0;i<=n;i++) A[i]=f[i];
        for(int i=0;i<=m;i++) B[i]=g[i];
        for(int i=n+1;i<(1ll<<lim);i++) A[i]=0;
        for(int i=m+1;i<(1ll<<lim);i++) B[i]=0;
        ntt(A,(1<<lim),1);
        ntt(B,(1<<lim),1);
        for(int i=0;i<(1<<lim);i++) C[i]=1ll*A[i]*B[i]%mod;
        ntt(C,(1<<lim),-1);
        for(int i=0;i<=n+m;i++) s[i]=C[i];
    }
}

namespace INV{
	int A[N],B[N],S[N];
	void solve(int *s,int *f,int n){
		S[0]=ksm(f[0],mod-2);
		S[1]=0;
		int len;
		for(len=2;len<=(n<<1ll);len<<=1ll){
			int lim=len<<1ll;
			for(int i=0;i<len;i++) A[i]=f[i],B[i]=S[i];
			for(int i=len;i<lim;i++) A[i]=B[i]=0;
			NTT::init(len);
			NTT::ntt(A,lim,1);
			NTT::ntt(B,lim,1);
			for(int j=0;j<lim;j++)
				S[j]=(2*B[j]%mod+mod-1ll*A[j]*B[j]%mod*B[j]%mod)%mod;
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

int n;
int a[N],mx[N];

int c[N],w[N];

int f[N],g[N],h[N];
int F[N],G[N],H[N];
void solve(int l,int r){
    if(l==r){
        // cout<<l<<": "<<f[l]<<" ";
        f[l]=(f[l]*w[l]%mod+c[l])%mod;
        return ;
    }
    int mid=(l+r)>>1;
    solve(l,mid);
    
    int len1=mid-l+1,len2=r-l+1;
    G[0]=0;
    for(int i=0;i<len1;i++) F[i]=f[l+i]*g[l+i]%mod;
    for(int i=1;i<=len2;i++) G[i]=h[i+1];
    
    NTT::solve(H,F,G,len1-1,len2);
    
    for(int i=len1;i<len2;i++) gmod(f[l+i]+=H[i]);
    
    solve(mid+1,r);
}



signed main(){
    init(N-5);
    cin>>n;
    
    INV::solve(g,mul,n);
    for(int i=1;i<=n;i++) g[i]=(mod-g[i])%mod;
    
    NTT::solve(h,mul,mul,n,n);
    for(int k=n;k>=1;k--) h[k]=h[k-1];
    h[0]=0;
    
    for(int k=1;k<=n;k++){
        c[k]=ksm((1+mod-g[k]*inv[k]%mod)%mod,mod-2);
        w[k]=c[k]*inv[k]%mod;
    }
    
    solve(1,n);
    // for(int k=1;k<=n;k++) cout<<f[k]<<" ";
    // cout<<endl;
    
    // for(int k=1;k<=n;k++){
    //     f[k]=0;
    //     for(int i=1;i<k;i++){
    //         gmod(f[k]+=g[i]*f[i]%mod*h[k-i+1]%mod);
    //     }
    //     f[k]=(f[k]*w[k]%mod+c[k])%mod;
    //     cout<<f[k]<<" ";
    // }
    // cout<<endl;
    
    for(int i=1;i<=n;i++){
        scanf("%lld",&a[i]);
        mx[i]=max(mx[i-1],a[i]);
    }
    int cur=0,ans=0;
    for(int i=1;i<=n;i++){
        if(mx[i]==i){
            ans=(ans+f[i-cur])%mod;
            cur=i;
        }
    }
    cout<<ans;
}

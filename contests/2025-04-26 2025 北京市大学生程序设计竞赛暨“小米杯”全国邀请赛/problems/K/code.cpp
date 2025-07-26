#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+5,K=11,mod=998244353,inv2=(mod+1)/2;

void gmod(int &x){
    x%=mod;
}

int ksm(int a,int x){
    int tot=1;
    while(x){
        if(x & 1) tot=tot*a%mod;
        a=a*a%mod;
        x>>=1;
    }
    return tot;
}

int mul[N];
void init(int lim){
    mul[0]=1;
    for(int i=1;i<=lim;i++) mul[i]=mul[i-1]*i%mod;
}

namespace NTT{
    int A[N],B[N],C[N];
    int rev[N],pre[N];
    int init(int n){
        int lim=0;
        while((1<<lim)<=n) lim++;
        for(int i=0;i<(1<<lim);i++)
            rev[i]=(rev[i>>1]>>1) | ((i & 1)<<(lim-1));
        int omega=ksm(3,(mod-1)/(1<<lim));
        pre[0]=1;
        for(int i=1;i<=(1<<lim);i++)
            pre[i]=pre[i-1]*omega%mod;
        return lim;
    }
    void ntt(int *f,int n,int opt){
        for(int i=0;i<n;i++)
            if(i<rev[i]) swap(f[i],f[rev[i]]);
        for(int l=1;l<n;l*=2){
            for(int i=0;i<n;i+=l*2){
                int u=n/l/2,nw=(opt==1)?0:n;
                for(int j=0;j<l;j++){
                    int x=f[i+j],y=pre[nw]*f[i+j+l]%mod;
                    gmod(f[i+j]=x+y);
                    gmod(f[i+j+l]=x+mod-y);
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
        for(int i=0;i<(1<<lim);i++) A[i]=B[i]=0;
        for(int i=0;i<=n;i++) A[i]=f[i];
        for(int i=0;i<=m;i++) B[i]=g[i];
        ntt(A,1<<lim,1);
        ntt(B,1<<lim,1);
        for(int i=0;i<(1<<lim);i++) C[i]=A[i]*B[i]%mod;
        ntt(C,1<<lim,-1);
        for(int i=0;i<=n+m;i++) s[i]=C[i]; 
    }
}

namespace INV{
    int A[N],B[N],S[N];
    void solve(int *s,int *f,int n){
        memset(A,0,sizeof(A));
        memset(B,0,sizeof(B));
        S[0]=ksm(f[0],mod-2);
        S[1]=0;
        for(int len=2;len<=(n<<1);len<<=1){
            int lim=len<<1;
            for(int i=0;i<len;i++) A[i]=f[i],B[i]=S[i];
            for(int i=len;i<lim;i++) A[i]=B[i]=0;
            NTT::init(len);
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

namespace poly {
    void Deriv(int *s,int *f,int n){
        int A[N]; A[n]=0;
        for(int i=1;i<=n;i++) A[i-1]=f[i]*i%mod;
        for(int i=0;i<=n;i++) s[i]=A[i];
    }
    void Limit(int *s,int *f,int n){
        int A[N]; A[0]=0;
        for(int i=0;i<=n-1;i++) A[i+1]=f[i]*ksm(i+1,mod-2)%mod;
        for(int i=0;i<=n;i++) s[i]=A[i];
    }
    void Ln(int *s,int *f,int n){
        int A[N],B[N];
        memset(A,0,sizeof(A));
        memset(B,0,sizeof(B));
        for(int i=0;i<=n;i++) A[i]=f[i],B[i]=0;
        Deriv(B,A,n);
        INV::solve(A,A,n);
        NTT::solve(A,A,B,n,n);
        Limit(A,A,n);
        for(int i=0;i<=n;i++) s[i]=A[i];
    }
    void Exp(int *s,int *f,int n){
        int A[N],B[N],C[N],S[N];
        memset(A,0,sizeof(A));
        memset(B,0,sizeof(B));
        memset(C,0,sizeof(C));
        memset(S,0,sizeof(S));
        S[0]=1;
        for(int len=2;len<=(n<<1);len<<=1){
            int lim=len<<1;
            for(int i=0;i<len;i++) A[i]=f[i],B[i]=S[i];
            
            Ln(C,B,len-1);
            for(int i=0;i<len;i++) C[i]=(mod-C[i]+A[i])%mod;
            C[0]=(C[0]+1)%mod;
            NTT::init(len);
            NTT::ntt(B,lim,1);
            NTT::ntt(C,lim,1);
            for(int j=0;j<lim;j++) S[j]=B[j]*C[j]%mod;
            
            NTT::ntt(S,lim,-1);
            for(int j=len;j<lim;j++) S[j]=0;
        }
        for(int i=0;i<=n;i++) s[i]=S[i];
    }
}

int n,m,k;
int F[N],G[N],H[N];
int f[K][N];

int S2(int n){
    return n*(n-1)/2;
}

signed main(){
    init(N-5);
    cin>>n>>k;
    f[0][1]=1;
    for(int d=1;d<=k;d++){
        for(int i=0;i<=n;i++) f[d-1][i]=f[d-1][i]*ksm(inv2,S2(i))%mod;
        
        poly::Exp(F,f[d-1],n);
        for(int i=0;i<=n;i++) G[i]=F[i]*ksm(2,S2(i))%mod;
        poly::Ln(f[d],G,n);
        
        // for(int i=0;i<=n;i++) cout<<f[d][i]*mul[i]%mod<<" ";
        // cout<<endl;
    }
    cout<<f[k][n]*mul[n]%mod;
}

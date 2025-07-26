#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=6e5+5,mod=998244353,inv3=332748118,B=500;

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



namespace MTT {
    const double PI=acos(-1);
    int a[N],b[N],s[N];
    struct cpl{
        double A,B;
    };
    inline cpl operator +(cpl X,cpl Y){
        return (cpl){X.A+Y.A,X.B+Y.B};
    }
    inline cpl operator -(cpl X,cpl Y){
        return (cpl){X.A-Y.A,X.B-Y.B};
    }
    inline cpl operator *(cpl X,cpl Y){
        return (cpl){X.A*Y.A-X.B*Y.B,X.A*Y.B+X.B*Y.A};
    }
    
    namespace FFT{
        cpl A[N],B[N],C[N],S1[N],S2[N],pre[N];
        int S[N];
        int rev[N];
        int init(int n,int m){
            int lim=0;
            while((1ll<<lim)<=n+m) lim++;
            for(int i=0;i<(1<<lim);i++)
                rev[i]=(rev[i>>1ll]>>1ll) | ((i & 1ll)<<(lim-1));
            for(int i=0;i<=(1<<lim);i++)
                pre[i]={cos(2*PI*i/(1<<lim)),sin(2*PI*i/(1<<lim))};
            return lim;
        }
        void fft(cpl *a,int n,int opt){
            for(int i=0;i<n;i++)
                if(i<rev[i]) swap(a[i],a[rev[i]]);
            for(int l=1;l<n;l*=2){
                for(int i=0;i<n;i+=l*2){
                    int u=n/l/2,nw=(opt==1)?0:n;
                    for(int j=0;j<l;j++){
                        cpl x=a[i+j],y=pre[nw]*a[i+j+l];
                        a[i+j]=x+y,a[i+j+l]=x-y;
                        nw+=opt*u;
                    }
                }
            }
            if(opt==-1){
                for(int i=0;i<n;i++) a[i].A=a[i].A/n,a[i].B=a[i].B/n;
            }
        }
        void solve(int *s,int *f,int *g,int n,int m,int mod){
            int M=sqrt(mod);
            int lim=init(n,m);
            for(int i=0;i<=n;i++) A[i]=(cpl){f[i]%M,f[i]/M},B[i]=(cpl){f[i]%M,-f[i]/M};
            for(int i=0;i<=m;i++) C[i]=(cpl){g[i]%M,g[i]/M};
            for(int i=n+1;i<(1ll<<lim);i++) A[i]=B[i]=(cpl){0,0};
            for(int i=m+1;i<(1ll<<lim);i++) C[i]=(cpl){0,0};
            fft(A,(1<<lim),1);
            fft(B,(1<<lim),1);
            fft(C,(1<<lim),1);
            for(int i=0;i<(1<<lim);i++) S1[i]=A[i]*C[i],S2[i]=B[i]*C[i];
            fft(S1,(1<<lim),-1);
            fft(S2,(1<<lim),-1);
            for(int i=0;i<=n+m;i++){
                long long a=round((S1[i].A+S2[i].A)/2),b=round((S2[i].A-S1[i].A)/2),c=round(S1[i].B);
                s[i]=(a%mod+b%mod*M%mod*M%mod+c%mod*M%mod)%mod;
            }
        }
    }
}







int n,ans,a[N],sgn[N];
int ln[N];
char S[N];

unordered_map <int,int> mp;

bool ispr[N];
int mxpr[N];

int F[N],G[N],H[N];
int f[N],g[N],s[N];

signed main(){
    init(N-5);
    scanf("%lld",&n);
    for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
    scanf("\n%s",S+1);
    for(int i=1;i<n;i++) sgn[i+1]=(S[i]=='+')?1:-1;
    
    for(int i=2;i<=n;i++) ispr[i]=1;
    for(int i=2;i<=n;i++){
        if(!ispr[i]) continue;
        for(int j=2;j<=n/i;j++)
            ispr[i*j]=0,mxpr[i*j]=i;
    }
    
    int bas=ksm(3,B),tot=1;
    for(int i=0;i<=mod/B;i++){
        mp[tot]=i;
        tot=tot*bas%mod;
    }
    for(int i=2;i<=n;i++){
        if(!ispr[i]) continue;
        int x=i;
        for(int j=0;j<B;j++){
            if(mp[x]){
                ln[i]=(mp[x]*B+j)%(mod-1);
                break;
            }
            x=x*inv3%mod;
        }
    }
    for(int i=2;i<=n;i++){
        if(!ispr[i]){
            int t=mxpr[i];
            ln[i]=(ln[t]+ln[i/t])%(mod-1);
        }
    }
    
    for(int i=1;i<=n;i++) F[i]=ln[i];
    for(int i=2;i<=n;i++) G[i]=(sgn[i]==1);
    MTT::FFT::solve(f,F,G,n,n,mod-1);
    
    memset(G,0,sizeof(G));
    for(int i=2;i<=n;i++) G[i]=(sgn[i]==-1);
    MTT::FFT::solve(g,F,G,n,n,mod-1);
    
    // for(int i=1;i<=n;i++) cout<<F[i]<<" "; cout<<endl;
    // for(int i=1;i<=n;i++) cout<<G[i]<<" "; cout<<endl;
    // for(int i=1;i<=n+1;i++) cout<<g[i]<<" "; cout<<endl;
    
    // return 0;
    
    s[2]=1;
    for(int k=3;k<=n;k++){
        if(sgn[k-1]==-1) continue;
        int tot1=0,tot2=0;
        // for(int i=2;i<k;i++){
        //     if(sgn[i]==1) tot1=(tot1+ln[k+1-i])%(mod-1);
        // }
        tot1=f[k+1];
        // for(int i=2;i<k;i++){
        //     if(sgn[i]==-1) tot2=(tot2+ln[k-1-i])%(mod-1);
        // }
        tot2=g[k-1];
        // cout<<k<<": "<<tot1<<" "<<tot2<<endl;
        s[k]=ksm(3,(tot1+tot2)%(mod-1));
    }
    // cout<<endl;
    
    ans=a[1]*mul[n-1]%mod;
    for(int k=2;k<=n;k++){
        ans=(ans+s[k]*ksm(k-1,mod-2)%mod*mul[n-1]%mod*(mod+sgn[k])%mod*a[k]%mod*inv[k-2]%mod)%mod;
    }
    cout<<ans;
}

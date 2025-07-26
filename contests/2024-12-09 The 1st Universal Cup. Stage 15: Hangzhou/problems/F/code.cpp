#pragma GCC optimize(3)
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e6+5,mod=998244353;
int T,n,p,g;
int a[N],mp[N];
int d[N],id;
vector <int> ANS;

int ksmmod(int a,int x){
    int tot=1;
    while(x){
        if(x & 1ll) tot=tot*a%mod;
        a=a*a%mod;
        x>>=1ll;
    }
    return tot;
}
int ksm(int a,int x){
    int tot=1;
    while(x){
        if(x & 1ll) tot=tot*a%p;
        a=a*a%p;
        x>>=1ll;
    }
    return tot;
}

void gmod(int &x){
    x+=x>>31 & mod;
}
namespace NTT{
    int A[N],B[N],C[N];
    int rev[N],pre[N];
    int init(int n){
        int lim=0;
        while((1<<lim)<=n) lim++;
        for(int i=0;i<(1<<lim);i++)
            rev[i]=(rev[i>>1]>>1) | ((i & 1)<<(lim-1));
        
        int omega=ksmmod(3,(mod-1)/(1<<lim));
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
                    gmod(f[i+j]=x+y-mod),gmod(f[i+j+l]=x-y);
                    nw+=opt*u;
                }
            }
        }
        if(opt==-1){
            int t=ksmmod(n,mod-2);
            for(int i=0;i<=n-1;i++)
                f[i]=f[i]*t%mod;
        }
    }
    void solve(int *s,int *f,int *g,int n,int m){
        if(n<=150){
            for(int i=0;i<=n;i++){
                for(int j=0;j<=m;j++){
                    gmod(s[i+j]+=f[i]*g[j]%mod-mod);
                }
            }
            return ;
        }
        
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


int F[N],G[N],H[N];
bool check(int k){
    for(int i=0;i<=p*2;i++) F[i]=G[i]=H[i]=0;
    for(int i=1;i<=k;i++) F[mp[i]]=1; // t
    for(int i=1;i<=n;i++)
        if(a[i]) G[p-mp[a[i]]]=G[p-mp[a[i]]+p-1]=1; // x
    NTT::solve(H,F,G,p,p*2);
    // cout<<"F: "; for(int i=0;i<=p;i++) cout<<F[i]<<" "; cout<<endl;
    // cout<<"G: "; for(int i=0;i<=p;i++) cout<<G[i]<<" "; cout<<endl;
    // cout<<"H: "; for(int i=0;i<=p;i++) cout<<H[i+p]<<" "; cout<<endl;
    for(int i=0;i<p-1;i++) if(H[i+p]==k) return 1;
    return 0;
}


signed main(){
    // freopen("1.txt","r",stdin);
    // freopen("3.txt","w",stdout);
    cin>>T;
    while(T--){
        scanf("%lld%lld",&n,&p);
        
        ANS.clear();
        
        bool fl=0;
        for(int i=1;i<=n;i++){
            scanf("%lld",&a[i]);
            if(!a[i]) fl=1;
        }
        
        
        if(!fl){
            printf("1 1\n");
            printf("0\n");
            continue;
        }
        if(n==1){
            printf("%lld 1\n",p);
            for(int i=0;i<p;i++) printf("%lld ",i);
            printf("\n");
            continue;
        }
        
        if(p==2){
            if(n==2) printf("1 2\n1\n");
            else printf("2 1\n0 1\n");
            continue;
        }
        
        id=0;
        for(int i=2;i<p-1;i++){
            if((p-1)%i==0) d[++id]=i;
        }
        for(int i=2;i<p;i++){
            bool flag=1;
            for(int j=1;j<=id && flag;j++){
                if(ksm(i,d[j])==1) flag=0;
            }
            if(flag){
                g=i;
                break;
            }
        }
        
        // cout<<" "<<p<<" "<<g<<endl;
        // memset(mp,0,sizeof(mp));
        for(int i=0;i<=p;i++) mp[i]=0;
        for(int i=0;i<p-1;i++) mp[ksm(g,i)]=i;
        // for(int i=1;i<=p-1;i++) cout<<mp[i]<<" ";
        // cout<<endl;
        // continue;
        
        int l=1,r=p-1,tot=0;
        while(l<=r){
            int mid=(l+r)>>1;
            
            if(check(mid)) l=mid+1,tot=mid;
            else r=mid-1;
        }
        check(tot);
        for(int i=0;i<p-1;i++) if(H[i+p]==tot) ANS.push_back(ksm(g,i));
        
        sort(ANS.begin(),ANS.end());
        printf("%lld %lld\n",ANS.size(),tot+1);
        for(int x: ANS) printf("%lld ",x);
        printf("\n");
    }
    
}

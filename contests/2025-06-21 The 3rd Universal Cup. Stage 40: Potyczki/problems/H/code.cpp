#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e6+5,mod=1e9+7;

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

int T,n,a,b;

int p[N],id;
bool vis[N];
int num[N];

signed main(){
    init(N-5);
    
    cin>>T;
    while(T--){
        scanf("%lld%lld%lld",&n,&a,&b);
        if(a>b) swap(a,b);
        int ans=0;
        
        id=0;
        p[++id]=n; num[n]=1;
        for(int i=1;i<=id;i++){
            int x=p[i];
            if(x<=1) continue;
            
            int L=(x+1)/2,R=x-L;
            
            int tot=0;
            tot=(tot+C(n-2-(b-a-1),R-1)*C(n-1-R,L-1)%mod)%mod;
            tot=(tot+C(n-2-(b-a-1),L-1)*C(n-1-L,R-1)%mod)%mod;
            
            ans=(ans+tot*mul[n-L-R]%mod*mul[L]%mod*mul[R]%mod*num[x]%mod)%mod;
            
            if(!vis[L]) p[++id]=L,vis[L]=1;
            if(!vis[R]) p[++id]=R,vis[R]=1;
            num[L]+=num[x];
            num[R]+=num[x];
        }
        
        for(int i=1;i<=id;i++){
            int x=p[i];
            num[x]=vis[x]=0;
        }
        
        printf("%lld\n",ans);
    }
}

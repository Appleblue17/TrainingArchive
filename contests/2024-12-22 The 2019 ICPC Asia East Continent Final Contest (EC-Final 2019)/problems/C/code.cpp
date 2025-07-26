#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+5,mod=998244353;

int ksm(int a,int x){
    int tot=1;
    while(x){
        if(x & 1ll) tot=tot*a%mod;
        a=a*a%mod;
        x>>=1ll;
    }
    return tot;
}

int n,k;
int f[N],g[N];
vector <int> V[N];

bool vis[N];
int ln[N];


signed main(){
    cin>>n>>k;
    for(int i=1;i<=n;i++) scanf("%lld",&g[i]);
    
    for(int t=2;t<=n;t++){
        if(vis[t]) continue;
        for(int i=t;i<=n;i+=t){
            int x=i,c=0;
            while(x%t==0) x/=t,c++;
            ln[i]+=c;
            vis[i]=1;
        }
    }
    for(int i=1;i<=n;i++)
        for(int j=i;j<=n;j+=i)
            V[j].push_back(i);
    
    // for(int i=1;i<=n;i++) cout<<ln[i]<<" ";
    // cout<<endl;
    
    f[1]=1;
    for(int i=2;i<=n;i++){
        int tot=0;
        for(int d: V[i]){
            tot=(tot+f[i/d]*g[d]%mod*(mod-ln[d])%mod+mod-k*f[d]%mod*g[i/d]%mod*(mod-ln[d])%mod)%mod;
        }
        f[i]=tot*ksm((mod-ln[i])*k%mod,mod-2)%mod;
        // cout<<i<<" "<<f[i]<<endl;
    }
    for(int i=1;i<=n;i++) printf("%lld ",f[i]);
    
    
}

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define N 210000
ll n,m,k,leafcnt[N],siz[N],sizcnt[N],sizleafcnt[N],f[N],sizw[N],n1[N];
vector<ll> g[N];
const ll mod=998244353;

ll ksm(ll a,ll x){
    ll tot=1;
    while(x){
        if(x & 1ll) tot=tot*a%mod;
        a=a*a%mod;
        x>>=1;
    }
    return tot;
}

ll mul[N],inv[N];
void init(ll lim){
    mul[0]=inv[0]=1;
    for(ll i=1;i<=lim;i++) mul[i]=mul[i-1]*i%mod;
    inv[lim]=ksm(mul[lim],mod-2);
    for(ll i=lim-1;i>=1;i--) inv[i]=inv[i+1]*(i+1)%mod;
}
ll C(ll m,ll n){
    if(m<n || m<0 || n<0) return 0;
    return mul[m]*inv[n]%mod*inv[m-n]%mod;
}

void dfs(ll u,ll fa){
    siz[u]=1;
    leafcnt[u]=0;
    for(ll v:g[u]){
        if(v == fa)continue;
        f[v]=u;
        dfs(v,u);
        
        siz[u]+=siz[v];
        leafcnt[u]+=leafcnt[v];
    }
    if(siz[u]==1){
        leafcnt[u]=1;
    }
    
    //printf("u=%lld,siz=%lld,leafcnt=%lld\n",u,siz[u],leafcnt[u]);
}
ll rt=1;
int main(){
    init(N-10);
    //printf("init done\n");
    scanf("%lld",&n);
    for(ll i=1;i<n;i++){
        ll u,v;
        scanf("%lld%lld",&u,&v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for(ll i=1;i<=n;i++){
        if(g[i].size()>1){
            rt=i;
            break;
        }
    }
    if(n == 2){
        printf("4\n");
        return 0;
    }
    dfs(rt,0);
    for(ll u=1;u<=n;u++){
        if(siz[u] <= n/2+1){
            if(!sizcnt[siz[u]]){
                if(g[f[u]].size()==2){
                    n1[siz[u]]=1;
                }
                sizcnt[siz[u]]=1;
                sizw[siz[u]]=u;
                sizleafcnt[siz[u]]=leafcnt[u];
                //printf("first occurance(z) of siz=%lld,sizleafcnt=%lld\n",siz[u],leafcnt[u]);
            }
            else{
                sizcnt[siz[u]]++;
            }
        }
        if(n-siz[u] <= n/2+1){
            if(u==rt)continue;
            if(!sizcnt[n-siz[u]]){
                if(g[u].size()==2){
                    n1[n-siz[u]]=1;
                }
                sizw[n-siz[u]]=u;
                sizcnt[n-siz[u]]=1;
                sizleafcnt[n-siz[u]]=leafcnt[rt]-leafcnt[u];
                //printf("first occurance(anti) of siz=%lld,sizleafcnt=%lld\n",n-siz[u],leafcnt[rt]-leafcnt[u]);
            }
            else{
                sizcnt[n-siz[u]]++;
            }
        }
    }
    ll ans = 2;
    for(ll i=1;i<=n/2;i++){
        //printf("sizcnt[%lld]=%lld,sizleafcnt[%lld]=%lld\n",i,sizcnt[i],i,sizleafcnt[i]);
        ll tmp=0;
        if(sizcnt[i]){
            if(sizcnt[i]>=2){
                tmp = C(n,i);
            }
            else if(sizcnt[i-1]){
                tmp = C(n,i);
            }
            else if(n1[i]){
                tmp = C(n,i);
            }
            else{
                ll t = leafcnt[rt]-sizleafcnt[i];
                if(i-t >= 0)tmp = C(n,i)+mod-C(n-leafcnt[rt],i-t);
                else tmp = C(n,i);
            }
        }
        if(i != n-i){
            ans += tmp*2;
        }
        else{
            ans += tmp;
        }
        ans %= mod ;
    }
    ans %= mod;
    printf("%lld\n",ans);
}

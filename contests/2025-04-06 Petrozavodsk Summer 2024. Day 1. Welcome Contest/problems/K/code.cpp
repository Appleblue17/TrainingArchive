#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define N 210000
ll n,m,k;
vector<ll> g[N],va[N],id[N];
vector<ll> cta[N];
multiset<ll> s[N];
unordered_map<ll,ll> ma[N];

int main(){
    scanf("%lld%lld",&n,&m);
    unordered_map<ll,ll> eid;
    for(int i=1;i<=m;i++){
        ll u,v,w;
        scanf("%lld%lld%lld",&u,&v,&w);
        g[u].push_back(v);
        va[u].push_back(w);
        id[u].push_back(i);
        eid[u*1e9+v]=i;
    }
    scanf("%lld",&k);
    for(int i=1;i<=k;i++){
        ll  a,b,c;
        scanf("%lld%lld%lld",&a,&b,&c);
        cta[eid[b*1e9+c]].push_back(a);
    }
    s[1].insert(0);
    for(int i=1;i<=n;i++){
        if(s[i].empty())continue;
        for(int j=0;j<g[i].size();j++){
            ll v = g[i][j];
            ll w = va[i][j];
            ll x = id[i][j];
            //printf("i=%d,v=%lld,w=%lld,x=%lld\n",i,v,w,x);
            for(ll a:cta[eid[i*1e9+v]]){
                if(!ma[i][a]){
                    continue;
                }
                s[i].erase(s[i].find(ma[i][a]));
                //printf("erasing the effect of (%d,%d,%d)\n",a,i,v);
            }
            
            if(!s[i].empty()){
                ll t = *s[i].begin();
                t += w;
                //printf("update v=%lld with t=%lld\n",v,t);
                s[v].insert(t);
                ma[v][i]=t;
            }
            
            for(ll a:cta[eid[i*1e9+v]]){
                if(!ma[i][a]){
                    continue;
                }
                s[i].insert(ma[i][a]);
            }
        }
    }
    if(!s[n].empty()){
        printf("%lld\n",*s[n].begin());
    }
    else{
        printf("-1\n");
    }
}

#pragma GCC optimize(2)
#pragma GCC optimize(3)
#include<bits/stdc++.h>
using namespace std;
const int N=1e7+5;
typedef long long ll;
const ll inf=1000000007ll;
int T;
int n, m;
typedef pair<int, int> pii;
#define fi first
#define se second
vector<pii> e2[N];
int idx;
unordered_map<int, int> fa;
int b[N], c[N];
inline int get(int x){
    if(x==fa[x]) return x;
    return fa[x]=get(fa[x]);
}
pii seg[N]; int tot;
int lp[N], rp[N];
void solve(){
    scanf("%d%d", &n, &m);
    if(m==0){
        printf("%d\n", n-1);
        return ;
    }
    unordered_map<ll, int> e;
    vector<int> vec;
    for(int i=1; i<=idx; ++i) e2[i].clear();
    unordered_map<int, int> h; idx=0;
    for(int i=1, x, y, z; i<=m; ++i){
        scanf("%d%d%d", &x, &y, &z);
        if(h.find(x)==h.end()) h[x]=++idx;
        if(h.find(y)==h.end()) h[y]=++idx;
        e2[h[x]].emplace_back(y, z);
        e2[h[y]].emplace_back(x, z);
        e[inf*x+y]=z;
        e[inf*y+x]=z;
        vec.emplace_back(x); vec.emplace_back(y);
    }
    sort(vec.begin(), vec.end());
    vec.erase(unique(vec.begin(), vec.end()), vec.end());
    int lst=0;
    fa.clear(); 
    tot=0;
    for(int i=0; i<(int)vec.size(); ++i){
        if(lst+1<=vec[i]-1){
            seg[++tot]=make_pair(lst+1, vec[i]-1);
        }
        seg[++tot]=make_pair(vec[i], vec[i]);
        lst=vec[i];
    }
    if(lst+1<=n){
        seg[++tot]=make_pair(lst+1, n);
    }
    ll ans=0;
    for(int i=1; i<=tot; ++i) {
        ans+=seg[i].se-seg[i].fi, lp[i]=rp[i]=i;
        fa[i]=i;
        fa[seg[i].fi+inf]=i; fa[seg[i].se+inf]=i;
    }
    int res=tot;
    while(res>1){
        for(int i=1; i<=tot; ++i) b[i]=0, c[i]=inf;
        for(int j=1; j<=tot; ++j) {
            if(seg[j].fi==seg[j].se&&h.find(seg[j].fi)!=h.end()){
                for(auto edg:e2[h[seg[j].fi]]){
                    int y=edg.fi, z=edg.se;
                    if(get(y+inf)==get(j)) continue;
                    int u=get(j), v=get(y+inf);
                    if(make_pair(z, v)<make_pair(c[u], b[u])) c[u]=z, b[u]=v;
                    if(make_pair(z, u)<make_pair(c[v], b[v])) c[v]=z, b[v]=u;
                }
            }
            int p=lp[j]-1;
            while(p>=1&&get(p)==get(j)) p=lp[p]-1, lp[j]=p+1;
            while(p>=1) {
                while(p>=1&&get(p)==get(j)) p=lp[p]-1;
                if(p<1) break;
                if(e.find(inf*seg[j].fi+seg[p].se)!=e.end()){
                    --p;
                }
                else{
                    int z=seg[j].fi-seg[p].se;
                    int u=get(j), v=get(p);
                    if(make_pair(z, v)<make_pair(c[u], b[u])) c[u]=z, b[u]=v;
                    if(make_pair(z, u)<make_pair(c[v], b[v])) c[v]=z, b[v]=u;
                    break;
                }
            }
        }
        for(int j=tot; j>=1; --j) {
            int p=rp[j]+1;
            while(p<=tot&&get(p)==get(j)) p=rp[p]+1, rp[j]=p-1;
            while(p<=tot) {
                while(p<=tot&&get(p)==get(j)) p=rp[p]+1;
                if(p>tot) break;
                if(e.find(inf*seg[j].se+seg[p].fi)!=e.end()){
                    ++p;
                }
                else{
                    int z=seg[p].fi-seg[j].se;
                    int u=get(j), v=get(p);
                    if(make_pair(z, v)<make_pair(c[u], b[u])) c[u]=z, b[u]=v;
                    if(make_pair(z, u)<make_pair(c[v], b[v])) c[v]=z, b[v]=u;
                    break;
                }
            }
        }
        for(int i=1; i<=tot; ++i) if(b[i]&&i==get(i)){
            int x=get(i), y=get(b[i]);
            if(x==y) continue;
            ans+=c[i]; fa[y]=x;
            --res;
        }
    }
    printf("%lld\n", ans);
}
int main(){
	// freopen("D:\\nya\\acm\\A\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\A\\test.out","w",stdout);
    scanf("%d", &T);
    for(int i=1; i<=T; ++i){
        solve();
    }
    return 0;
}

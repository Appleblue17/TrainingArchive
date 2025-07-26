#include <bits/stdc++.h>
using namespace std;
const int N=5e5+5,INF=1e9;
int T,n;
vector<int> e1[N], e2[N];
int dfn[N], timer, lp[N], rp[N], pos[N], f[N][20], dep[N];
void dfs1(int x, int fa){
    dep[x]=dep[fa]+1; f[x][0]=fa;
    for(int i=1; i<20; ++i) f[x][i]=f[f[x][i-1]][i-1];
    dfn[x]=++timer; pos[timer]=x; lp[x]=timer;
    for(auto y:e2[x]) if(y^fa) dfs1(y, x);
    rp[x]=timer;
}
int rt[N];
int sz[N], son[N];
vector<int> vec[N];
int jump(int x, int y){
    for(int i=19; i>=0; --i) if(dep[f[x][i]]>dep[y]) x=f[x][i];
    return x;
}
void dfs2(int x, int fa){
    sz[x]=1; son[x]=0;
    for(auto y:e1[x]) if(y^fa) {
        dfs2(y, x);
        sz[x]+=sz[y];
        if(sz[y]>sz[son[x]]) son[x]=y;
    }
}
struct BIT{
    int tr[N];
    inline void add(int x, int v){
        for(; x<=n; x+=(x&-x)) tr[x]+=v;
    }
    inline int get(int l, int r){
        int ret=0;
        for(; r; r-=(r&-r)) ret+=tr[r];
        for(--l; l; l-=(l&-l)) ret-=tr[l];
        return ret;
    }
}B;
long long ans=0;
void dfs3(int x, int fa, int flag){
    rt[x]=x; vec[x].push_back(x);
    for(auto y:e1[x]) if(y!=fa&&y!=son[x]){
        dfs3(y, x, 0);
    }
    if(!son[x]) {
        if(flag) B.add(dfn[x], 1);
        return ;
    }
    dfs3(son[x], x, 1);
    ans+=B.get(lp[x], rp[x]);
    rt[x]=rt[son[x]];
    vec[rt[x]].push_back(x);
    B.add(dfn[x], 1);
    for(auto y:e1[x]) if(y!=fa&&y!=son[x]){
        for(auto t:vec[rt[y]]){
            if(!(lp[x]<=dfn[t]&&dfn[t]<=rp[x])) continue;
            int ft=jump(t, x);
            ans+=B.get(lp[x], rp[x]);
            ans-=B.get(lp[ft], rp[ft]);
        }
        for(auto t:vec[rt[y]]){
            vec[rt[x]].push_back(t);
            B.add(dfn[t], 1);
        }
    }
    if(!flag){
        for(auto t:vec[rt[x]]) B.add(dfn[t], -1);
    }
}
signed main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i=1; i<=n; ++i) e1[i].clear(), e2[i].clear();
        for(int i=1, x, y; i<n; ++i){
            scanf("%d%d", &x, &y);
            e1[x].push_back(y); e1[y].push_back(x);
        }
        for(int i=1, x, y; i<n; ++i){
            scanf("%d%d", &x, &y);
            e2[x].push_back(y); e2[y].push_back(x);
        }
        timer=0;
        dfs1(1, 0);
        for(int i=1; i<=n; ++i) vec[i].clear();
        dfs2(1, 0);
        ans=0;
        dfs3(1, 0, 0);
        printf("%lld\n", ans);
    }
    
}

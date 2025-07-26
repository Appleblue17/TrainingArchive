#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
typedef long long ll;
int T;
int n;
vector<int> e[N];
int a[N];
int tr[N<<2];
inline void build(int p, int l, int r){
    if(l==r){
        tr[p]=a[l];
        return ;
    }
    int mid=(l+r)>>1;
    build(p<<1, l, mid); build(p<<1|1, mid+1, r);
    tr[p]=min(tr[p<<1], tr[p<<1|1]);
}
inline int get(int p, int l, int r, int L, int R){
    if(L<=l&&r<=R) return tr[p];
    int mid=(l+r)>>1, ret=1e9;
    if(L<=mid) ret=get(p<<1, l, mid, L, R);
    if(R>mid) ret=min(ret, get(p<<1|1, mid+1, r, L, R));
    return ret;
}
int f[N][25];
int dfn[N], tim, dep[N];
vector<int> vec[N];
inline void dfs(int x, int fa){
    dfn[x]=++tim;
    dep[x]=dep[fa]+1;
    vec[dep[x]].push_back(x);
    f[x][0]=fa;
    for(int i=1; i<=20; ++i) f[x][i]=0;
    for(int i=1; f[x][i-1]; ++i) f[x][i]=f[f[x][i-1]][i-1];
    for(auto y:e[x]){
        if(y==fa) continue;
        dfs(y, x);
    }
}
inline bool cmp(int x, int y){
    return dfn[x]<dfn[y];
}
inline int lca(int x, int y){
    if(dep[x]>dep[y]) swap(x, y);
    for(int i=20; i>=0; --i) if(dep[f[y][i]]>=dep[x]) y=f[y][i];
    if(y==x) return x;
    for(int i=20; i>=0; --i) if(f[y][i]!=f[x][i]) x=f[x][i], y=f[y][i];
    return f[x][0];
}
int stk[N], top;
vector<int> g[N];
inline void add(int x, int y){
    g[x].push_back(y); 
    g[y].push_back(x);
}
inline void build(int id){
    stk[top=1]=1; g[1].clear();
    for(auto x:vec[id]){
        int lc=lca(stk[top], x);
        if(lc!=stk[top]){
            while(dfn[stk[top-1]]>dfn[lc]) add(stk[top], stk[top-1]), --top;
            if(lc!=stk[top-1]) g[lc].clear(), add(lc, stk[top]), stk[top]=lc;
            else add(lc, stk[top]), --top;
        }
        g[x].clear(); stk[++top]=x;
    }
    for(int i=1; i<top; ++i) add(stk[i], stk[i+1]);
}
ll dp[N];
int rk[N], lp[N], rp[N];
void dfs2(int x, int fa, int id){
    if(dep[x]==id){
        dp[rk[x]]=min(dp[rk[x]], dp[rk[x]-1]+get(1, 1, n, 1, id-dep[fa]));
        lp[x]=rp[x]=rk[x];
        return ;
    }
    lp[x]=n, rp[x]=1;
    for(auto y:g[x]){
        if(y==fa) continue;
        dfs2(y, x, id);
        lp[x]=min(lp[x], lp[y]); rp[x]=max(rp[x], rp[y]);
    }
    dp[rp[x]]=min(dp[rp[x]], dp[lp[x]-1]+get(1, 1, n, id-dep[x]+1, id-dep[fa]));
}
void solve(){
    scanf("%d", &n);
    for(int i=1; i<=n; ++i) {
        scanf("%d", &a[i]);
        e[i].clear();
        vec[i].clear();
    }
    build(1, 1, n);
    for(int i=1, x, y; i<n; ++i){
        scanf("%d%d", &x, &y);
        e[x].push_back(y); 
        e[y].push_back(x);
    }
    tim=0;
    dfs(1, 0);
    ll ans=a[1];
    for(int i=2; i<=n; ++i){
        if(vec[i].empty()) break;
        sort(vec[i].begin(), vec[i].end(), cmp);
        build(i);
        for(int j=1; j<=(int)vec[i].size(); ++j) dp[j]=1e18, rk[vec[i][j-1]]=j;
        dp[0]=0;
        dfs2(1, 0, i);
        ans+=dp[vec[i].size()];
    }
    printf("%lld\n", ans);
}
int main(){
    scanf("%d", &T);
    while(T--){
        solve();
    }
}

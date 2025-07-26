#pragma GCC optimize(2)
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e6+6;
int T, n, m;
int p[N], rk[N];
int tr[N];
void add(int x, int v){
    for(; x<=n; x+=(x&-x)) tr[x]+=v;
}
int get(int l, int r){
    int ret=0;
    for(; r; r-=(r&-r)) ret+=tr[r];
    for(--l; l; l-=(l&-l)) ret-=tr[l];
    return ret;
}
set<int> e[N];
set<int> bin[N]; int rt[N], idx;
int ans[N];
int ft[N], lp[N], rp[N], timer;
void work(int x, int fa, int root){
    bin[root].insert(rk[x]);
    for(auto y:e[x]) if(y^fa) work(y, x, root);
}
void del(int x, int fa, int root){
    bin[root].erase(rk[x]);
    for(auto y:e[x]) if(y^fa) del(y, x, root);
}
void dfs(int x, int fa){
    ft[x]=fa;
    lp[x]=++timer;
    add(timer, 1);
    for(auto y:e[x]){
        if(y==fa) continue;
        dfs(y, x);
    }
    rp[x]=timer;
}
int sz(int x){
    return get(lp[x], rp[x]);
}
int calc(int x, int all){
    int ct=p[*bin[rt[x]].begin()];
    bin[rt[x]].erase(rk[ct]);
    int cursz=sz(ct);
    add(lp[ct], -cursz);
    --all;
    vector<pair<int, int> > vec;
    for(auto y:e[ct]){
        e[y].erase(e[y].find(ct));
        if(ft[y]==ct) vec.push_back(make_pair(sz(y), y)), all-=sz(y);
    }
    for(auto y:e[ct]){
        if(ft[ct]==y) vec.push_back(make_pair(all, y));
    }
    if(vec.empty()) {
        add(lp[ct], cursz);
        return ct;
    }
    sort(vec.begin(), vec.end());
    int lstrt=rt[x];
    for(int i=0; i+1<(int)vec.size(); ++i){
        int nx=vec[i].second;
        rt[nx]=++idx;
        work(nx, 0, idx);
        del(nx, 0, lstrt);
        ans[calc(nx, vec[i].first)]=ct;
    }
    rt[vec.back().second]=lstrt;
    ans[calc(vec.back().second, vec.back().first)]=ct;
    add(lp[ct], cursz);
    return ct;
}
void solve(){
    scanf("%d", &n);
    for(int i=1; i<=n; ++i) scanf("%d", &p[i]), rk[p[i]]=i;
    for(int i=0; i<=n; ++i) tr[i]=0, e[i].clear(), rt[i]=0, bin[i].clear();
    for(int i=1, x, y; i<n; ++i){
        scanf("%d%d", &x, &y);
        e[x].insert(y); e[y].insert(x);
    }
    timer=0;
    dfs(1, 0);
    rt[1]=idx=1;
    work(1, 0, 1);
    ans[calc(1, n)]=0;
    for(int i=1; i<=n; ++i) printf("%d ", ans[i]);
    putchar('\n');
}
int main(){
    // freopen("text.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    scanf("%d", &T);
    while(T--){
        solve();
    }
}

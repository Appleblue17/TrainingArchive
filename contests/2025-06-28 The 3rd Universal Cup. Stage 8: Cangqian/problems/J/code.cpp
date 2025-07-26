#include <bits/stdc++.h>
using namespace std;
const int N=5e5+5;
typedef long long ll;
int T, n, m; 
struct edg{
    int x, y, z;
    bool operator <(const edg &t)const{
        return z<t.z;
    }
};
edg e1[N], e2[N];
typedef pair<int, int> pii;
#define fi first
#define se second
vector<pii> e[N];
int fa[N];
int get(int x){
    if(x==fa[x]) return x;
    return fa[x]=get(fa[x]);
}
int f[N][20], w[2][N][20];
int val[N], dep[N];
void dfs(int x, int fa){
    f[x][0]=fa;
    dep[x]=dep[fa]+1;
    if(x!=1) {
        if(val[x]&1) w[1][x][0]=val[x];
        else w[0][x][0]=val[x];
    }
    for(int i=1; i<20; ++i){
        f[x][i]=f[f[x][i-1]][i-1];
        w[0][x][i]=max(w[0][x][i-1], w[0][f[x][i-1]][i-1]);
        w[1][x][i]=max(w[1][x][i-1], w[1][f[x][i-1]][i-1]);
    }
    for(auto ee:e[x]){
        int y=ee.fi, w=ee.se;
        if(y==fa) continue;
        val[y]=w;
        dfs(y, x);
    }
}
ll opt[2];
inline int get(int op, int x, int y){
    int ret=-2e9;
    if(dep[x]<dep[y]) swap(x, y);
    for(int i=19; i>=0; --i) {
        if(dep[f[x][i]]>=dep[y]) ret=max(ret, w[op][x][i]), x=f[x][i];
    }
    if(x==y) return ret;
    for(int i=19; i>=0; --i){
        if(f[x][i]!=f[y][i]){
            ret=max(ret, w[op][x][i]), x=f[x][i];
            ret=max(ret, w[op][y][i]), y=f[y][i];
        }
    }
    ret=max(ret, max(w[op][x][0], w[op][y][0]));
    return ret;
}
void solve(){
    scanf("%d%d", &n, &m);
    ll ans=0;
    for(int i=1; i<=m; ++i){
        scanf("%d%d%d", &e1[i].x, &e1[i].y, &e1[i].z);
    }
    sort(e1+1, e1+m+1);
    for(int i=1; i<=n; ++i){
        fa[i]=i; e[i].clear();
    }
    int m2=0;
    for(int i=1; i<=m; ++i){
        int fx=get(e1[i].x), fy=get(e1[i].y);
        if(fx==fy){
            e2[++m2]=e1[i];
            continue;
        }
        e[e1[i].x].emplace_back(e1[i].y, e1[i].z); e[e1[i].y].emplace_back(e1[i].x, e1[i].z);
        ans+=e1[i].z;
        fa[fx]=fy;
    }
    opt[0]=opt[1]=-1;
    if(ans&1) opt[1]=ans;
    else opt[0]=ans;
    if(m-m2!=n-1){
        printf("-1 -1\n");
        return ;
    }
    for(int i=1; i<=n; ++i) for(int j=0; j<20; ++j) w[0][i][j]=w[1][i][j]=-2e9;
    dfs(1, 0);
    for(int i=1; i<=m2; ++i){
        int x=e2[i].x, y=e2[i].y, z=e2[i].z;
        int cost=get((z&1)^1, x, y);
        if(cost!=-2e9) {
            if(opt[(ans&1)^1]==-1) opt[(ans&1)^1]=ans+z-cost;
            else opt[(ans&1)^1]=min(opt[(ans&1)^1], ans+z-cost);
        }
    }
    printf("%lld %lld\n", opt[0], opt[1]);
}
int main(){
    scanf("%d", &T);
    while(T--){
        solve();
    }
}

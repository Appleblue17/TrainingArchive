#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef long long ll;
const int N=505;
#define fi first
#define se second
typedef vector<int> vi;
typedef pair<int, int> pii;
#define pb push_back
#define mkp make_pair
#define inf 0x3f3f3f3f
int n, m;
ll a[N];
pair<int, int> pp[N];
ll cal(int x, int y){
    if(pp[x].se<pp[y].fi) return 0;
    else if(pp[x].se>pp[y].se) return 0;
    else return a[pp[x].se]-a[pp[y].fi];
}
struct edge{
    int u, v; ll w;
}e[N][N];
ll lab[N], sl[N], q[N], hd, tl, rt[N], col[N], mat[N], frm[N][N], fa[N];
int vis[N], tim;
vi p[N];
ll d(edge x){
    return lab[x.u]+lab[x.v]-e[x.u][x.v].w*2;
}
void upd(int u, int v){
    if(!sl[v]||d(e[u][v])<d(e[sl[v]][v])) sl[v]=u;
}
void updall(int u){
    sl[u]=0;
    for(int i=1; i<=n; ++i) if(e[i][u].w>0&&rt[i]!=u&&col[rt[i]]==0) upd(i, u);
}
void push(int u){
    if(u<=n) q[++tl]=u;
    else for(int x:p[u]) push(x);
}
void setrt(int u, int r){
    rt[u]=r;
    if(u>n) for(int x:p[u]) setrt(x, r);
}
int rot(int b, int x){
    int pos=find(p[b].begin(), p[b].end(), x)-p[b].begin();
    if(pos%2==0) return pos;
    reverse(p[b].begin()+1, p[b].end());
    return p[b].size()-pos;
}
void match(int u, int v){
    mat[u]=e[u][v].v;
    if(u<=n) return ;
    auto w=e[u][v];
    int x=frm[u][w.u], pos=rot(u, x);
    for(int i=0; i<=pos-1; ++i) match(p[u][i], p[u][i^1]);
    match(x, v);
    rotate(p[u].begin(), p[u].begin()+pos, p[u].end());
}
void aug(int u, int v){
    assert(u&&v);
    int t=rt[mat[u]];
    match(u, v);
    if(t) match(t, rt[fa[t]]), aug(rt[fa[t]], t);
}
int lca(int u, int v){
    ++tim;
    while(u||v){
        if(vis[u]==tim) return u;
        vis[u]=tim;
        u=rt[mat[u]];
        if(u) u=rt[fa[u]];
        if(!u) swap(u, v);
    }
    return 0;
}
int newn(){
    int x=n+1;
    while(x<=m&&rt[x]) ++x;
    if(x>m) ++m;
    p[x].clear(), lab[x]=mat[x]=rt[x]=col[x]=0;
    return x;
}
void blossom(int u, int v, int r){
    int x=newn();
    mat[x]=mat[r];
    p[x].pb(r);
    for(int i=u; i!=r; i=rt[fa[i]]){
        p[x].pb(i); p[x].pb(i=rt[mat[i]]);
        push(i);
    }
    reverse(p[x].begin()+1, p[x].end());
    for(int i=v; i!=r; i=rt[fa[i]]){
        p[x].pb(i); p[x].pb(i=rt[mat[i]]);
        push(i);
    }
    setrt(x, x);
    for(int i=1; i<=m; ++i) e[x][i].w=e[i][x].w=0, frm[x][i]=0;
    for(int t:p[x]){
        for(int i=1; i<=m; ++i){
            if(!e[x][i].w||d(e[t][i])<d(e[x][i])) e[x][i]=e[t][i], e[i][x]=e[i][t];
        }
        for(int i=1; i<=n; ++i) if(frm[t][i]) frm[x][i]=t;
    }
    updall(x);
}
void expand(int x){
    for(int u:p[x]) setrt(u, u);
    int u=frm[x][e[x][fa[x]].u], pos=rot(x, u);
    for(int i=0; i<pos; i+=2){
        int a=p[x][i], b=p[x][i+1];
        fa[a]=e[b][a].u;
        col[a]=1; col[b]=0;
        sl[a]=0;
        updall(b), push(b);
    }
    col[u]=1;
    fa[u]=fa[x];
    for(int i=pos+1; i<p[x].size(); ++i){
        col[p[x][i]]=-1; updall(p[x][i]);
    }
    rt[x]=0;
}
bool path(edge e){
    int u=rt[e.u], v=rt[e.v];
    assert(!d(e));
    if(col[v]==-1){
        fa[v]=e.u;
        col[v]=1;
        int t=rt[mat[v]];
        sl[v]=sl[t]=col[t]=0;
        push(t);
    }
    else if(!col[v]){
        int t=lca(u, v);
        if(!t) return aug(u, v), aug(v, u), 1;
        else blossom(u, v, t);
    }
    return 0;
}
bool bfs(){
    for(int i=0; i<=m; ++i) col[i]=-1, sl[i]=0;
    hd=1; tl=0;
    for(int i=1; i<=m; ++i) if(rt[i]==i&&!mat[i]) fa[i]=col[i]=0, push(i);
    if(!tl) return 0;
    while(1){
        while(hd<=tl){
            int u=q[hd++];
            for(int v=1; v<=n; ++v){
                if(e[u][v].w>0&&rt[u]!=rt[v]){
                    if(d(e[u][v])) upd(u, rt[v]);
                    else if(path(e[u][v])) return 1;
                }
            }
        }
        int tmp=inf;
        for(int i=1; i<=n; ++i) if(col[rt[i]]==0) tmp=min(tmp, lab[i]);
        for(int i=n+1; i<=m; ++i) if(rt[i]==i&&col[i]==1) tmp=min(tmp, lab[i]>>1);
        for(int i=1; i<=m; ++i) if(rt[i]==i&&sl[i]&&col[i]!=1) tmp=min(tmp, d(e[sl[i]][i])>>(col[i]+1));
        for(int i=1; i<=n; ++i){
            if(col[rt[i]]==0) lab[i]-=tmp;
            if(col[rt[i]]==1) lab[i]+=tmp;
            if(lab[i]<=0) return 0;
        }
        for(int i=n+1; i<=m; ++i){
            if(rt[i]==i){
                if(col[i]==0) lab[i]+=tmp*2;
                if(col[i]==1) lab[i]-=tmp*2;
            }
        }
        hd=1, tl=0;
        for(int i=1; i<=m; ++i) if(rt[i]==i&&sl[i]&&rt[sl[i]]!=i&&!d(e[sl[i]][i])&&path(e[sl[i]][i])) return 1;
        for(int i=n+1; i<=m; ++i) if(rt[i]==i&&col[i]==1&&!lab[i]) expand(i);
    }
}
signed main(){
	// freopen("D:\\nya\\acm\\A\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\A\\test.out","w",stdout);
    scanf("%lld", &n);
    m=n;
    for(int i=1; i<=n; ++i){
        scanf("%lld%lld", &pp[i].fi, &pp[i].se);
    }
    sort(pp+1, pp+n+1);
    for(int i=1; i<n*2; ++i){
        scanf("%lld", &a[i]); a[i]+=a[i-1];
    }
    for(int i=n*2; i>=1; --i) a[i]=a[i-1];
    ll sum=0;
    ll mx=0;
    for(int i=1; i<=n; ++i) for(int j=1; j<=n; ++j) e[i][j]=(edge){i, j, 0}, frm[i][j]=0;
    for(int i=1; i<=n; ++i){
        sum+=a[pp[i].se]-a[pp[i].fi];
        for(int j=i+1; j<=n; ++j){
            // cout<<i<<' '<<j<<' '<<cal(i, j)<<endl;
            mx=max(mx, cal(i, j));
            e[i][j].w=e[j][i].w=max(e[i][j].w, cal(i, j));
        }
    }
    for(int i=1; i<=n; ++i) frm[i][i]=i;
    for(int i=1; i<=n; ++i) lab[i]=mx, rt[i]=i, p[i].clear();
    while(bfs());
    ll totcost=0;
    for(int i=1; i<=n; ++i) if(mat[i]&&i<mat[i]) totcost+=e[i][mat[i]].w;
    // cout<<totcost<<endl;
    printf("%lld\n", sum-totcost);
}

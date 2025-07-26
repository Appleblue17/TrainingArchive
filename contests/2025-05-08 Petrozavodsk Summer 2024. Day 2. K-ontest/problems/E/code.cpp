#pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+5;
int n, m;
vector<int> e[N];
int fa[N], dep[N], dep2[N], sz[N], son[N], top[N];
inline void dfs(int x, int f){
    fa[x]=f; sz[x]=1; dep[x]=dep[f]+1;
    for(auto y:e[x]) if(y^f) {
        dep2[y]=dep2[x]+1-((x==1&&e[x].size()==1)||(x!=1&&e[x].size()==2));
        dfs(y, x);
        sz[x]+=sz[y];
        if(sz[y]>=sz[son[x]]) son[x]=y;
    }
}
int dfn[N], pos[N], timer;
inline void dfs2(int x, int tp){
    top[x]=tp; dfn[x]=++timer; pos[timer]=x;
    if(son[x]) dfs2(son[x], tp);
    for(auto y:e[x]) if((y^fa[x])&&(y^son[x])) dfs2(y, y);
}
inline int lca(int x, int y){
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]]) swap(x, y);
        x=fa[top[x]];
    }
    if(dep[x]<dep[y]) return x;
    else return y;
}
inline void opt(__int128 x){
    if(x==0){
        printf("0\n");
        return ;
    }
    vector<int> v;
    while(x) v.push_back(x%10), x/=10;
    while(!v.empty()) putchar(v.back()+'0'), v.pop_back();
    putchar('\n');
}
ll mx[N<<2], cnt[N<<2], tag[N<<2];
inline void down(int p){
    if(tag[p]!=0){
        cnt[p<<1]+=tag[p]; cnt[p<<1|1]+=tag[p];
        mx[p<<1]+=tag[p]; mx[p<<1|1]+=tag[p];
        tag[p<<1]+=tag[p]; tag[p<<1|1]+=tag[p];
        tag[p]=0;
    }
}
inline void up(int p){
    mx[p]=max(mx[p<<1], mx[p<<1|1]);
}
inline void add(int p, int l, int r, int L, int R, int x){
    if(L>R) return ;
    if(L<=l&&r<=R){
        cnt[p]+=x; mx[p]+=x; tag[p]+=x;
        return ;
    }
    int mid=(l+r)>>1;
    down(p);
    if(L<=mid) add(p<<1, l, mid, L, R, x);
    if(R>mid) add(p<<1|1, mid+1, r, L, R, x);
    up(p);
}
inline void mdf(int p, int l, int r, int x, ll z){
    if(l==r){
        mx[p]=cnt[p]-z;
        return ;
    }
    int mid=(l+r)>>1;
    down(p);
    if(x<=mid) mdf(p<<1, l, mid, x, z);
    else mdf(p<<1|1, mid+1, r, x, z);
    up(p);
}
__int128 summx=0;
ll cmx[N];
inline void fnd(int p, int l, int r, int L, int R){
    if(L>R) return ;
    if(mx[p]<=0) return ;
    if(l==r){
        int x=pos[l];
        if(cnt[p]>cmx[fa[x]]){
            summx+=cnt[p]-cmx[fa[x]];
            cmx[fa[x]]=cnt[p];
        }
        mx[p]=cmx[fa[x]]-cnt[p];
        return ;
    }
    int mid=(l+r)>>1;
    down(p);
    if(L<=mid) fnd(p<<1, l, mid, L, R);
    if(R>mid) fnd(p<<1|1, mid+1, r, L, R);
    up(p);
}
inline void upd(int x, int y, int z){
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]]) swap(x, y);
        add(1, 1, n, dfn[top[x]], dfn[x], z);
        fnd(1, 1, n, dfn[top[x]], dfn[x]);
        x=fa[top[x]];
    }
    if(dfn[x]>dfn[y]) swap(x, y);
    add(1, 1, n, dfn[x]+1, dfn[y], z);
    fnd(1, 1, n, dfn[x]+1, dfn[y]);
}
inline void build(int p, int l, int r){
    if(l==r){
        if(l==1) mx[p]=cnt[p]=-1e18;
        else if(fa[pos[l]]==1&&e[1].size()==1) mx[p]=cnt[p]=-1e18;
        else if(fa[pos[l]]!=1&&e[fa[pos[l]]].size()==2) mx[p]=cnt[p]=-1e18;
        return ;
    }
    int mid=(l+r)>>1;
    build(p<<1, l, mid); build(p<<1|1, mid+1, r);
    up(p);
}
int main(){
	// freopen("D:\\nya\\acm\\A\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\A\\test.out","w",stdout);
    scanf("%d%d", &n, &m);
    for(int i=1, x, y; i<n; ++i){
        scanf("%d%d", &x, &y);
        e[x].push_back(y); e[y].push_back(x);
    }
    dfs(1, 0);
    dfs2(1, 1);
    build(1, 1, n);
    __int128 sum=0;
    int x, y, k;
    while(m--){
        scanf("%d%d%d", &x, &y, &k);
        sum+=1ll*k*(dep2[x]+dep2[y]-2*dep2[lca(x, y)]);
        upd(x, y, k);
        opt(sum-summx);
    }
}

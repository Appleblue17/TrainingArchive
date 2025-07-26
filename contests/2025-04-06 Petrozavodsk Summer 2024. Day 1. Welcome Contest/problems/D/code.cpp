#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double dou;
typedef pair<int,int> pii;
#define fi first
#define se second
#define mapa make_pair
typedef long double ld;
typedef unsigned long long ull;
#define ep emplace_back
template <typename T>inline void read(T &x){
	x=0;char c=getchar();bool f=0;
	for(;c<'0'||c>'9';c=getchar()) f|=(c=='-');
	for(;c>='0'&&c<='9';c=getchar())
	x=(x<<1)+(x<<3)+(c^48);
	x=(f?-x:x);
}
const int N=1e5+5;
const ll inf=1e17;
int n, m, cnt;
char s[N];
int u[N], v[N], w[N];
vector<int> e[N];
int sz[N];
int cent, mn;
void dfs(int x, int fa){
    sz[x]=1;
    int mx=0;
    for(auto y:e[x]) if(y^fa){
        dfs(y, x);
        sz[x]+=sz[y];
        mx=max(mx, sz[y]);
    }
    mx=max(mx, n-sz[x]);
    if(mx<mn){
        mn=mx; cent=x;
    }
}
int ft[N], sz2[N];
int dfn[N], lp[N], rp[N], timer, pos[N];
void dfs2(int x, int fa){
    ft[x]=fa;
    sz[x]=1; sz2[x]=(s[x]=='B');
    dfn[x]=lp[x]=++timer; pos[timer]=x;
    for(auto y:e[x]) if(y^fa){
        dfs2(y, x);
        sz[x]+=sz[y]; sz2[x]+=sz2[y];
    }
    rp[x]=timer;
}
int bel[N];
void dfs3(int x, int fa, int rt){
    bel[x]=rt;
    for(auto y:e[x]) if(y^fa){
        dfs3(y, x, rt);
    }
}
bool flag[N];
ll tr[N<<2], tag[N<<2];
void build(int p, int l, int r){
    if(l==r){
        if(flag[pos[l]]) tr[p]=0;
        else tr[p]=inf;
        return ;
    }
    int mid=(l+r)>>1;
    build(p<<1, l, mid); build(p<<1|1, mid+1, r);
    tr[p]=min(tr[p<<1], tr[p<<1|1]);
}
inline void down(int p){
    tr[p<<1]+=tag[p]; tr[p<<1|1]+=tag[p];
    tag[p<<1]+=tag[p]; tag[p<<1|1]+=tag[p];
    tag[p]=0;
}
inline void mdf(int p, int l, int r, int L, int R, ll v){
    if(L>R) return ;
    if(L<=l&&r<=R){
        tr[p]+=v; tag[p]+=v;
        return ;
    }
    int mid=(l+r)>>1;
    down(p);
    if(L<=mid) mdf(p<<1, l, mid, L, R, v);
    if(R>mid) mdf(p<<1|1, mid+1, r, L, R, v);
    tr[p]=min(tr[p<<1], tr[p<<1|1]);
}
int main(){
	// freopen("D:\\nya\\acm\\A\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\A\\test.out","w",stdout);
	read(n);
    scanf("%s", s+1);
    for(int i=1; i<=n; ++i) cnt+=s[i]=='B';
    if(cnt>n-cnt){
        cnt=n-cnt;
        for(int i=1; i<=n; ++i) {
            if(s[i]=='B') s[i]='G';
            else s[i]='B';
        }
    }
    for(int i=1; i<n; ++i){
        read(u[i]); read(v[i]); read(w[i]);
        e[u[i]].ep(v[i]); e[v[i]].ep(u[i]);
    }
    read(m);
    if(cnt==0){
        while(m--) printf("0\n");
        return 0;
    }
    mn=1e9;
    dfs(1, 0);
    dfs2(cent, 0);
    vector<int> rt;
    for(int i=1; i<=n; ++i) if(sz[i]==cnt){
        rt.ep(i);
        dfs3(i, ft[i], i);
        flag[i]=1;
    }
    build(1, 1, n);
    for(int i=1; i<n; ++i){
        if(ft[v[i]]==u[i]) swap(u[i], v[i]);
        if(bel[u[i]]==bel[v[i]]&&bel[v[i]]!=0){
            int crt=bel[u[i]];
            mdf(1, 1, n, dfn[crt], dfn[crt], 1ll*w[i]*(sz[u[i]]-sz2[u[i]]));
            mdf(1, 1, n, 1, lp[crt]-1, 1ll*w[i]*sz2[u[i]]);
            mdf(1, 1, n, rp[crt]+1, n, 1ll*w[i]*sz2[u[i]]);
        }
        else{
            mdf(1, 1, n, lp[u[i]], rp[u[i]], 1ll*w[i]*(cnt-sz2[u[i]]));
            mdf(1, 1, n, 1, lp[u[i]]-1, 1ll*w[i]*sz2[u[i]]);
            mdf(1, 1, n, rp[u[i]]+1, n, 1ll*w[i]*sz2[u[i]]);
        }
    }
    while(m--){
        int i, c;
        read(i); read(c);
        if(bel[u[i]]==bel[v[i]]&&bel[v[i]]!=0){
            int crt=bel[u[i]];
            mdf(1, 1, n, dfn[crt], dfn[crt], 1ll*c*(sz[u[i]]-sz2[u[i]]));
            mdf(1, 1, n, 1, lp[crt]-1, 1ll*c*sz2[u[i]]);
            mdf(1, 1, n, rp[crt]+1, n, 1ll*c*sz2[u[i]]);
        }
        else{
            mdf(1, 1, n, lp[u[i]], rp[u[i]], 1ll*c*(cnt-sz2[u[i]]));
            mdf(1, 1, n, 1, lp[u[i]]-1, 1ll*c*sz2[u[i]]);
            mdf(1, 1, n, rp[u[i]]+1, n, 1ll*c*sz2[u[i]]);
        }
        w[i]+=c;
        printf("%lld\n", tr[1]);
    }
    return 0;
}


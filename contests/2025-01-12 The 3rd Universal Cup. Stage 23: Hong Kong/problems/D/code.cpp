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
typedef unsigned int uint;
#define ep emplace_back
template <typename T>inline void read(T &x){
	x=0;char c=getchar();bool f=0;
	for(;c<'0'||c>'9';c=getchar()) f|=(c=='-');
	for(;c>='0'&&c<='9';c=getchar())
	x=(x<<1)+(x<<3)+(c^48);
	x=(f?-x:x);
}
const int N=5e5+5;
const ll inf=1e9;
int n, m;
vector<int> e[N];
char s[2];
int dfn[N], top[N], timer, f[N], tsz[N], son[N], dep[N];
void dfs(int x, int fa){
	f[x]=fa; tsz[x]=1; dep[x]=dep[fa]+1;
	for(int y:e[x]) if(y^fa){
		dfs(y, x);
		tsz[x]+=tsz[y];
		if(tsz[y]>tsz[son[x]]) son[x]=y;
	}
}
void dfs2(int x, int tp){
	top[x]=tp;
	dfn[x]=++timer;
	if(son[x]) dfs2(son[x], tp);
	for(int y:e[x]) if(y!=f[x]&&y!=son[x]){
		dfs2(y, y);
	}
}
inline int lca(int x, int y){
	while(top[x]^top[y]){
		if(dep[top[x]]<dep[top[y]]) swap(x, y);
		x=f[top[x]];
	}
	return (dep[x]<dep[y])?x:y;
}
int ans[N];
vector<pii> ins[N], pop[N], qry[N];
struct mat{
	ll a00, a01, a10, a11;
	mat(ll _a00=0, ll _a01=inf, ll _a10=inf, ll _a11=0){a00=_a00; a01=_a01; a10=_a10; a11=_a11;}
}emp;
inline mat operator +(mat x, mat y){
	return (mat){x.a00+y.a00, x.a01+y.a01, x.a10+y.a10, x.a11+y.a11};
}
inline mat operator *(mat x, mat y){
	mat z;
	z.a00=min(x.a00+y.a00, x.a01+y.a10);
	z.a01=min(x.a00+y.a01, x.a01+y.a11);
	z.a10=min(x.a10+y.a00, x.a11+y.a10);
	z.a11=min(x.a10+y.a01, x.a11+y.a11);
	return z;
}
mat tr[N*50];
int sz[N*50], ls[N*50], rs[N*50];
int rt[N], idx;
inline void add(int &p, int l, int r, int x, ll v){
	if(!p) p=++idx;
	if(l==r){
		sz[p]++; 
		if(sz[p]==1) tr[p]=(mat){v, v/2, v, inf};
		else tr[p]=tr[p]+(mat){v, v/2, v, inf};
		return ;
	}
	int mid=(l+r)>>1;
	if(x<=mid) add(ls[p], l, mid, x, v);
	else add(rs[p], mid+1, r, x, v);
	tr[p]=tr[rs[p]]*tr[ls[p]];
	sz[p]=sz[rs[p]]+sz[ls[p]];
}
inline void del(int &p, int l, int r, int x, ll v){
	if(!p) p=++idx;
	if(l==r){
		sz[p]--; 
		if(sz[p]==0) tr[p]=emp;
		else tr[p]=tr[p]+(mat){-v, -v/2, -v, -inf};
		return ;
	}
	int mid=(l+r)>>1;
	if(x<=mid) del(ls[p], l, mid, x, v);
	else del(rs[p], mid+1, r, x, v);
	tr[p]=tr[rs[p]]*tr[ls[p]];
	sz[p]=sz[rs[p]]+sz[ls[p]];
}
inline int merge(int p, int q, int l, int r){
	if((!p)||(!q)) return p+q;
	if(l==r){
		sz[p]=sz[p]+sz[q];
		tr[p]=tr[p]+tr[q];
		return p;
	}
	int mid=(l+r)>>1;
	ls[p]=merge(ls[p], ls[q], l, mid);
	rs[p]=merge(rs[p], rs[q], mid+1, r);
	sz[p]=sz[ls[p]]+sz[rs[p]];
	tr[p]=tr[rs[p]]*tr[ls[p]];
	return p;
}
inline int get(int p, int l, int r, int L, int R, ll lim, mat &w){
	if(L<=l&&r<=R){
		mat tem=w*tr[p];
		if(min(tem.a00, tem.a01)<lim){
			w=tem; return 0;
		}
		if(l==r) return l;
		int mid=(l+r)>>1;
		tem=w*tr[rs[p]];
		if(min(tem.a00, tem.a01)<lim) {
			w=tem; return get(ls[p], l, mid, L, R, lim, w);
		}
		else{
			return get(rs[p], mid+1, r, L, R, lim, w);
		}
	}
	int mid=(l+r)>>1, ret=0;
	if(R>mid) ret=get(rs[p], mid+1, r, L, R, lim, w);
	if(ret==0&&L<=mid) ret=get(ls[p], l, mid, L, R, lim, w);
	return ret; 
}
inline int gets(int p, int l, int r, int L, int R){
	if(L<=l&&r<=R) return sz[p];
	int mid=(l+r)>>1, ret=0;
	if(L<=mid) ret+=gets(ls[p], l, mid, L, R);
	if(R>mid) ret+=gets(rs[p], mid+1, r, L, R);
	return ret;
}
inline void solve(int x){
	for(int y:e[x]) if(y^f[x]) {
		solve(y); rt[x]=merge(rt[x], rt[y], 1, m);
	}
	for(auto t:ins[x]){
		add(rt[x], 1, m, t.se, t.fi);
	}
	for(auto t:pop[x]){
		del(rt[x], 1, m, t.se, t.fi);
	}
	for(auto t:qry[x]){
		mat tem;
		tem.a00=tem.a01=0; tem.a10=tem.a11=inf;
		int pos=get(rt[x], 1, m, 1, t.se, t.fi, tem);
		ans[t.se]=gets(rt[x], 1, m, pos+1, t.se);
	}

}
int main(){
	// freopen("D:\\nya\\acm\\B\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\B\\test2.out","w",stdout);
	read(n); read(m);
	for(int i=1, x, y; i<n; ++i){
		read(x); read(y);
		e[x].ep(y); e[y].ep(x);
	}
	dfs(1, 0); dfs2(1, 1);
	for(int i=1; i<=m; ++i){
		scanf("%s", s+1);
		if(s[1]=='A'){
			ans[i]=-1;
			int x, y, z;
			read(x); read(y); read(z); z<<=1;
			ins[x].ep(z, i);
			ins[y].ep(z, i);
			pop[x=lca(x, y)].ep(z, i);
			pop[f[x]].ep(z, i);
		}
		else{
			int x, h;
			read(x); read(h); h<<=1;
			qry[x].ep(h, i);
		}
	}
	solve(1);
	for(int i=1; i<=m; ++i) if(ans[i]!=-1) printf("%d\n", ans[i]);
	return 0;
}

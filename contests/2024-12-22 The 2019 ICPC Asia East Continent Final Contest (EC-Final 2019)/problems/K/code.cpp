#pragma GCC optimize(3)
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
const int N=6e5+5;
const int mod=998244353;
const int inf=1e9;
int n, m;
int u[N], v[N]; ll w[N];
set<pair<ll, int> > s;
set<pii> e[N];
bool ban[N];
void dfs(int x, int fa, int ed, ll add){
	if(x==ed) return ;
	int y=0, id=0;
	if(e[x].upper_bound(mapa(fa, inf))!=e[x].end()){
		y=(*e[x].upper_bound(mapa(fa, inf))).fi;
		id=(*e[x].upper_bound(mapa(fa, inf))).se;
	}
	else{
		y=(*e[x].begin()).fi;
		id=(*e[x].begin()).se;
	}
	if(s.find(mapa(w[id], id))==s.end()){
		w[id]+=add;
		if(u[id]!=x) swap(u[id], v[id]);
		s.insert(mapa(w[id], id));
	}
	else{
		e[u[id]].erase(e[u[id]].find(mapa(v[id], id)));
		e[v[id]].erase(e[v[id]].find(mapa(u[id], id)));
		s.erase(mapa(w[id], id));
		w[id]+=add;
	}
	dfs(y, x, ed, add);
}
inline void work(int x){
	ban[x]=1;
	s.erase(s.find(mapa(w[x], x)));
	e[u[x]].erase(e[u[x]].find(mapa(v[x], x)));
	e[v[x]].erase(e[v[x]].find(mapa(u[x], x)));
	dfs(u[x], v[x], v[x], w[x]);
}
int edg[N], tot;
inline bool cmp(int x, int y){
	return w[x]>w[y];
}
int fa[N], sz[N];
inline int get(int x){
	while(x!=fa[x]) x=fa[x]=fa[fa[x]];
	return x;
}
int main(){
	// freopen("D:\\nya\\acm\\A\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\A\\test.out","w",stdout);
	read(n); read(m);
	for(int i=1; i<=m; ++i){
		read(u[i]); read(v[i]); read(w[i]);
		if(u[i]>v[i]) swap(u[i], v[i]);
		if(u[i]+1==v[i]||(u[i]==1&&v[i]==n)) s.insert(mapa(w[i], i));
		if(u[i]==1&&v[i]==n) swap(u[i], v[i]);
		e[u[i]].insert(mapa(v[i], i));
		e[v[i]].insert(mapa(u[i], i));
	}
	for(int i=1; i<=m-n+1; ++i) work((*s.begin()).se);
	for(int i=1; i<=m; ++i) if(!ban[i]){
		edg[++tot]=i;
	}
	sort(edg+1, edg+tot+1, cmp);
	for(int i=1; i<=n; ++i) fa[i]=i, sz[i]=1;
	int ans=0;
	for(int i=1; i<=tot; ++i){
		int x=u[edg[i]], y=v[edg[i]];
		x=get(x); y=get(y);
		ans=(ans+w[edg[i]]%mod*sz[x]%mod*sz[y]%mod)%mod;
		fa[x]=y; sz[y]+=sz[x];
	}
	printf("%d\n", ans);
	return 0;
}


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
const int N=5e5+5;
int n, m, q, mod;
vector<int> e[N];
int fa[N];
bool inc[N];
inline int get(int x){
	if(x==fa[x]) return x;
	return fa[x]=get(fa[x]);
}
inline void merge(int x, int y){
	x=get(x); y=get(y);
	if(x==y) return ;
	fa[x]=y;
}
inline void dfs(int x, int rt){
	inc[x]=1;
	for(auto y:e[x]) {
		merge(y, rt);
		if(!inc[y]) dfs(y, rt);
	}
}
vector<int> clique[N];
int bel[N];
vector<int> g[N];
int dfn[N], out[N], timer;
int deg[N];
int top[N];
inline void dfs2(int x, int tp){
	dfn[x]=++timer; top[x]=tp;
	for(auto y:g[x]) if(!dfn[y]) dfs2(y, tp);
	out[x]=timer;
}
int pw[N];
unordered_map<ll, bool> h, h2;
inline ll hs(int x, int y){return 1000000000ll*x+y;}
int indeg[N], incir[N];
int fa2[N];
inline int get2(int x){
	if(x==fa2[x]) return x;
	return fa2[x]=get2(fa2[x]);
}
inline void merge2(int x, int y){
	x=get2(x); y=get2(y);
	if(x==y) return ;
	fa2[y]=x;
}
vector<int> cir[N];
int main(){
	// freopen("D:\\nya\\acm\\B\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\B\\test.out","w",stdout);
	read(n); read(m); read(q); read(mod);
	pw[0]=1;
	for(int i=1; i<=n; ++i) pw[i]=((ll)pw[i-1]*i+1)%mod;
	for(int i=1, x, y; i<=m; ++i){
		read(x); read(y); ++x; ++y;
		e[x].ep(y);
		h[hs(x, y)]=1;
	}
	for(int i=1; i<=n; ++i) fa[i]=i;
	for(int i=1; i<=n; ++i) if(e[i].size()>=2&&!inc[i]){
		for(auto t:e[i]) merge(t, e[i][0]), dfs(t, e[i][0]);
	}
	for(int i=1; i<=n; ++i) clique[get(i)].ep(i);
	for(int i=1; i<=n; ++i) if(i==get(i)){
		for(auto t:clique[i]) bel[t]=i;
	}
	for(int i=1; i<=n; ++i){
		for(auto j:e[i]) if(bel[i]^bel[j]){
			if(h2.find(hs(bel[j], bel[i]))==h2.end()){
				g[bel[j]].ep(bel[i]); ++deg[bel[i]]; ++indeg[bel[j]];
				h2[hs(bel[j], bel[i])]=1;
			}
		}
	}
	for(int i=1; i<=n; ++i) if(i==get(i)){
		if(!deg[i]) {
			dfn[i]=++timer;
			for(auto j:g[i]) if(!dfn[j]) dfs2(j, j);
			out[i]=timer;
		}
	}
	queue<int> que;
	for(int i=1; i<=n; ++i) if(!dfn[i]){
		incir[i]=1;
		if(!indeg[i]) que.push(i);
	}
	while(!que.empty()){
		int x=que.front(); que.pop(); incir[x]=0;
		for(auto y:e[x]) if(!(--indeg[y])) que.push(y);
	}
	for(int i=1; i<=n; ++i) fa2[i]=i;
	for(int i=1; i<=n; ++i) if(incir[i]) {
		for(auto j:g[i]) if(incir[j]) merge2(i, j);
	}
	for(int i=1; i<=n; ++i) if(incir[i]) cir[get2(i)].ep(i);
	for(int i=1; i<=n; ++i) if(incir[i]&&get2(i)==i){
		++timer; int cur=timer;
		for(auto t:cir[i]) {
			dfn[t]=cur;
			for(auto tt:g[t]) if(!incir[tt]&&!dfn[tt]) {
				dfs2(tt, tt);
			}
		}
		for(auto t:cir[i]) out[t]=timer;
	}
	while(q--){
		int x, y; read(x); read(y); ++x; ++y;
		if(x==y){
			printf("%d\n", 1%mod);
			continue;
		}
		int fx=get(x), fy=get(y);
		if(dfn[fx]<dfn[fy]||dfn[fx]>out[fy]){
			printf("0\n");
			continue;
		}
		if(incir[fy]){
			printf("%d\n", 1%mod);
			continue;
		}
		if(fx==fy){
			printf("%d\n", pw[clique[fx].size()-2]);
			continue;
		}
		if(clique[fy].size()==1){
			printf("%d\n", 1%mod);
			continue;
		}
		fx=top[fx];
		int sz=e[fx].size();
		int op=h.find(hs(fx, y))!=h.end();
		sz-=op;
		printf("%lld\n", ((ll)sz*pw[clique[fy].size()-2]%mod+op)%mod);
	}
	return 0;
}

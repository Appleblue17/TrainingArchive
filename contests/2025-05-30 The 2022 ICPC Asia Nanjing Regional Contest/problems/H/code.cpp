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
mt19937 rnd(100000193);
int n, m;
vector<pii> e[N];
int w[N];
struct node{
	int ls, rs;
	int siz, pri;
	ll val;
	ll tagfi, tagdt;
}tr[N*20];
int rt[N];
int idx;
void apply(int x, ll mfi, ll mdt){
	tr[x].val+=mdt*tr[tr[x].ls].siz+mfi;
	tr[x].tagfi+=mfi; tr[x].tagdt+=mdt;
}
void down(int rt){
	if(tr[rt].rs) apply(tr[rt].rs, tr[rt].tagfi+tr[rt].tagdt*(tr[tr[rt].ls].siz+1), tr[rt].tagdt);
	if(tr[rt].ls) apply(tr[rt].ls, tr[rt].tagfi, tr[rt].tagdt);
	tr[rt].tagfi=0; tr[rt].tagdt=0;
}
void push_up(int rt){
	tr[rt].siz=1+tr[tr[rt].ls].siz+tr[tr[rt].rs].siz;
	return ;
}
int Merge(int x, int y){
	if(x==0||y==0) return x+y;
	down(x); down(y);
	if(tr[x].pri<tr[y].pri){
		tr[x].rs=Merge(tr[x].rs, y);
		push_up(x);
		return x;
	}
	tr[y].ls=Merge(x, tr[y].ls);
	push_up(y);
	return y;
}
void Split(int rt, ll v, int &x, int &y){
	if(rt==0){
		x=y=0;
		return ;
	}
	down(rt);
	if(tr[rt].val>=v){
		x=rt;
		Split(tr[rt].rs, v, tr[x].rs, y);
		push_up(x);
	}
	else{
		y=rt;
		Split(tr[rt].ls, v, x, tr[y].ls);
		push_up(y);
	}
}
int add_node(int rt, ll v){
	++idx;
	tr[idx].siz=1; tr[idx].pri=rnd();
	tr[idx].val=v;
	int A=0, B=0;
	Split(rt, v, A, B);
	return Merge(Merge(A, idx), B);
}
void dfs2(int rt, int &crt){
	if(rt==0) return ;
	down(rt);
	crt=add_node(crt, tr[rt].val);
	dfs2(tr[rt].ls, crt);
	dfs2(tr[rt].rs, crt);
}
void dfs(int x, int fa){
	vector<int> son;
	int mx=0;
	for(auto edg:e[x]) {
		int y=edg.fi;
		if(y==fa) continue;
		w[y]=edg.se;
		dfs(y, x);
		son.ep(y);
		if(tr[rt[y]].siz>tr[rt[mx]].siz) mx=y;
		apply(rt[y], (m-1)*w[y], -2*w[y]);
	}
	if(son.empty()){
		rt[x]=++idx;
		tr[idx].siz=1; tr[idx].pri=rnd();
		return ;
	}
	rt[x]=rt[mx];
	rt[x]=add_node(rt[x], 0ll);
	for(auto y:son){
		if(y==mx) continue;
		dfs2(rt[y], rt[x]);
	}
}
vector<ll> res;
void dfs3(int rt){
	if(rt==0) return ;
	down(rt);
	res.ep(tr[rt].val);
	dfs3(tr[rt].ls); dfs3(tr[rt].rs);
}
int main(){
	// freopen("D:\\nya\\acm\\A\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\A\\test.out","w",stdout);
	read(n); read(m);
	for(int i=1, x, y, w; i<n; ++i){
		read(x); read(y); read(w);
		e[x].ep(y, w);
		e[y].ep(x, w);
	}
	dfs(1, 0);
	ll ans=0;
	dfs3(rt[1]);
	sort(res.begin(), res.end(), greater<ll>());
	for(int i=0; i<m; ++i) ans+=res[i];
	printf("%lld\n", ans);
	return 0;
}


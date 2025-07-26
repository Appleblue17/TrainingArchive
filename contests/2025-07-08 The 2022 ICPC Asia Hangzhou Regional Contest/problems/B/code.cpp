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
const int N=1e6+5, M=(1<<17)+5;
const ll inf=1e15;
int n, m, q, bd;
ll w[17];
int c[N]; ll d[N];
ll ans;
struct myheap{
	priority_queue<ll> p, q;
	void push(ll x){
		p.push(x);
	}
	void pop(ll x){
		q.push(x);
	}
	ll top(){
		while(!q.empty()&&p.top()==q.top()){
			p.pop(); q.pop();
		}
		return p.top();
	}
};
struct DS{
	ll g[M<<2], f[M<<2], res[M<<2];
	void up(int p){
		res[p]=max(max(res[p<<1], res[p<<1|1]), f[p<<1]+g[p<<1|1]);
		f[p]=max(f[p<<1], f[p<<1|1]);
		g[p]=max(g[p<<1], g[p<<1|1]);
	}
	void mdff(int p, int l, int r, int x, ll v){
		if(l==r){
			f[p]=v; res[p]=f[p]+g[p];
			return ;
		}
		int mid=(l+r)>>1;
		if(x<=mid) mdff(p<<1, l, mid, x, v);
		else mdff(p<<1|1, mid+1, r, x, v);
		up(p);
	}
	void mdfg(int p, int l, int r, int x, ll v){
		if(l==r){
			g[p]=v; res[p]=f[p]+g[p];
			return ;
		}
		int mid=(l+r)>>1;
		if(x<=mid) mdfg(p<<1, l, mid, x, v);
		else mdfg(p<<1|1, mid+1, r, x, v);
		up(p);
	}
	void build(int p, int l, int r){
		g[p]=f[p]=res[p]=-inf;
		if(l==r){
			return ;
		}
		int mid=(l+r)>>1;
		build(p<<1, l, mid); build(p<<1|1, mid+1, r);
	}
	myheap mxd[M], mxd2[M];
	void add(int x, int y, ll v){
		if(x==0) return ;
		mxd[x].push(v);
		mdfg(1, 0, bd, x, mxd[x].top());
		mxd2[y].push(v);
		mdff(1, 0, bd, y, mxd2[y].top());
	}
	void del(int x, int y, ll v){
		if(x==0) return ;
		mxd[x].pop(v);
		mdfg(1, 0, bd, x, mxd[x].top());
		mxd2[y].pop(v);
		mdff(1, 0, bd, y, mxd2[y].top());
	}
}t[17];
void calc(){
	ans=0;
	for(int i=1; i<=m; ++i) {
		if(t[i].res[1]<0) continue;
		ans=max(ans, w[i]*t[i].res[1]);
	}
	printf("%lld\n", ans);
}
int main(){
	// freopen("D:\\nya\\acm\\A\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\A\\test.out","w",stdout);
	read(n); read(m); read(q); bd=(1<<m)-1;
	for(int i=1; i<=m; ++i) {
		read(w[i]), t[i].build(1, 0, bd); 
		for(int j=0; j<(1<<i); ++j) t[i].mxd[j].push(-inf), t[i].mxd2[j].push(-inf);
	}
	for(int i=1; i<=n; ++i) read(c[i]); 
	for(int i=1; i<=n; ++i) read(d[i]);
	for(int i=1; i<=n; ++i){
		for(int j=1; j<=m; ++j){
			int cc=c[i]&((1<<j)-1);
			t[j].add(cc, (1<<j)-cc, d[i]);
		}
	}
	calc();
	while(q--){
		ull x, u, v;
		read(x); read(u); read(v);
		x^=ans; u^=ans; v^=ans;
		for(int j=1; j<=m; ++j){
			int cc=c[x]&((1<<j)-1);
			t[j].del(cc, (1<<j)-cc, d[x]);
		}
		c[x]=u; d[x]=v;
		for(int j=1; j<=m; ++j){
			int cc=c[x]&((1<<j)-1);
			t[j].add(cc, (1<<j)-cc, d[x]);
		}
		calc();
	}
	return 0;
}


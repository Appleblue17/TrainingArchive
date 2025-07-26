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
const int N=3e5+5;
int n, m;
int a[N];
struct sgt{
	vector<pii> tr;
	inline void upd(int p){
		tr[p].fi=max(tr[p<<1].fi, tr[p<<1|1].fi);
		if(tr[p].fi==tr[p<<1].fi) tr[p].se=tr[p<<1].se;
		else tr[p].se=tr[p<<1|1].se;
	}
	inline void ins(int p, int l, int r, int x, int v){
		if(l==r){
			tr[p]=mapa(a[v], v);
			return ;
		}
		int mid=(l+r)>>1;
		if(x<=mid) ins(p<<1, l, mid, x, v);
		else ins(p<<1|1, mid+1, r, x, v);
		upd(p);
	}
	inline void del(int p, int l, int r, int x){
		if(l==r){
			tr[p].fi=0;
			return ;
		}
		int mid=(l+r)>>1;
		if(x<=mid) del(p<<1, l, mid, x);
		else del(p<<1|1, mid+1, r, x);
		upd(p);
	}
};
sgt tree[N];
int lim;
int main(){
	// freopen("D:\\nya\\acm\\A\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\A\\test.out","w",stdout);
	read(n); read(m);
	lim=n/m+5;
	for(int i=1; i<=n; ++i) read(a[i]);
	for(int i=0; i<m; ++i) tree[i].tr.resize(lim<<2);
	for(int i=1; i<=n; ++i) tree[i%m].ins(1, 1, lim, (i-1)/m+1, i);
	vector<int> vec;
	for(int i=1; i<=n;){
		int mx=tree[i%m].tr[1].fi, pos=tree[i%m].tr[1].se;
		vec.ep(mx);
		for(int j=i; j<=pos; ++j) tree[j%m].del(1, 1, lim, (j-1)/m+1);
		i=pos+1;
	}
	for(auto t:vec) printf("%d ", t);
	return 0;
}

#pragma GCC optimize(2)
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
int n, m;
int w[N], p[N];
int a[N], b[N], c[N];
struct TandT{
	int rt[N], tr[N*120], ls[N*120], rs[N*120], idx;
	inline void addp(int &p, int l, int r, int x){
		if(!p) p=++idx;
		++tr[p];
		if(l==r) return ;
		int mid=(l+r)>>1;
		if(x<=mid) addp(ls[p], l, mid, x);
		else addp(rs[p], mid+1, r, x);
	}
	inline void add(int x, int y){
		for(; x<=n; x+=(x&-x)){
			addp(rt[x], 1, n, y);
		}
	}
	inline int getp(int p, int l, int r, int L, int R){
		if(!p) return 0;
		if(L<=l&&r<=R) return tr[p];
		int mid=(l+r)>>1, ret=0;
		if(L<=mid) ret=getp(ls[p], l, mid, L, R);
		if(R>mid) ret+=getp(rs[p], mid+1, r, L, R);
		return ret;
	}
	inline int get(int l1, int r1, int l2, int r2){
		if(l2>r2||l1>r1) return 0;
		int ret=0;
		for(; r1; r1-=(r1&-r1)) ret+=getp(rt[r1], 1, n, l2, r2);
		for(--l1; l1; l1-=(l1&-l1)) ret-=getp(rt[l1], 1, n, l2, r2);
		return ret;
	}
}t1, t2, t3, t4, t5;
int main(){
	// freopen("D:\\nya\\acm\\A\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\A\\test.out","w",stdout);
	read(n);
	for(int i=1; i<=n; ++i){
		read(p[i]); w[p[i]]=i; 
	}
	for(int i=1; i<=n; ++i) t1.add(i, w[i]);
	ll sum=0;
	for(int i=1; i<=n; ++i){
		a[i]=t1.get(1, i-1, 1, w[i]);
		b[i]=i-1-a[i];
		c[i]=min(a[i], b[i]);
		if(a[i]<=b[i]) t2.add(i, w[i]);
		if(a[i]>=b[i]) t3.add(i, w[i]);
		if(a[i]+1<=b[i]-1) t4.add(i, w[i]);
		if(b[i]+1<=a[i]-1) t5.add(i, w[i]);
		sum+=c[i];
	}
	read(m);
	while(m--){
		int x, y;
		read(x); read(y);
		x=p[x]; y=p[y];
		if(x>y) swap(x, y);
		if(x==y){
			printf("%lld\n", sum);
		}
		else{
			ll ans=sum;
			ans-=c[x]; ans-=c[y];
			int ax=t1.get(1, y-1, 1, w[x]-1)+(w[y]<w[x]);
			int bx=y-1-ax;
			int ay=t1.get(1, x-1, 1, w[y]-1);
			int by=x-1-ay;
			ans+=min(ax, bx);
			ans+=min(ay, by);
			if(w[y]<w[x]){
				ans-=t3.get(x+1, y-1, w[y], w[x]);
				ans+=t4.get(x+1, y-1, w[y], w[x]);
			}
			else{
				ans-=t2.get(x+1, y-1, w[x], w[y]);
				ans+=t5.get(x+1, y-1, w[x], w[y]);
			}
			printf("%lld\n", ans);
		}
	}
	return 0;
}


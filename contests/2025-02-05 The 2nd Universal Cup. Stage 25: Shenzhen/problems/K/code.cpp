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
inline int fpow(ll x, int y, int mod){
	ll ret=1;
	while(y){
		if(y&1) ret=ret*x%mod;
		x=x*x%mod; y>>=1;
	}
	return ret;
}
const int N=2e5+5, m1=1e9+7, m2=998244353;
int n1, n2, m;
struct node{
    int x, y;
};
node bs=(node){131, 137};
inline node operator +(node x, node y){
    return (node){(x.x+y.x)%m1, (x.y+y.y)%m2};
}
inline node operator -(node x, node y){
    return (node){(x.x-y.x+m1)%m1, (x.y-y.y+m2)%m2};
}
inline node operator *(node x, node y){
    return (node){(int)(1ll*x.x*y.x%m1), (int)(1ll*x.y*y.y%m2)};
}
inline bool operator !=(node x, node y){
    return x.x!=y.x||x.y!=y.y;
}
inline bool operator ==(node x, node y){
	return (x.x==y.x)&&(x.y==y.y);
}
node pw[N], ipw[N];
struct sgt{
	int sz[N<<2]; node hs[N<<2]; int mx[N<<2], mn[N<<2];
	pair<node, int> find(int p, int l, int r, int x){
		if(l==r){
			if(mx[p]>=x) return mapa(hs[p], 1);
			else return mapa((node){0, 0}, 0); 
		}
		if(mn[p]>=x) return mapa(hs[p], sz[p]);
		int mid=(l+r)>>1;
		if(mx[p<<1|1]>=x){
			node reths=(hs[p]-hs[p<<1|1])*ipw[sz[p<<1|1]];
			int retsz=sz[p]-sz[p<<1|1];
			pair<node, int> rs_info=find(p<<1|1, mid+1, r, x);
			return mapa(reths*pw[rs_info.se]+rs_info.fi, retsz+rs_info.se);
		}
		else{
			return find(p<<1, l, mid, x);
		}
	}
	void up(int p, int l, int r){
		mx[p]=max(mx[p<<1], mx[p<<1|1]);
		mn[p]=mn[p<<1|1];
		hs[p]=hs[p<<1|1];
		int mid=(l+r)>>1;
		pair<node, int> tem=find(p<<1, l, mid, mx[p<<1|1]);
		sz[p]=tem.se+sz[p<<1|1];
		hs[p]=tem.fi*pw[sz[p<<1|1]]+hs[p<<1|1];
	}
	void build(int p, int l, int r){
		if(l==r){
			read(mx[p]); mn[p]=mx[p];
			sz[p]=1;
			hs[p]=(node){mx[p], mn[p]};
			return ;
		}
		int mid=(l+r)>>1;
		build(p<<1, l, mid); build(p<<1|1, mid+1, r);
		up(p, l, r);
	}
	void mdf(int p, int l, int r, int x, int v){
		if(l==r){
			mx[p]=mn[p]=v;
			hs[p]=(node){v, v};
			return ;
		}
		int mid=(l+r)>>1;
		if(x<=mid) mdf(p<<1, l, mid, x, v);
		else mdf(p<<1|1, mid+1, r, x, v);
		up(p, l, r);
	}
}T1, T2;
int main(){
	// freopen("D:\\nya\\acm\\A\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\A\\test.out","w",stdout);
	pw[0]=(node){1, 1};
	for(int i=1; i<N; ++i) pw[i]=pw[i-1]*bs;
	ipw[0]=(node){1, 1};
	ipw[1]=(node){fpow(bs.x, m1-2, m1), fpow(bs.y, m2-2, m2)};
	for(int i=2; i<N; ++i) ipw[i]=ipw[i-1]*ipw[1];
	read(n1);
	T1.build(1, 1, n1);
	read(n2);
	T2.build(1, 1, n2); 
	read(m);
	while(m--){
		int op, x, v;
		read(op); read(x); read(v);
		if(op==1) T1.mdf(1, 1, n1, x, v);
		else T2.mdf(1, 1, n2, x, v);
		// printf("%d %d %d %d\n", T1.hs[1].x, T1.hs[1].y, T2.hs[1].x, T2.hs[1].y);
		// printf("%d %d\n", T1.sz[1], T2.sz[1]);
		if(T1.hs[1]==T2.hs[1]&&T1.sz[1]==T2.sz[1]) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}


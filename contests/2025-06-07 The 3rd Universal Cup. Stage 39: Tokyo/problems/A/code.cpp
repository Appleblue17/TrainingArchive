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
int n, m, a[N];
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
	int sz[N<<2]; node hs[N<<2], hs2[N<<2]; int mx[N<<2], mn[N<<2];
	pair<pair<node, node>, int> find(int p, int l, int r, int x){
		if(l==r){
			if(mx[p]>=x) return mapa(mapa(hs[p], hs2[p]), 1);
			else return mapa(mapa((node){0, 0}, (node){0, 0}), 0); 
		}
		if(mn[p]>=x) return mapa(mapa(hs[p], hs2[p]), sz[p]);
		int mid=(l+r)>>1;
		if(mx[p<<1|1]>=x){
			node reths=(hs[p]-hs[p<<1|1])*ipw[sz[p<<1|1]];
			node reths2=(hs2[p]-hs2[p<<1|1])*ipw[sz[p<<1|1]];
			int retsz=sz[p]-sz[p<<1|1];
			pair<pair<node, node>, int> rs_info=find(p<<1|1, mid+1, r, x);
			return mapa(mapa(reths*pw[rs_info.se]+rs_info.fi.fi, reths2*pw[rs_info.se]+rs_info.fi.se), retsz+rs_info.se);
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
		pair<pair<node, node>, int> tem=find(p<<1, l, mid, mx[p<<1|1]);
		sz[p]=tem.se+sz[p<<1|1];
		hs[p]=tem.fi.fi*pw[sz[p<<1|1]]+hs[p<<1|1];
		hs2[p]=tem.fi.se*pw[sz[p<<1|1]]+hs2[p<<1|1];
	}
	void get(int p, int l, int r, int L, int R, node &prehs, node &prehs2, int &premx, int &presz){
		if(L<=l&&r<=R){
			if(premx==0){
				premx=mx[p];
				prehs=hs[p];
				prehs2=hs2[p];
				presz=sz[p];
				return ;
			}
			pair<pair<node, node>, int> tem=find(p, l, r, premx);
			prehs=tem.fi.fi*pw[presz]+prehs;
			prehs2=tem.fi.se*pw[presz]+prehs2;
			presz=tem.se+presz;
			premx=max(premx, mx[p]);
			return ;
		}
		int mid=(l+r)>>1;
		if(R>mid) get(p<<1|1, mid+1, r, L, R, prehs, prehs2, premx, presz);
		if(L<=mid) get(p<<1, l, mid, L, R, prehs, prehs2, premx, presz);
	}
	void build(int p, int l, int r){
		if(l==r){
			mn[p]=mx[p]=a[l];
			sz[p]=1;
			hs[p]=(node){l, l};
			hs2[p]=(node){1, 1};
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
}T;
int main(){
	// freopen("D:\\nya\\acm\\A\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\A\\test.out","w",stdout);
	pw[0]=(node){1, 1};
	for(int i=1; i<N; ++i) pw[i]=pw[i-1]*bs;
	ipw[0]=(node){1, 1};
	ipw[1]=(node){fpow(bs.x, m1-2, m1), fpow(bs.y, m2-2, m2)};
	for(int i=2; i<N; ++i) ipw[i]=ipw[i-1]*ipw[1];
	read(n); read(m);
	for(int i=1; i<=n; ++i) read(a[i]);
	reverse(a+1, a+n+1);
	T.build(1, 1, n);
	while(m--){
		int l1, r1, l2, r2;
		read(l1); read(r1); read(l2); read(r2);
		r1=n-r1+1; l1=n-l1+1; r2=n-r2+1; l2=n-l2+1;
		swap(l1, r1); swap(l2, r2);
		node prehs=(node){0, 0}, prehs2=(node){0, 0}; int premx=0, presz=0;
		T.get(1, 1, n, l1, r1, prehs, prehs2, premx, presz);
		node tem1=prehs;
		tem1=tem1-(prehs2*(node){l1-1, l1-1});
		prehs=(node){0, 0}, prehs2=(node){0, 0}; premx=0, presz=0;
		T.get(1, 1, n, l2, r2, prehs, prehs2, premx, presz);
		node tem2=prehs;
		tem2=tem2-(prehs2*(node){l2-1, l2-1});
		if(tem1==tem2){
			printf("Yes\n");
		}
		else{
			printf("No\n");
		}
	}
	return 0;
}


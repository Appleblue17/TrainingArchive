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
const int N=1e6+5;
int n;
int a[N];
int lp[N], rp[N];
mt19937_64 rnd(time(0));
ull hs[N], pre[N];
unordered_map<ull, int> h;
int f[N], g[N];
int mx[N][20], mn[N][20], lg[N];
inline int gmx(int l, int r){
	int t=lg[r-l+1];
	return max(mx[l][t], mx[r-(1<<t)+1][t]); 
}
inline int gmn(int l, int r){
	int t=lg[r-l+1];
	return min(mn[l][t], mn[r-(1<<t)+1][t]); 
}
inline int gmx(int l, int r, int x){
	return max(gmx(l, x-1), gmx(x+1, r));
}
inline int gmn(int l, int r, int x){
	return min(gmn(l, x-1), gmn(x+1, r));
}
int lpos[N], rpos[N];
int main(){
	// freopen("D:\\nya\\acm\\A\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\A\\test.out","w",stdout);
	read(n);
	for(int i=1; i<=n; ++i) hs[i]=rnd();
	for(int i=0; i<=2*n+1; ++i) f[i]=g[i]=1;
	h[0]=0;
	for(int i=1; i<=n*2; ++i) {
		read(a[i]);
		pre[i]=pre[i-1]^hs[a[i]];
		if(h.find(pre[i])!=h.end()) f[i]=1+f[h[pre[i]]];
		h[pre[i]]=i;
		if(lp[a[i]]==0) lp[a[i]]=i;
		else rp[a[i]]=i;
	}
	h.clear();
	h[pre[2*n]]=2*n+1;
	for(int i=n*2; i>=1; --i){
		if(h.find(pre[i-1])!=h.end()) g[i]=1+g[h[pre[i-1]]];
		h[pre[i-1]]=i;
	}
	h.clear();
	for(int i=1; i<=n*2; ++i){
		if(h.find(pre[i])==h.end()){
			lpos[i]=i-1;
			h[pre[i]]=i-1;
		}
		else lpos[i]=h[pre[i]];
	} 
	h.clear();
	for(int i=n*2; i>=1; --i){
		if(h.find(pre[i])==h.end()){
			rpos[i]=i+1;
			h[pre[i]]=i+1;
		}
		else rpos[i]=h[pre[i]];
	} 
	for(int i=2; i<=n*2; ++i) lg[i]=lg[i>>1]+1;
	for(int i=1; i<=n*2; ++i) mx[i][0]=rp[a[i]], mn[i][0]=lp[a[i]];
	for(int i=1; i<=lg[n*2]; ++i){
		for(int j=1; j+(1<<i)-1<=n*2; ++j){
			mx[j][i]=max(mx[j][i-1], mx[j+(1<<(i-1))][i-1]);
			mn[j][i]=min(mn[j][i-1], mn[j+(1<<(i-1))][i-1]);
		}
	}
	for(int i=1; i<=n*2; ++i){
		ll ans=(ll)f[i-1]*g[i+1];
		int l=lpos[i], r=rpos[i], lstr=i, lstl=i;
		while(true){
			if(l<=0||r>=2*n+1) break;
			if(l<=lp[a[i]]&&rp[a[i]]<=r) break;
			while(l>gmn(l, r, i)||r<gmx(l, r, i)) {
				if(l>gmn(l, r, i)) l=gmn(l, r, i);
				if(r<gmx(l, r, i)) r=gmx(l, r, i);
				if(l<=lp[a[i]]&&rp[a[i]]<=r) break;
			}
			if(l<=lp[a[i]]&&rp[a[i]]<=r) break;
			if(pre[r]==pre[lstr]||pre[l]==pre[lstl]){
				l=lpos[l]; r=rpos[r]; continue;
			} 
			lstr=r;
			ans+=(ll)f[l-1]*g[r+1];
			l=lpos[l]; r=rpos[r];
		}
		printf("%lld ", ans);
	}
	return 0;
}

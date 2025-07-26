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
const ll inf=1e14;
int n; ll a[N];
ll sum[N];
ull ans=0;
ll u[N], v[N], p[N], q[N], tem[N];
inline bool cmp1(int x, int y){
	return u[x]<u[y];
}
inline bool cmp2(int x, int y){
	return v[x]<v[y];
}
inline bool cmp3(int x, int y){
	return u[x]>u[y];
}
inline bool cmp4(int x, int y){
	return v[x]>v[y];
}
inline bool cmp5(int x, int y){
	return u[x]-p[x]>u[y]-p[y];
}
inline bool cmp6(int x, int y){
	return q[x]>q[y];
}
ll tr[N*60]; int ls[N*60], rs[N*60];
int rt, idx;
inline void mdf(int &p, ll l, ll r, ll x, ll v){
	if(!p) {
		p=++idx;
		tr[p]=ls[p]=rs[p]=0;
	}
	tr[p]+=v;
	if(l==r) return ;
	ll mid=(l+r)>>1;
	if(x<=mid) mdf(ls[p], l, mid, x, v);
	else mdf(rs[p], mid+1, r, x, v);
}
inline ll get(int p, ll l, ll r, ll L, ll R){
	if(L>R) return 0;
	if(!p) return 0;
	if(L<=l&&r<=R) return tr[p];
	ll mid=(l+r)>>1; ll ret=0;
	if(L<=mid) ret=get(ls[p], l, mid, L, R);
	if(R>mid) ret+=get(rs[p], mid+1, r, L, R);
	return ret;
}
void solve(int l, int r){
	if(l==r){
		u[l]=v[l]=a[l];
		ans+=a[l];
		return ;
	}
	int mid=(l+r)>>1;
	solve(l, mid); solve(mid+1, r);
	p[mid]=a[mid];
	for(int i=mid-1; i>=l; --i) p[i]=max(p[i+1], sum[mid]-sum[i-1]);
	q[mid+1]=a[mid+1];
	for(int i=mid+2; i<=r; ++i) q[i]=max(q[i-1], sum[i]-sum[mid]);
	vector<int> v1, v2;
	for(int i=l; i<=mid; ++i) v1.ep(i);
	for(int i=mid+1; i<=r; ++i) v2.ep(i);
	sort(v1.begin(), v1.end(), cmp1);
	sort(v2.begin(), v2.end(), cmp2);
	int it=0;
	rt=idx=0;
	for(auto t:v1){
		while(it<(int)v2.size()&&v[v2[it]]<u[t]) mdf(rt, -inf, inf, q[v2[it]], 1), ++it; 
		ans+=1ull*u[t]*get(rt, -inf, inf, -inf, u[t]-p[t]-1);
	}
	sort(v1.begin(), v1.end(), cmp3);
	sort(v2.begin(), v2.end(), cmp4);
	it=0;
	rt=idx=0;
	for(auto t:v1){
		while(it<(int)v2.size()&&v[v2[it]]>=u[t]) mdf(rt, -inf, inf, v[v2[it]]-q[v2[it]], v[v2[it]]), ++it; 
		ans+=get(rt, -inf, inf, p[t]+1, inf);
	}
	sort(v1.begin(), v1.end(), cmp5);
	sort(v2.begin(), v2.end(), cmp6);
	it=0;
	rt=idx=0;
	for(auto t:v1){
		while(it<(int)v2.size()&&q[v2[it]]>=u[t]-p[t]) mdf(rt, -inf, inf, v[v2[it]]-q[v2[it]], 1), ++it; 
		ans+=1ull*p[t]*get(rt, -inf, inf, -inf, p[t]);
	}
	it=0;
	rt=idx=0;
	for(auto t:v1){
		while(it<(int)v2.size()&&q[v2[it]]>=u[t]-p[t]) mdf(rt, -inf, inf, v[v2[it]]-q[v2[it]], q[v2[it]]), ++it; 
		ans+=get(rt, -inf, inf, -inf, p[t]);
	}
	tem[r]=u[r]=a[r];
	for(int i=r-1; i>=l; --i) tem[i]=max(tem[i+1]+a[i], a[i]), u[i]=max(tem[i], u[i+1]);
	tem[l]=v[l]=a[l];
	for(int i=l+1; i<=r; ++i) tem[i]=max(tem[i-1]+a[i], a[i]), v[i]=max(tem[i], v[i-1]);
}
int main(){
	// freopen("D:\\nya\\acm\\A\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\A\\test.out","w",stdout);
	read(n);
	for(int i=1; i<=n; ++i) read(a[i]), sum[i]=sum[i-1]+a[i];
	solve(1, n);
	printf("%llu\n", ans);
	return 0;
}


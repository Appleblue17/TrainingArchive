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
typedef __int128 lint;
#define ep emplace_back
template <typename T>inline void read(T &x){
	x=0;char c=getchar();bool f=0;
	for(;c<'0'||c>'9';c=getchar()) f|=(c=='-');
	for(;c>='0'&&c<='9';c=getchar())
	x=(x<<1)+(x<<3)+(c^48);
	x=(f?-x:x);
}
const int N=1e5+5;
const int inf=1e9;
int n, m, V, K, D;
struct node{
	int t, h, id;
	inline bool operator <(const node &x)const{
		if(t!=x.t) return t<x.t;
		return id<x.id;
	}
}a[N];
ll tr[N*70]; int root, ls[N*70], rs[N*70], idx;
inline void ins(int &p, int l, int r, int x, int v){
	if(!p) p=++idx;
	tr[p]+=v;
	if(l==r) return ;
	int mid=(l+r)>>1;
	if(x<=mid) ins(ls[p], l, mid, x, v);
	else ins(rs[p], mid+1, r, x, v);
}
inline ll get(int p, int l, int r, int L, int R){
	if(L>R) return 0;
	if(!p) return 0;
	if(L<=l&&r<=R) return tr[p];
	int mid=(l+r)>>1; ll ret=0;
	if(L<=mid) ret+=get(ls[p], l, mid, L, R);
	if(R>mid) ret+=get(rs[p], mid+1, r, L, R);
	return ret;
}
ll ans[N];
int main(){
	// freopen("D:\\nya\\acm\\C\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\C\\test.out","w",stdout);
	read(n); read(m); read(V); read(K); read(D);
	for(int i=1; i<=n; ++i) read(a[i].t), read(a[i].h), a[i].id=i;
	for(int i=1, p, v; i<=m; ++i){
		read(p); read(v); ins(root, 1, inf, p, v);
	}
	sort(a+1, a+n+1);
	ll lst=1, res=K;
	for(int i=1; i<=n; ++i){
		ll l=a[i].t, r=1ll*n*inf+a[i].t, mid, ret=r;
		if(lst<a[i].t) res=K, lst=a[i].t;
		while(l<=r){
			mid=(l+r)/2;
			ll s1=get(root, 1, inf, 1, min((ll)inf, 1ll*(mid-a[i].t+1)*V));
			lint s2=(lint)max(0ll, mid-lst)*D*K;
			if(mid>=lst) s2+=1ll*res*D;
			if(s2+s1>=a[i].h){
				ret=mid; r=mid-1;
			}
			else{
				l=mid+1;
			}
		}
		// cout<<a[i].t<<' '<<a[i].h<<' '<<ret<<' '<<lst<<' '<<res<<endl;
		ans[a[i].id]=ret;
		if(ret<lst) continue;
		ll s1=get(root, 1, inf, 1, min((ll)inf, 1ll*(ret-a[i].t+1)*V));
		ll s2=1ll*max(0ll, ret-lst-1)*D*K;
		if(ret>lst) s2+=1ll*res*D;
		if(ret>lst) lst=ret, res=K;
		if(s1+s2<a[i].h){
			int tem=(a[i].h-s1-s2-1+D)/D;
			res-=tem;
			if(res==0) res=K, ++lst;
		}
	}
	for(int i=1; i<=n; ++i) printf("%lld ", ans[i]);
	return 0;
}


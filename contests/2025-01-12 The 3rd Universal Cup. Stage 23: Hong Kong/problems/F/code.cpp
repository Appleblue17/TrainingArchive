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
int T, n;
int a[N];
vector<pii> lp[N], rp[N];
int main(){
	// freopen("D:\\nya\\acm\\B\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\B\\test.out","w",stdout);
	read(T);
	while(T--){
		read(n);
		for(int i=1; i<=n; ++i) read(a[i]), a[i+n]=a[i];
		for(int i=1; i<=n*2; ++i) lp[i].clear(), rp[i].clear();
		for(int i=1; i<=n*2; ++i){
			int lst=a[i];
			lp[i].ep(lst, i);
			for(auto t:lp[i-1]){
				if(t.fi/2+a[i]>lst){
					lst=t.fi/2+a[i]; lp[i].ep(lst, t.se);
				}
			}
		}
		rp[n*2+1].clear();
		for(int i=n*2; i>=1; --i){
			int lst=a[i];
			rp[i].ep(lst, i);
			for(auto t:rp[i+1]){
				if(t.fi/2+a[i]>lst){
					lst=t.fi/2+a[i]; rp[i].ep(lst, t.se);
				}
			}
		}
		for(int i=1; i<=n; ++i){
			int it=rp[i].size()-1;
			ll ans=a[i];
			for(auto t:lp[i+n]){
				while(it>=0&&rp[i][it].se>=t.se) --it;
				if(it>=0) ans=max(ans, (ll)t.fi+rp[i][it].fi-a[i]);
			}
			printf("%lld ", ans);
		}
		putchar('\n');
	}
	return 0;
}


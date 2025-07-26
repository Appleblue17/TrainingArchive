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
const int N=5e5+5;
int T, n, d;
int a[N];
int main(){
	// freopen("D:\\nya\\acm\\B\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\B\\test.out","w",stdout);
	read(T);
	while(T--){
		read(n); read(d);
		a[0]=0;
		for(int i=1; i<=n; ++i) read(a[i]), a[0]+=a[i];
		sort(a+1, a+n+1);
		if(d==1){
			printf("%lld\n", 1ll*a[0]*(a[0]-1)/2);
			continue;
		}
		if(d==2){
			ll ans=0, sum=0;
			for(int i=1; i<=n; ++i) ans+=sum*a[i], sum+=a[i];
			printf("%lld\n", ans);
			continue;
		}
		ll sum=0, ans=0;
		for(int i=1; i<=n; ++i) ans+=1ll*(a[i]-sum)*(n-i+1)*(n-i)/2, sum+=a[i]-sum;
		printf("%lld\n", ans);
	}
	return 0;
}


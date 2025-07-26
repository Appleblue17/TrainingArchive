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
int T, n;
int a[N];
ll s[N], s2[N];
int main(){
	// freopen("D:\\nya\\acm\\C\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\C\\test.out","w",stdout);
	read(T);
	while(T--){
		read(n);
		for(int i=1; i<=n; ++i){
			read(a[i]); 
		}
		int pos=1;
		while(pos<n&&a[pos+1]<a[pos]) ++pos;
		s[pos]=s2[pos]=0;
		for(int i=pos-1; i>=1; --i) s[i]=s[i+1]+a[i];
		for(int i=pos+1; i<=n; ++i) s2[i]=s2[i-1]+a[i];
		ll s1=a[pos];
		ld ans=0;
		for(int i=pos+1; i<=n; ++i){
			s1+=a[i];
			ans=max(ans, (ld)(s1+s[pos-1])/(i-pos+1+1));
			ans=max(ans, (ld)(s1+s[1])/i);
		}
		s1=a[pos];
		for(int i=pos-1; i>=1; --i){
			s1+=a[i];
			ans=max(ans, (ld)(s1+s2[pos+1])/(pos+1-i+1));
			ans=max(ans, (ld)(s1+s2[n])/(n-i+1));
		}
		printf("%.10LF\n", ans);
	}
	return 0;
}


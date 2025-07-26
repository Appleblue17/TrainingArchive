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
int T, n;
int a[N], b[N], p[N], q[N];
int tr[N];
inline int get(int x){
	int ret=0;
	for(; x<=n; x+=(x&-x)) ret+=tr[x];
	return ret;
}
inline void add(int x){
	for(; x; x-=(x&-x)) ++tr[x];
}
int main(){
	// freopen("D:\\nya\\acm\\B\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\B\\test.out","w",stdout);
	read(T);
	while(T--){
		read(n);
		for(int i=1; i<=n; ++i) read(a[i]), p[a[i]]=i, tr[i]=0;
		p[n+1]=n+1;
		int it=1;
		while(it<=n){
			if(p[it]<p[it+1]) b[it]=it, ++it;
			else b[it]=it+1, b[it+1]=it, it+=2;
		}
		ll sum=0;
		for(int i=1; i<=n; ++i) q[b[i]]=i;
		// for(int i=1; i<=n; ++i) cout<<b[i]<<' '; cout<<endl;
		for(int i=1; i<=n; ++i) a[i]=q[a[i]];
		for(int i=1; i<=n; ++i) {
			sum+=get(a[i]);
			add(a[i]);
		}
		printf("%lld\n", sum);
	}
	return 0;
}


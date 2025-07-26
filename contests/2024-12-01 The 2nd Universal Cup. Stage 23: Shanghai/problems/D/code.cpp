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
const int N=3e5+5, M=1000;
int n;
int a[N], pos[N];
ll ans;
int v[N];
int cnt[M*2];
int main(){
	// freopen("D:\\nya\\acm\\C\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\C\\test.out","w",stdout);
	read(n);
	for(int i=1; i<=n; ++i) read(a[i]), pos[a[i]]=i, v[i]=-1;
	for(int i=n; i>=1; --i){
		for(int j=0; j<M*2; ++j) cnt[j]=0;
		int cur=M; ++cnt[M];
		for(int j=pos[i]+1; j<=n; ++j){
			cur+=v[j];
			if(cur>=M*2||cur<0) break;
			++cnt[cur];
		}
		ll mul=0; cur=M;
		for(int j=pos[i]-1; j>=0; --j){
			cur-=v[j+1];
			if(cur>=M*2||cur<0) break;
			mul+=cnt[cur]+cnt[cur-1];
		}
		ans+=mul*i;
		// cout<<i<<' '<<mul<<endl;
		v[pos[i]]=1;
	}
	printf("%lld\n", ans);
	return 0;
}


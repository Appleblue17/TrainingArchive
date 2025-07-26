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
const int N=20, M=2e5;
int n, m;
int s[N], g[M];
ll f[M];
bool ban[M];
int main(){
	// freopen("D:\\nya\\acm\\A\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\A\\test.out","w",stdout);
	read(n); read(m);
	for(int i=1, x, y; i<=m; ++i){
		read(x); read(y);
		--x; --y;
		s[x]|=1<<y; s[y]|=1<<x;
	}
	for(int i=0; i<(1<<n); ++i){
		for(int j=0; j<n; ++j) if((i>>j)&1) g[i]|=s[j];
		for(int j=0; j<n; ++j) if((i>>j)&1){
			for(int k=0; k<n; ++k) if((i>>k)&1){
				if((s[k]&(1<<j))!=0) ban[i]=1;
			}
		}
	}
	f[0]=1;
	for(int s=0; s<(1<<n); ++s){
		int w=(1<<n)-1-s;
		for(int t=w; t; t=(t-1)&w){
			if(ban[t]) continue;
			if((g[t]&s)==s) f[s|t]+=f[s];
		}
	}
	printf("%lld\n", f[(1<<n)-1]);
	return 0;
}


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
const int N=505;
int T, n, m;
ll f[N][N];
bitset<505> g[N];
int main(){
	// freopen("D:\\nya\\acm\\A\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\A\\test.out","w",stdout);
	read(n); read(m);
	for(int i=1, x, y; i<=m; ++i){
		read(x); read(y);
		g[x][y]=1;
	}
	for(int k=1; k<=n; ++k){
		for(int i=1; i<=n; ++i) if(g[i][k]){
			g[i]|=g[k];
		}
	}
	for(int i=n; i>=1; --i){
		for(int j=i+1; j<=n; ++j) if(g[i][j]){
			for(int k=i+1; k<j; ++k){
				f[i][j]+=min(f[i][k], f[k][j]);
			}
			++f[i][j];
		}
	}
	printf("%lld\n", f[1][n]);
	return 0;
}


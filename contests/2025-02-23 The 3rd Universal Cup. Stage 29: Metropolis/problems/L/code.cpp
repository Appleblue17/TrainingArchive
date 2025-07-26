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
const int N=5005;
const int inf=1e9;
int T, n, m;
int r[N];
int f[N][N], g[N][N], lim[N][N];
void solve(){
	read(n); read(m);
	for(int i=0; i<n; ++i) read(r[i]);
	for(int i=0; i<n; ++i) for(int j=0; j<n; ++j) f[i][j]=g[i][j]=lim[i][j]=inf;
	while(m--){
		int x, y, t;
		read(x); read(y); read(t);
		if(r[x]*2>=n-1) continue;
		int lp=(x+n-y+n-r[x])%n;
		int rp=(x+n-y+r[x])%n;
		lim[lp][rp]=min(lim[lp][rp], t);
	}
	for(int len=2; len<=n; ++len){
		for(int lp=0; lp<n; ++lp){
			int rp=(lp+len-1)%n;
			lim[lp][rp]=min(lim[lp][rp], min(lim[(lp+1)%n][rp], lim[lp][(rp+n-1)%n]));
		}
	}
	for(int len=n-1; len>0; --len){
		for(int lp=0; lp<n; ++lp){
			int rp=(lp+len-1)%n;
			f[lp][rp]=max(min(lim[(rp+1)%n][(lp+n-1)%n], f[(lp+n-1)%n][rp])-1, min(lim[(rp+1)%n][(lp+n-1)%n], g[lp][(rp+1)%n])-len);
			g[lp][rp]=max(min(lim[(rp+1)%n][(lp+n-1)%n], f[(lp+n-1)%n][rp])-len, min(lim[(rp+1)%n][(lp+n-1)%n], g[lp][(rp+1)%n])-1);
		}
	}
	for(int i=0; i<n; ++i) printf("%c", "01"[f[i][i]>=0]);
	putchar('\n');
}
int main(){
	// freopen("D:\\nya\\acm\\B\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\B\\test.out","w",stdout);
	read(T);
	while(T--) solve();
	return 0;
}


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
const int N=10005;
const ll inf=1e18;
int n, m;
int l[N], k[N];
vector<pii> e[N];
int w[N], c[N];
ll f[N][N], g[N], h[N];
void work(int x, int l, int r){
	for(int i=0; i<=m; ++i) f[x][i]=inf;
	int p1=0, p2=l;
	while(p1<=m&&h[p1]>=inf) ++p1;
	while(p2<=r&&g[p2]>=inf) ++p2;
	while(p1+p2<=m){
		f[x][p1+p2]=h[p1]+g[p2];
		if(p2<r&&h[p1]+g[p2+1]<h[p1+1]+g[p2]) ++p2;
		else ++p1;
	}
}
void dfs(int x, int fa){
	for(auto edg:e[x]){
		int y=edg.fi;
		if(y==fa) continue;
		dfs(y, x);
		int cl=l[edg.se], ck=k[edg.se];
		if(c[y]>ck){
			for(int i=1; i<=m; ++i){
				printf("-1\n");
			}
			exit(0);
		}
		w[y]=cl; 
		for(int i=0; i<=m; ++i) g[i]=(2ll*max(c[y], i)-i)*w[y];
		for(int i=0; i<=m; ++i) g[i]+=f[y][i];
		for(int i=min(m, ck)+1; i<=m; ++i) g[i]=inf;
		for(int i=0; i<=m; ++i) h[i]=f[x][i];
		work(x, max(2*c[y]-ck, 0), min(m, ck));
		c[x]=max(c[x], c[y]);
	}
}
ll ans[N];
int main(){
	// freopen("D:\\nya\\acm\\A\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\A\\test.out","w",stdout);
	read(n); read(m);
	for(int i=1, x, y; i<n; ++i){
		read(x); read(y); read(l[i]); read(k[i]);
		e[x].ep(y, i); e[y].ep(x, i);
	}
	for(int i=2; i<=n; ++i) read(c[i]);
	dfs(1, 0);
	ans[c[1]]=f[1][0];
	for(int i=1; i<=c[1]; ++i){
		ans[c[1]]=min(ans[c[1]], f[1][i]);
	}
	for(int i=c[1]+1; i<=m; ++i) {
		ans[i]=f[1][i];
	}
	for(int i=1; i<c[1]; ++i) printf("-1\n");
	for(int i=c[1]; i<=m; ++i){
		if(ans[i]>=inf) ans[i]=-1;
		printf("%lld\n", ans[i]);
	}
	return 0;
}


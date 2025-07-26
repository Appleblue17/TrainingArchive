#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double dou;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
#define fi first
#define se second
#define MAXN 1000010
#define mapa make_pair
typedef long double ld;
typedef unsigned long long ull;
template <typename T>inline void read(T &x){
	x=0;char c=getchar();bool f=0;
	for(;c<'0'||c>'9';c=getchar()) f|=(c=='-');
	for(;c>='0'&&c<='9';c=getchar())
	x=(x<<1)+(x<<3)+(c^48);
	x=(f?-x:x);
}
const int mo=1e9+7;
using namespace std;
ll a[MAXN],b[MAXN];
ll f[5010][5010];
ll t,n,m,x,y,ans,k;
ll Abs(ll x){
	return x<0?-x:x;
}
void solve(){
	memset(f,48,sizeof(f));
	ans=0;
	scanf("%lld",&n);
	scanf("%lld",&m);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
	}
	for(int i=1;i<=m;i++){
		scanf("%lld",&b[i]);
	}
	sort(a+1,a+n+1);
	sort(b+1,b+m+1);
	f[0][0]=0;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=min((ll)i,m);j++){
			f[i][j] = min(f[i-1][j-1] + Abs(a[i]-b[j]),f[i-1][j]);
		//	printf("f[%d][%d]=%lld\n",i,j,f[i][j]);
		}
	}
	printf("%lld\n",f[n][m]);
}
int main(){
	//cin >> t;
	//for(int i=1;i<=t;i++){
		solve();
	//}
}

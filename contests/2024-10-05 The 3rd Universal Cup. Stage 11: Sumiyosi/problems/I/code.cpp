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
template <typename T>inline void read(T &x){
	x=0;char c=getchar();bool f=0;
	for(;c<'0'||c>'9';c=getchar()) f|=(c=='-');
	for(;c>='0'&&c<='9';c=getchar())
	x=(x<<1)+(x<<3)+(c^48);
	x=(f?-x:x);
}
const int mod=998244353;
const int N=105;
int n, a[N];
int f[N][N*N];
int sum, all;
ll frc[N];
int main(){
	// freopen("D:\\nya\\test.in","r",stdin);
	// freopen("D:\\nya\\test.out","w",stdout);
	read(n);
	frc[0]=1;
	for(int i=1; i<=n; ++i) read(a[i]), all+=a[i], frc[i]=frc[i-1]*i%mod;
	if(all&1){
		printf("0\n");
		return 0;
	}
	sort(a+1, a+n+1);
	f[0][0]=1;
	for(int i=1; i<=n; ++i){
		for(int j=i-1; j>=0; --j){
			for(int k=min(sum, all-a[i]); k>=0; --k){
				f[j+1][k+a[i]]=(f[j+1][k+a[i]]+f[j][k])%mod;
			}
		}
		sum+=a[i];
	}
	int ans=0;
	for(int i=1; i<n; ++i) ans=(ans+frc[i]*frc[n-i]%mod*f[i][all/2]%mod)%mod;
	printf("%d\n", ans);
	return 0;
}

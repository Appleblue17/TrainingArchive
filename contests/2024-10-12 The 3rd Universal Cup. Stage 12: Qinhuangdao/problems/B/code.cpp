#pragma GCC optimize(2)
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
const int N=2e6+5;
int Test, n, mod;
inline ll fpow(ll x, ll y){
	ll ret=1;
	while(y){
		if(y&1) ret=ret*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return ret;
}
inline ll plu(ll x, ll y){x+=y; return (x>=mod)?x-mod:x;}
inline ll sub(ll x, ll y){x-=y; return (x<0)?x+mod:x;}
ll frc[N], inv[N];
inline ll C(int x, int y){
	if(x<0||y<0||x-y<0) return 0;
	return frc[x]*inv[y]%mod*inv[x-y]%mod;
}
ll a[N], b[N]; ll A, B;
inline ll S(int x){
	if(x%2) return 0;
	return (C(x,x/2)+mod-C(x,x/2-1))%mod;
}
ll CT[N];
ll F[N];
int main(){
	// freopen("D:\\nya\\acm\\A\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\A\\test.out","w",stdout);
	read(Test);
	while(Test--){
		read(n); read(mod); read(b[0]); read(A); read(B);
		for(int i=1; i<=2*n; ++i) b[i]=plu(A*b[i-1]%mod, B), a[i]=plu(a[i-1], plu(b[i], 1));
		frc[0]=1;
		for(int i=1; i<=n*2; ++i) frc[i]=frc[i-1]*i%mod;
		inv[n*2]=fpow(frc[n*2], mod-2);
		for(int i=n*2-1; i>=0; --i) inv[i]=inv[i+1]*(i+1)%mod;
		ll all=sub(C(n*2, n), C(n*2, n+1)), sum=0;
		for(int i=n*2; i>=0; --i) CT[i]=S(i);
		
		ll cur=0;
		for(int i=n*2; i>=1; --i){
			cur=plu(cur, CT[i-1]*CT[2*n-i-1]%mod);
			F[i]=cur;
		}
		
		for(int i=1; i<=n*2; ++i){ 
			cur=F[i];
//			cout<<F[i]<<" ";
			sum=sub(sum, cur*a[i]%mod);
			sum=plu(sum, (ll)a[i]*sub(all, cur)%mod);
		}
//		cout<<endl;
		printf("%lld\n", fpow(all, mod-2)*sum%mod);
	}
	return 0;
}

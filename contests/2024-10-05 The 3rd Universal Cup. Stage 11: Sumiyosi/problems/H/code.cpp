#include<bits/stdc++.h>
using namespace std;
const int mo = 998244353;
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
ll ksm(ll a,ll b)
{
    ll r=1;
    while(b)
    {
        if(b&1) r=a*r%mo;
        a=a*a%mo;
        b>>=1;
    }
    return r;
}
using namespace std;
ll a[MAXN],b[MAXN],t[MAXN],id[MAXN];
ll n,m,x,y,ans,k;
bool cmp(int i,int j){
	ll fi = t[i]*b[i]*b[j]+t[j]*a[i]*b[j];
	ll se = t[j]*b[j]*b[i]+t[i]*a[j]*b[i];
	return fi<se;
}
void solve(){
	ans=0;
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld%lld%lld",&t[i],&a[i],&b[i]);
		id[i]=i;
	}
	sort(id+1,id+n+1,cmp);
	for(int i=1;i<=n;i++){
		ans = (ans+t[id[i]])*b[id[i]]%mo*ksm(a[id[i]],mo-2)%mo;
	}
	printf("%lld\n",ans);
}
int main(){
	solve();
}

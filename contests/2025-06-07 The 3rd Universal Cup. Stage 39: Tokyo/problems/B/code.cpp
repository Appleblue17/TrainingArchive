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
typedef pair<ull,ull> puu;
//mt19937_64 rng(GetTickCount());
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
ll t,n,m,x,y,ans,k;
void solve(){
	ans=0;
	scanf("%lld",&n);
	scanf("%lld",&k);
	for(int i=1;i<=2*k;i++){
		scanf("%lld",&a[i]);
	}
	int lim=0,cur=0;
    ll cnt0=n,cnt1=0;//cnt0 = cur,cnt1 > cur
    for(int i=1;i<=2*k;i++){
        lim++;
        if(a[i] >= cnt0){
            cur += 2;
            ll t = a[i]-cnt0;
            cnt1 = t;
            cnt0 = n-t;
        }
        else{
            cnt0 -= a[i];
            cnt1 += a[i];
        }
        //printf("cnt0=%lld,cnt1=%lld,lim=%d,cur=%d\n",cnt0,cnt1,lim,cur);
        //assert(cnt0 != 0);
        if(cur < lim){
            printf("No\n");
            return;
        }
    }
    if(cnt0 == n && cur == lim){
        printf("Yes\n");
    }
    else printf("No\n");
}
int main(){
	int T;
    scanf("%d",&T);
	for(int i=1;i<=T;i++){
		solve();
	}
}


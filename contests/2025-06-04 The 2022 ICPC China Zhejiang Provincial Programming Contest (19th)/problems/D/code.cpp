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
const int N=2e5+5;
int n, m, E;
int v[N], a[N], b[N];
vector<int> dp;
int f[N];
inline void solve(int lp, int rp, int lv, int rv){
	if(lp>rp||lv>rv) return ;
	if(lv==rv){
		for(int i=lp; i<=rp; ++i) f[i]=lv;
		return ;
	}
	int midv=(lv+rv)>>1;
	vector<vector<int> > back;
	int L=lp, R=min(rp, midv), mid, ret=lp-1;
	for(int i=midv+1; i<=rv; ++i){
		back.ep(dp);
		for(int j=m-a[i]; j>=0; --j){
			dp[j+a[i]]=max(dp[j+a[i]], dp[j]+v[i]);
		}
	}
	for(int i=max(rp+1, lv); i<=midv; ++i){
		back.ep(dp);
		for(int j=m-b[i]; j>=0; --j){
			dp[j+b[i]]=max(dp[j+b[i]], dp[j]+v[i]);
		}
	}
	while(L<=R){
		mid=(L+R)>>1;
		for(int i=L; i<mid; ++i){
			back.ep(dp);
			for(int j=m-a[i]; j>=0; --j){
				dp[j+a[i]]=max(dp[j+a[i]], dp[j]+v[i]);
			}
		}
		for(int i=mid; i<=R; ++i){
			back.ep(dp);
			for(int j=m-b[i]; j>=0; --j){
				dp[j+b[i]]=max(dp[j+b[i]], dp[j]+v[i]);
			}
		}
		ll sum=0;
		int mx=0;
		for(int i=1; i<=m; ++i) mx=max(mx, dp[i]), sum+=mx;
		if(sum<=1ll*m*E){
			ret=mid; 
			for(int i=mid; i<=R; ++i) dp=back.back(), back.pop_back();
			back.ep(dp);
			for(int j=m-a[mid]; j>=0; --j){
				dp[j+a[mid]]=max(dp[j+a[mid]], dp[j]+v[mid]);
			}
			L=mid+1;
		}
		else{
			for(int i=mid; i<=R; ++i) dp=back.back(), back.pop_back();
			for(int i=L; i<mid; ++i) dp=back.back(), back.pop_back();
			for(int i=mid; i<=R; ++i){
				back.ep(dp);
				for(int j=m-b[i]; j>=0; --j){
					dp[j+b[i]]=max(dp[j+b[i]], dp[j]+v[i]);
				}
			}
			R=mid-1;
		}
	}
	while(back.size()){
		dp=back.back(); back.pop_back();
	}
	if(rp<lv){
		for(int i=ret+1; i<=rp; ++i){
			back.ep(dp);
			for(int j=m-b[i]; j>=0; --j){
				dp[j+b[i]]=max(dp[j+b[i]], dp[j]+v[i]);
			}
		}
	}
	else{
		for(int i=ret+1; i<lv; ++i){
			back.ep(dp);
			for(int j=m-b[i]; j>=0; --j){
				dp[j+b[i]]=max(dp[j+b[i]], dp[j]+v[i]);
			}
		}
	}
	for(int i=max(midv+1, ret+1); i<=rv; ++i){
		back.ep(dp);
		for(int j=m-a[i]; j>=0; --j){
			dp[j+a[i]]=max(dp[j+a[i]], dp[j]+v[i]);
		}
	}
	solve(lp, ret, lv, midv);
	while(back.size()){
		dp=back.back(); back.pop_back();
	}
	if(rp<lv){
		for(int i=lv; i<=midv; ++i){
			back.ep(dp);
			for(int j=m-b[i]; j>=0; --j){
				dp[j+b[i]]=max(dp[j+b[i]], dp[j]+v[i]);
			}
		}
	}
	else{
		for(int i=rp+1; i<=midv; ++i){
			back.ep(dp);
			for(int j=m-b[i]; j>=0; --j){
				dp[j+b[i]]=max(dp[j+b[i]], dp[j]+v[i]);
			}
		}
	}
	for(int i=lp; i<=ret&&i<=midv; ++i){
		back.ep(dp);
		for(int j=m-a[i]; j>=0; --j){
			dp[j+a[i]]=max(dp[j+a[i]], dp[j]+v[i]);
		}
	}
	solve(ret+1, rp, midv+1, rv);
	while(back.size()){
		dp=back.back(); back.pop_back();
	}
}
int main(){
	// freopen("D:\\nya\\acm\\A\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\A\\test.out","w",stdout);
	read(n); read(m); read(E);
	for(int i=1; i<=n; ++i){
		read(v[i]); read(a[i]); read(b[i]);
	}
	dp.resize(m+1);
	for(int i=1; i<=m; ++i) dp[i]=-2e9;
	dp[0]=0;
	solve(1, n, 1, n+1);
	ll ans=0;
	for(int i=1; i<=n; ++i) ans+=n+1-f[i];
	printf("%lld\n", ans);
	return 0;
}


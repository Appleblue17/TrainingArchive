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
const int N=5e5+5, mod=998244353;
inline ll fpow(ll x, ll y){
	ll ret=1;
	while(y){
		if(y&1) ret=ret*x%mod;
		x=x*x%mod; y>>=1;
	}
	return ret;
}
ll frc[N];
int T, n, m, S;
int d[N];
void solve(){
	read(n); read(m); read(S);
	deque<pair<pair<ll, ll>, int> > que;
	ll lst=0;
	ll ans=1;
	que.push_front(mapa(mapa(lst, lst+m-1), 0));
	for(int i=1; i<=S; ++i){
		read(d[i]);
		ll cl=lst+d[i], cr=cl+m-1;
		while(!que.empty()&&que.front().fi.se<cl){
			int dt=i-que.front().se;
			if(dt<n) ans=ans*fpow(frc[dt]*frc[dt]%mod*fpow(dt+1, n-dt+1)%mod, que.front().fi.se-que.front().fi.fi+1)%mod;
			else ans=ans*fpow(frc[n]*frc[n]%mod*fpow(n+1, dt-n+1)%mod, que.front().fi.se-que.front().fi.fi+1)%mod;
			que.pop_front();
		}
		while(!que.empty()&&que.back().fi.fi>cr){
			int dt=i-que.back().se;
			if(dt<n) ans=ans*fpow(frc[dt]*frc[dt]%mod*fpow(dt+1, n-dt+1)%mod, que.back().fi.se-que.back().fi.fi+1)%mod;
			else ans=ans*fpow(frc[n]*frc[n]%mod*fpow(n+1, dt-n+1)%mod, que.back().fi.se-que.back().fi.fi+1)%mod;
			que.pop_back();
		}
		if(!que.empty()&&que.front().fi.fi<cl){
			ll tl=que.front().fi.fi, tr=que.front().fi.se; int ts=que.front().se;
			int dt=i-que.front().se;
			if(dt<n) ans=ans*fpow(frc[dt]*frc[dt]%mod*fpow(dt+1, n-dt+1)%mod, cl-tl)%mod;
			else ans=ans*fpow(frc[n]*frc[n]%mod*fpow(n+1, dt-n+1)%mod, cl-tl)%mod;
			que.pop_front();
			que.push_front(mapa(mapa(cl, tr), ts));
		}
		if(!que.empty()&&que.back().fi.se>cr){
			ll tl=que.back().fi.fi, tr=que.back().fi.se; int ts=que.back().se;
			int dt=i-que.back().se;
			if(dt<n) ans=ans*fpow(frc[dt]*frc[dt]%mod*fpow(dt+1, n-dt+1)%mod, tr-cr)%mod;
			else ans=ans*fpow(frc[n]*frc[n]%mod*fpow(n+1, dt-n+1)%mod, tr-cr)%mod;
			que.pop_back();
			que.push_back(mapa(mapa(tl, cr), ts));
		}
		if(que.empty()){
			que.push_front(mapa(mapa(cl, cr), i));
		}
		else if(d[i]<0){
			que.push_front(mapa(mapa(cl, que.front().fi.fi-1), i));
		}
		else if(d[i]>0){
			que.push_back(mapa(mapa(que.back().fi.se+1, cr), i));
		}
		lst=cl;
	}
	while(!que.empty()){
		int dt=S+1-que.front().se;
		if(dt<n) ans=ans*fpow(frc[dt]*frc[dt]%mod*fpow(dt+1, n-dt+1)%mod, que.front().fi.se-que.front().fi.fi+1)%mod;
		else ans=ans*fpow(frc[n]*frc[n]%mod*fpow(n+1, dt-n+1)%mod, que.front().fi.se-que.front().fi.fi+1)%mod;
		que.pop_front();
	}
	printf("%lld\n", ans);
}
int main(){
	// freopen("D:\\nya\\acm\\A\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\A\\test.out","w",stdout);
	frc[0]=1;
	for(int i=1; i<N; ++i) frc[i]=frc[i-1]*i%mod;
	read(T);
	while(T--) solve();
	return 0;
}


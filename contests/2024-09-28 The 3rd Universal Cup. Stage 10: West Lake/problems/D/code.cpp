#pragma GCC optimize(2)
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pll;
#define fi first
#define se second
#define MAXN 1000010
#define mapa make_pair
template <typename T>inline void read(T &x){
	x=0;char c=getchar();bool f=0;
	for(;c<'0'||c>'9';c=getchar()) f|=(c=='-');
	for(;c>='0'&&c<='9';c=getchar())
	x=(x<<1)+(x<<3)+(c^48);
	x=(f?-x:x);
}

using namespace std;
pll a[MAXN];
ll t,n,m,x,y,ans,k;
ll Abs(ll x){
	return x<0?-x:x;
}
bool within(pll u,pll v,ll x){//check whether v is inside u
	if(v.fi < u.fi)return 0;
	if(v.fi == u.fi && v.se == u.se)return 1;
	if(v.fi == u.fi) return 0;
	__int128 A=Abs(v.se - u.se),B=x,C=(v.fi - u.fi);
	if(A <= B*C)return 1;
	else return 0;
}
pll Down(pll u,pll v,ll x){
	pll ret;
	if(u.fi > v.fi) swap(u,v);
	if(u.se < v.se)
		ret = mapa(u.fi - (Abs(v.se-u.se)/(2*x)-(v.fi - u.fi)/2)
				, u.se + (Abs(v.se-u.se)/2-x*(v.fi - u.fi)/2) );
	else
		ret = mapa(u.fi - (Abs(v.se-u.se)/(2*x)-(v.fi - u.fi)/2)
				, u.se - (Abs(v.se-u.se)/2-x*(v.fi - u.fi)/2) );
	
	return ret;
}
bool check(ll x){
	pll u,v,tar;
	ll tmp=(1000000000/x+1)*x*2;
	u = mapa(-tmp,0);
	v = mapa(-tmp,0);
	for(ll i=1;i<=n;i++){
		
		tar = a[i];
		tar.fi*=2*x,tar.se*=2*x;
		
		bool f1 = within(u,v,x);
		bool f2 = within(v,u,x);
		if(f1 | f2){
			if(f2)swap(u,v);
			if(within(v,tar,x)){
				v = tar;
			}
			else if(within(u,tar,x)){
				u = tar;
			}
			else return 0;
		}
		else{
			bool f1 = within(u,tar,x),f2 = within(v,tar,x);
			if(f1 & f2){
				u = Down(u,v,x);
				v = tar;
			}
			else if(f1){
				u = tar;
			}
			else if(f2){
				v = tar;
			}
			else return 0;
		}
	}
	
	return 1;
}
unordered_map<ll,ll> ma;
void solve(){
	ans=0;
	scanf("%lld",&n);
	ma.clear();
	ll X,Y;
	for(ll i=1;i<=n;i++){
		read(X);read(Y);
		a[i].fi=X;a[i].se=Y;
		ma[Y]++;
	}
	
	if(ma.size() <= 2){
		printf("0\n");
		return;
	}
	
	ll le=1,ri=1e9,ans=ri+1;
	while(le <= ri){
		ll mi=(le+ri)/2;
		if(check(mi)) ans=mi, ri = mi-1;
		else le = mi+1;
	}
	if(ans <= 1e9) printf("%lld\n",ans);
	else printf("-1\n");
}
int main(){
	cin >> t;
	for(ll i=1;i<=t;i++){
		solve();
	}
}

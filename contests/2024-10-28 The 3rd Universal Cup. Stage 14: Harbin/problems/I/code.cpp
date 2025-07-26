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
int sm=0;
ll a[MAXN];
ll Prime[MAXN],pc;
unordered_map<ll,ll> ma;
ll t,n,m,x,y,ans,k,s;
ll dfscnt;
bool ip(ll x){
	for(int i=2;i*i<=x;i++){
		if(x%i==0)return 0;
	}
	return 1;
}
ll f(int s,int m,int dep){
	dfscnt++;
	if(dfscnt >= 3e5)return 1e12;
	//printf("f %d %d %d\n",s,m,dep);
	vector<ll> g;
	g.clear();
	//if(dep >= ans)return 1e12;
	for(int i=1;i*i<=m;i++){
		if(m%i==0){
		//	printf("add %d,%d\n",i,m/i);
			if(i!=1)g.push_back(i);
			g.push_back(m/i);
		}
	}
	if(g.size()<=2){
		if(s<m)return 1e12;
		else{
			if(ma[m]){
				ans = min(ans,sm+abs(s-m-ma[1])-1+dep);
				//printf("get ans=%lld\n",ans);
				return abs(s-m-ma[1])-1;
			}
			else{
				ans = min(ans,sm+abs(s-m-ma[1])+1+dep);
				//printf("get ans=%lld\n",ans);
				return abs(s-m-ma[1])+1;
			}
		}
	}
	sort(g.begin(),g.end());
	g.push_back(1e12);
	int i;
	vector<int> v;
	for(i=0;i<g.size();i++){
//		printf("%d ",g[i]);
		if(g[i]>=s)break;
	}
	i--;
//	printf("max is %d\n",g[i]);
	for(int j=i;j>=0;j--){
		if(ma[g[j]]>0){
			v.push_back(g[j]);
		}
	}
	for(int j=i;j>=0;j--){
		if(!ma[g[j]]){
			v.push_back(g[j]);
		}
	}
	ll ans=1e12;
	for(int j=0;j<v.size();j++){
	//	printf("choose %d\n",v[j]);
		if(ma[v[j]]){
			ma[v[j]]--;
			ans = min(ans,f(s-v[j],m/v[j],dep-1)-1);
			ma[v[j]]++;
		}
		else{
			ans = min(ans,f(s-v[j],m/v[j],dep+1)+1);
		}
	}
	return ans;
}

int main(){
	//freopen("9527.out","w",stdout);
	ans=1e12;int smx=0;
	scanf("%lld",&n);
	scanf("%lld",&s);
	scanf("%lld",&m);
	vector<int> g1;
	for(int i=1;i*i<=m;i++){
		g1.push_back(i);
		g1.push_back(m%i);
		smx += i+m%i;
	}
	
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		ma[a[i]]++;
		if(a[i]!=1)sm++;
	}
	//s -= ma[1];
	ll x = f(s,m,0);
	if(x >= 1e11)printf("-1\n");
	else printf("%lld\n",ans);
}

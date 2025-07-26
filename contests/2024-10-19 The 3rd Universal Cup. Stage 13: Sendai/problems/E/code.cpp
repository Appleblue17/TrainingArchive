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
ll a[MAXN],las[MAXN],cl;
vector<ll> g[MAXN];
ll t,n,m,x,y,ans,k,q;
void solve(){
	ans=0;
	n=1;a[1]=1;m=1;//n: length of a; m: overall length
	scanf("%lld",&q);
	for(int i=1;i<=q;i++){
		scanf("%lld%lld",&t,&x);
		if(t == 1){
			n++;m++;
			a[n]=x;
		}
		else if(t == 2){
			if(m <= 1e15)m*=2;
			if(cl != n){
				las[n]=cl;
				cl=n;
			}
			g[n].push_back(x);
			//printf("g[%lld],%lld\n",n,x);
		}
		else{
			if(x > m){
				printf("-1\n");
				continue;
			}
			int u = n,v = cl;
			bool f=0;
			while(x > u-v){
				//printf("u=%d,v=%d,x=%lld\n",u,v,x);
				x -= (u-v);
				//printf("%lld\n",g[v].size());
				for(int i=g[v].size()-1;i>=0;i--){
					int cx = g[v][i];
					//printf("cx=%lld\n",cx);
					if(x % 2 == 1){
						printf("%lld\n",cx);
						f=1;
						break;
					}
					else x = x/2;
				}
				if(f)break;
				u = v;
				v = las[v];
				//printf("u=%d,v=%d,x=%lld\n",u,v,x);
			}
			if(!f){
				printf("%lld\n",a[u-x+1]);
			}
		}
	}
}
int main(){
	solve();
}

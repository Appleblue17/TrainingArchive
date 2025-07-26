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
int n;
int px[N], py[N];
dou dis[N];
int v1, v2;
vector<pair<int, dou> > e[N];
inline dou get(int i, int j){
	return sqrt(1.0*(px[i]-px[j])*(px[i]-px[j])+1.0*(py[i]-py[j])*(py[i]-py[j]));
}
bool vis[N];
void dij(){
	priority_queue<pair<dou, int> > q;
	for(int i=1; i<=n+1; ++i) dis[i]=1e18;
	q.push(mapa(0, 0));
	while(!q.empty()){
		int x=q.top().se;
		q.pop();
		if(vis[x]) continue;
		vis[x]=1;
		for(auto edg:e[x]){
			int y=edg.fi; dou z=edg.se;
			if(dis[y]>dis[x]+z){
				dis[y]=dis[x]+z;
				if(!vis[y]) q.push(mapa(-dis[y], y));
			}
		}
	}
}
int main(){
	// freopen("D:\\nya\\acm\\A\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\A\\test.out","w",stdout);
	read(n); 
	for(int i=1; i<=n; ++i) read(px[i]), read(py[i]);
	read(px[0]); read(py[0]); read(px[n+1]); read(py[n+1]);
	read(v1); read(v2);
	for(int i=1; i<=n+1; ++i){
		dou dis=get(0, i);
		e[0].ep(i, dis/v1);
	}
	for(int i=1; i<=n; ++i){
		for(int j=i+1; j<=n+1; ++j){
			dou dis=get(i, j);
			if(v2*3.0>=dis){
				e[i].ep(j, dis/v2);
				e[j].ep(i, dis/v2);
			}
			else{
				e[i].ep(j, 3.0+(dis-v2*3.0)/v1);
				e[j].ep(i, 3.0+(dis-v2*3.0)/v1);
			}
		}
	}
	dij();
	printf("%.7lf\n", dis[n+1]);
	return 0;
}


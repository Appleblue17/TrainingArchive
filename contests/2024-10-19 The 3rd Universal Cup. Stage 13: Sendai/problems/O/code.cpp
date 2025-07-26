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
ll a[MAXN],b[MAXN];
ll t,x,y,ans,k;
const int N_MAX = 1000, E_MAX = 1000000;

struct Edge
{
	int to, next;
};

int n, m;
vector <int> g[N_MAX + 10];

int opp[N_MAX + 10];
bool vis[N_MAX + 10];

bool vx[N_MAX + 10], vy[N_MAX + 10];

void addEdge(int x, int y)
{
	//printf("addEdge(%d,%d)\n",x,y);
	g[x].push_back(y);
}

bool find(int x)
{
	if (vis[x]) return false;
	vis[x] = true;
	for (int i = 0; i < (int) g[x].size(); i++) {
		int y = g[x][i];
		if (opp[y] == 0 || find(opp[y])) {
			opp[y] = x;
			return true;
		}
	}
	return false;
}

void mark(int x)
{
	if (vx[x]) return;
	vx[x] = true;
	for (int i = 0; i < (int) g[x].size(); i++) {
		int y = g[x][i];
		if (opp[y] && !vy[y]) {
			vy[y] = true;
			mark(opp[y]);
		}
	}
}

int hungary()
{
	memset(opp, 0, sizeof(opp));
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		memset(vis, false, sizeof(vis));
		ans += find(i);
	}
	return ans;
}

int maxIndSet()
{
	int ans = hungary();
	memset(vis, false, sizeof(vis));
	for (int i = 1; i <= m; i++)
		vis[opp[i]] = true;
	memset(vx, false, sizeof(vx));
	memset(vy, false, sizeof(vy));
	for (int i = 1; i <= n; i++)
		if (!vis[i]) mark(i);
	return n + m - ans;
}
int N,M,id[510],l[510],r[510];
int main()
{
	scanf("%d%d",&N,&M);
	for(int i=1;i<=M;i++){
		scanf("%d%d",&l[i],&r[i]);
		if(l[i]%2==1){
			n++;
			id[i]=n;
		}
		else{
			m++;
			id[i]=m;
		}
	}
	for(int i=1;i<=M;i++){
		for(int j=i+1;j<=M;j++){
			//printf("i=%d,j=%d\n",i,j);
			if((l[i]&1) != (l[j]&1)){
				//printf("%d,%d\n",l[i]&1,l[j]&1);
			//	if((abs(l[i]-l[j])&2)){
					//printf("*\n");
					if(!((r[i]<l[j] || r[j] < l[i]) || ((l[i] <= l[j] && r[j] <= r[i])||(l[j]<=l[i] && r[i]<=r[j])))){
						//int t0=0;
						//int t1 = r[j]-l[i];
						//int t2 = r[i]-l[j];
						//if(t1<0)t0=t2;
						//else t0 = t1;
						//if(t0&2){
							if(l[i]&1)addEdge(id[i],id[j]);
							else addEdge(id[j],id[i]);
						//}
						
					}
			//	}
			}
		}
	}
	ans = maxIndSet();
	printf("%lld\n",ans);
	/*for (int i = 1; i <= n; i++)
		if (vx[i]) printf("%d ", i);
	puts("");
	for (int i = 1; i <= m; i++)
		if (!vy[i]) printf("%d ", i);
	puts("");
	return 0;*/
}

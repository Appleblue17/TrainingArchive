#pragma GCC optimize(3)
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
int n, m;
char str[N];
int state[N];
vector<pii> e[N];
int dep[N], dfn[N]; ll dis[N];
int ft[N][18];
vector<int> leaf;
int leafcnt;
ll bel[N];
int seq[N<<1], timer, pos[N], lg[N<<1];
void dfs(int x, int fa){
	dfn[x]=++dfn[0];
	seq[++timer]=x; pos[x]=timer;
	bool isleaf=1;
	ft[x][0]=fa;
	for(int i=1; ft[x][i-1]; ++i) ft[x][i]=ft[ft[x][i-1]][i-1];
	for(auto edg:e[x]) if(edg.fi^fa){
		dep[edg.fi]=dep[x]+1; dis[edg.fi]=dis[x]+edg.se;
		isleaf=false;
		dfs(edg.fi, x);
		bel[x]|=bel[edg.fi];
		seq[++timer]=x;
	}
	if(isleaf){
		bel[x]=1ll<<(ll)leaf.size();
		leaf.ep(x);
	}
}
int st[20][N<<1];
inline void lca_pre(){
	for(int i=2;i<=timer;i++) lg[i]=lg[i>>1]+1;
	for(int i=1;i<=timer;i++) st[0][i]=seq[i];
	for(int i=1;i<=lg[timer];i++){
		for(int j=1;j+(1<<i)-1<=timer;j++){
			st[i][j]=dep[st[i-1][j]]<dep[st[i-1][j+(1<<(i-1))]]?
			st[i-1][j]:st[i-1][j+(1<<(i-1))];
		}
	}
}
inline int lca(int x,int y){
	if(x==0||y==0) return x|y;
	x=pos[x];y=pos[y];
	if(x>y) x^=y^=x^=y;
	int t=lg[y-x+1];
	return dep[st[t][x]]<dep[st[t][y-(1<<t)+1]]?
	st[t][x]:st[t][y-(1<<t)+1];
}
struct sgt{
	int mx[N<<2], mn[N<<2];
	inline int cmp(int x, int y){
		if(x==0||y==0) return x|y;
		return dep[x]>dep[y]?x:y;
	}
	inline int cmp2(int x, int y){
		if(x==0||y==0) return x|y;
		return dep[x]<dep[y]?x:y;
	}
	inline void up(int p){
		mx[p]=cmp(mx[p<<1], mx[p<<1|1]);
		mn[p]=cmp2(mn[p<<1], mn[p<<1|1]);
	}
	void mdf(int p, int l, int r, int x, int v){
		if(l==r){
			mx[p]=mn[p]=v;
			return ;
		}
		int mid=(l+r)>>1;
		if(x<=mid) mdf(p<<1, l, mid, x, v);
		else mdf(p<<1|1, mid+1, r, x, v);
		up(p);
	}
	int getmx(int p, int l, int r, int L, int R){
		if(L<=l&&r<=R) return mx[p];
		int mid=(l+r)>>1, ret=0;
		if(L<=mid) ret=getmx(p<<1, l, mid, L, R);
		if(R>mid) ret=cmp(ret, getmx(p<<1|1, mid+1, r, L, R));
		return ret;
	}
	int getmn(int p, int l, int r, int L, int R){
		if(L<=l&&r<=R) return mn[p];
		int mid=(l+r)>>1, ret=0;
		if(L<=mid) ret=getmn(p<<1, l, mid, L, R);
		if(R>mid) ret=cmp2(ret, getmn(p<<1|1, mid+1, r, L, R));
		return ret;
	}
}T[55];
bool vis[N];
inline bool cmp(int x, int y){
	return dfn[x]<dfn[y];
}
int main(){
	// freopen("D:\\nya\\acm\\A\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\A\\test.out","w",stdout);
	read(n); read(m);
	scanf("%s", str+1);
	for(int i=1; i<=n; ++i) state[i]=str[i]=='1';
	for(int i=1, x, y, w; i<n; ++i){
		read(x); read(y); read(w);
		e[x].ep(y, w); e[y].ep(x, w);
	}
	dep[1]=1;
	dfs(1, 0);
	lca_pre();
	leafcnt=(int)leaf.size();
	for(int i=1; i<=n; ++i) if(state[i]){
		for(int j=0; j<leafcnt; ++j) if((bel[i]>>j)&1){
			T[j].mdf(1, 1, n, i, i);
		}
	}
	int op, x, l, r;
	while(m--){
		read(op);
		if(op==1){
			read(x);
			state[x]^=1;
			for(int j=0; j<leafcnt; ++j) if((bel[x]>>j)&1){
				T[j].mdf(1, 1, n, x, x*state[x]);
			}
		}
		else{
			read(l); read(r);
			int alllca=0;
			for(int i=0; i<leafcnt; ++i){
				alllca=lca(alllca, T[i].getmn(1, 1, n, l, r));
			}
			if(alllca==0){
				printf("-1\n");
				continue;
			}
			ll ans=0;
			vector<int> vec;
			vec.ep(alllca);
			vis[alllca]=true;
			for(int i=0; i<leafcnt; ++i){
				int x=T[i].getmx(1, 1, n, l, r);
				if(x!=0&&!vis[x]) vis[x]=true, vec.ep(x);
			}
			sort(vec.begin(), vec.end(), cmp);
			for(int i=0; i+1<(int)vec.size(); ++i) {
				ans+=dis[vec[i]]+dis[vec[i+1]]-(dis[lca(vec[i], vec[i+1])]<<1ll);
			}
			ans+=dis[vec.back()]-dis[alllca];
			for(int t:vec) vis[t]=false;
			printf("%lld\n", ans);
		}
	}
	return 0;
}


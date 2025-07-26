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
int Test, n, K, m, rt;
int perm[N];
vector<int> e[N];
namespace TREE{
	int f[N][21];
	vector<int> d[N][21];
	inline void dfs(int x, int fa){
		f[x][1]=fa;
		for(auto y:e[x]) if(y^fa) dfs(y, x);
	}
	inline void init(){
		for(int i=1; i<=rt; ++i) for(int j=0; j<=K; ++j) d[i][j].clear(), f[i][j]=0;
		dfs(rt, 0);
		for(int i=1; i<=rt; ++i){
			int x=i;
			for(int j=0; j<=K&&x; ++j){
				d[x][j].emplace_back(i);
				f[i][j]=x;
				x=f[x][1];
			}
		}
	}
};
struct node{
	int l, r, c;
	inline bool operator <(const node &t)const{
		if(l!=t.l) return l<t.l;
		return r<t.r;
	}
};
set<node> s;
namespace BIT{
	int tr[N];
	inline void clr(){
		for(int i=1; i<=n; ++i) tr[i]=0;
	}
	inline void addd(int x, int v){
		for(; x; x-=(x&-x)) tr[x]+=v;
	}
	inline void add(int l, int r, int x){
		addd(r, x); addd(l-1, -x);
	}
	inline int get(int p){
		int ret=0;
		for(; p<=n; p+=(p&-p)) ret+=tr[p];
		return ret;
	}
}
namespace DS{
	int que[N], hh, tt;
	int bfn[N], seq[N];
	int lb[N][21], rb[N][21];
	inline void init(){
		for(int i=1; i<=rt; ++i) bfn[i]=0;
		que[hh=tt=1]=rt;
		while(hh<=tt){
			int x=que[hh]; bfn[x]=hh; seq[hh]=x; ++hh;
			for(auto y:e[x]) if(!bfn[y]) que[++tt]=y;
		}
		for(int i=1; i<=rt; ++i){
			for(int j=0; j<=K; ++j) {
				lb[i][j]=rt+1; rb[i][j]=0;
				for(auto t:(TREE::d[i][j])){
					lb[i][j]=min(lb[i][j], bfn[t]);
					rb[i][j]=max(rb[i][j], bfn[t]);
				}
			}
		}
	}
};
typedef set<node>::iterator IT;
inline void mdfff(int l, int r, int c){
	l=max(l, 41);
	if(l>r) return ;
	IT cur=s.lower_bound((node){r+1, 0, 0});
	--cur;
	vector<IT> vec;
	vector<node> vec2;
	while((*cur).r>=l){
		int l2=(*cur).l, r2=(*cur).r, c2=(*cur).c;
		vec.ep(cur);
		if(l<=l2&&r2<=r){
			BIT::add(c2+1, c, r2-l2+1);
		}
		else if(l2<l&&r2<=r){
			BIT::add(c2+1, c, r2-l+1);
			vec2.push_back((node){l2, l-1, c2});
		}
		else if(l<=l2&&r<r2){
			BIT::add(c2+1, c, r-l2+1);
			vec2.push_back((node){r+1, r2, c2});
		}
		else{
			BIT::add(c2+1, c, r-l+1);
			vec2.push_back((node){l2, l-1, c2});
			vec2.push_back((node){r+1, r2, c2});
		}
		if(cur==s.begin()) break;
		--cur;
	}
	for(auto t:vec) s.erase(t);
	s.insert((node){l, r, c});
	for(auto t:vec2) s.insert(t);
}
inline void mdff(int x, int k, int v){
	if(TREE::d[x][k].empty()) return ;
	mdfff(DS::lb[x][k], DS::rb[x][k], v);
}
inline void mdf(int x, int v){
	int k=K;
	while(k>=0){
		mdff(x, k, v);
		if(k-1>=0) mdff(x, k-1, v);
		--k; x=TREE::f[x][1];
	}
}
vector<pii> qry[N];
inline void clr(){
	for(int i=1; i<=n+40; ++i) {
		e[i].clear(); qry[i].clear();
	}
	BIT::clr();
}
int ans[500005];
int main(){
	// freopen("D:\\nya\\acm\\C\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\C\\test.out","w",stdout);
	read(Test);
	while(Test--) {
		read(n); read(K); read(m);
		clr();
		for(int i=1, x, y; i<n; ++i){
			read(x); read(y); e[x].emplace_back(y); e[y].emplace_back(x);
		}
		e[n+1].emplace_back(1);
		for(int i=n+2; i<=n+40; ++i) e[i].emplace_back(i-1);
		rt=n+40;
		TREE::init();
		DS::init();
		s.clear();
		s.insert((node){41, n+40, 0});
		for(int i=1, l, r; i<=m; ++i){
			read(l); read(r);
			qry[r].ep(l, i);
		}
		for(int i=1; i<=n; ++i){
			mdf(i, i);
			for(auto t:qry[i]) ans[t.se]=BIT::get(t.fi);
		}
		for(int i=1; i<=m; ++i) printf("%d\n", ans[i]);
	}
	return 0;
}


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
const int N=5e5+5;
int n, m;
const int inf=1e9;
struct node{
	int u, d, id;
	inline bool operator <(const node &t)const{
		return id<t.id;
	}
};
map<int, vector<node> > vec;
struct rec{
	int l, r, u, d, id;
	inline bool operator <(const rec &t)const{
		if(l!=t.l) return l<t.l;
		return r<t.r;
	}
}p[N];
void insrec(int l, int r, int u, int d, int id){
	p[id]=(rec){l, r, u, d, id};
	vec[l].push_back((node){u, d, id});
	vec[r+1].push_back((node){u, d, -id});
}
vector<int> e[N];
int fa[N], dep[N];
int top[N], dfn[N], pos[N], lp[N], rp[N], timer, sz[N], son[N];
void dfs(int x){
	sz[x]=1;
	for(auto y:e[x]){
		dfs(y);
		sz[x]+=sz[y];
		if(sz[y]>sz[son[x]]) son[x]=y;
	}
}
void dfs2(int x, int tp){
	top[x]=tp;
	dfn[x]=++timer; lp[x]=timer; pos[timer]=x;
	if(son[x]) dfs2(son[x], tp);
	for(auto y:e[x]) if(y^son[x]) dfs2(y, y);
	rp[x]=timer;
}
bool sta[N];
struct BIT{
	int tr[N];
	inline void addd(int x, int v){
		for(; x<=n+1; x+=(x&-x)) tr[x]+=v;
	}
	inline void add(int l, int r, int v){
		if(l==0) ++l;
		if(l>r) return ;
		addd(l, v); addd(r+1, -v);
	}
	inline int get(int x){
		int ret=0;
		for(; x; x-=(x&-x)) ret+=tr[x];
		return ret;
	}
}w;
struct BIT2{
	int tr[N];
	inline void add(int x, int v){
		for(; x<=n+1; x+=(x&-x)) tr[x]+=v;
	}
	inline int gett(int x){
		int ret=0;
		for(; x; x-=(x&-x)) ret+=tr[x];
		return ret;
	}
	inline int get(int l, int r){
		return gett(r)-gett(l-1);
	}
}T;
void getchain(int x, vector<pii> &chain){
	while(x){
		chain.ep(dfn[top[x]], dfn[x]);
		x=fa[top[x]];
	}
	reverse(chain.begin(), chain.end());
}
int main(){
	// freopen("D:\\nya\\acm\\B\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\B\\test.out","w",stdout);
	read(n); read(m);
	for(int i=1, l, r, u, d; i<=n; ++i){
		read(l); read(u); read(r); read(d);
		insrec(l, r, u, d, i);
	}
	sort(p+1, p+n+1);
	set<pii> s;
	s.insert(mapa(0, 0)); s.insert(mapa(inf+1, 0));
	for(auto if1:vec){
		sort(if1.se.begin(), if1.se.end());
		for(auto if2:if1.se){
			int u=if2.u, d=if2.d, id=if2.id;
			if(id>0){
				set<pii>::iterator it=s.lower_bound({u, -1});
				--it;
				int faid=(*it).se;
				e[faid].ep(id);
				fa[id]=faid;
				dep[id]=dep[faid]+1;
				s.insert(mapa(d, faid));
				s.insert(mapa(u, id));
			}
			else{
				s.erase(s.find(mapa(d, fa[-id])));
				s.erase(s.find(mapa(u, -id)));
			}
		}
	}
	dfs(0); dfs2(0, 0);
	while(m--){
		char s[2]; int x;
		scanf("%s", s+1);
		read(x);
		if(s[1]=='^'){
			vector<pii> chain;
			getchain(x, chain);
			int lim=0, val=1;
			if(sta[x]) lim=1, val=-1;
			int l=0, r=chain.size()-1, mid, ret=-1;
			while(l<=r){
				mid=(l+r)>>1;
				if(T.get(lp[pos[chain[mid].se]], rp[pos[chain[mid].se]])==lim){
					ret=mid; r=mid-1;
				}
				else {
					l=mid+1;
				}
			}
			if(ret!=-1){
				l=chain[ret].fi, r=chain[ret].se-1, ret=chain[ret].se;
				while(l<=r){
					mid=(l+r)>>1;
					if(T.get(lp[pos[mid]], rp[pos[mid]])==lim) ret=mid, r=mid-1;
					else l=mid+1;
				}
				w.add(dep[pos[ret]], dep[x], val);
			}
			T.add(dfn[x], val);

			sta[x]^=1;
		}
		else{
			printf("%d\n", w.get(x+1));
		}
	}
	return 0;
}


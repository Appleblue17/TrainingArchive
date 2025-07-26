#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
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
const int N=1e6+5;
int n, q;
int w[N];
int lin[N], nxt[N*2], to[N*2], val[N*2], tot;
inline void in(int x, int y, int z){
	nxt[++tot]=lin[x]; lin[x]=tot; to[tot]=y; val[tot]=z;
	nxt[++tot]=lin[y]; lin[y]=tot; to[tot]=x; val[tot]=z;
}
namespace LCA{
	int dfntot=0;
	int dfn[N<<1],dep[N<<1],pos[N];
	inline void get_dfn(int x,int fa,int timer){
		dfn[++dfntot]=x;pos[x]=dfntot;dep[x]=timer;
		for(int i=lin[x];i;i=nxt[i]){
			if(to[i]==fa) continue;get_dfn(to[i],x,timer+1);
			dfn[++dfntot]=x;
		}
	}
	int lg[N<<1],st[25][N<<1];
	inline void lca_pre(){
		get_dfn(1,0,1);
		for(int i=2;i<=dfntot;i++) lg[i]=lg[i>>1]+1;
		for(int i=1;i<=dfntot;i++) st[0][i]=dfn[i];
		for(int i=1;i<=lg[dfntot];i++){
			for(int j=1;j+(1<<i)-1<=dfntot;j++){
				st[i][j]=dep[st[i-1][j]]<dep[st[i-1][j+(1<<(i-1))]]?
				st[i-1][j]:st[i-1][j+(1<<(i-1))];
			}
		}
	}
	inline int lca(int x,int y){
		x=pos[x];y=pos[y];
		if(x>y) x^=y^=x^=y;
		int t=lg[y-x+1];
		return dep[st[t][x]]<dep[st[t][y-(1<<t)+1]]?
		st[t][x]:st[t][y-(1<<t)+1];
	}
}
int dfn[N], tim;
ll dis[N];
void dfs1(int x, int fa){
	dfn[x]=++tim;
	for(int i=lin[x]; i; i=nxt[i]){
		int y=to[i]; if(y==fa) continue;
		dis[y]=dis[x]+val[i];
		dfs1(y, x);
	}
}
int qx[N]; ll qk[N];
int ans[N];
int seq[N], _seq[N];
int node[N];
int s[N], k;
int vis[N];
inline bool cmp(int x,int y){return dfn[x]<dfn[y];}
int stk[N], top;
vector<int> vec[N];
void add(int x,int y){
	vec[x].ep(y);
	vec[y].ep(x);
}
ll mxup[N], mxdown[N];
inline void build(){
	sort(s+1,s+k+1,cmp);
	stk[top=1]=1;vec[1].clear();
	for(int i=1;i<=k;++i){
		if(s[i]==1) continue;
		int lc=LCA::lca(s[i],stk[top]);
		if(lc!=stk[top]){
			while(dfn[stk[top-1]]>dfn[lc]) add(stk[top],stk[top-1]),top--;
			if(lc!=stk[top-1]) vec[lc].clear(),add(lc,stk[top]),stk[top]=lc;
			else add(lc,stk[top]),top--;
		}
		vec[s[i]].clear();stk[++top]=s[i];
	}
	for(int i=1;i<top;i++) add(stk[i],stk[i+1]);
}
inline void dfs2(int x, int fa){
	if(vis[x]==2) mxdown[x]=0;
	else mxdown[x]=-1e18;
	for(auto y:vec[x]) if(y^fa){
		dfs2(y, x);
		mxdown[x]=max(mxdown[y]+dis[y]-dis[x], mxdown[x]);
	}
}
inline void dfs3(int x, int fa, ll dist){
	if(vis[x]==2){
		dist=max(dist, 0ll);
	}
	mxup[x]=dist;
	ll mx1=dist, mx2=-1e18;
	for(auto y:vec[x]) if(y^fa) {
		ll curd=dis[y]-dis[x];
		if(curd+mxdown[y]>=mx1){
			mx2=mx1; mx1=curd+mxdown[y];
		}
		else{
			mx2=max(mx2, curd+mxdown[y]);
		}
	}
	for(auto y:vec[x]) if(y^fa){
		ll curd=dis[y]-dis[x];
		if(mx1!=mxdown[y]+curd) dfs3(y, x, mx1+curd);
		else dfs3(y, x, mx2+curd);
	}
}
inline void solve(int lv, int rv, int lp, int rp){
	// cout<<"cur:"<<lv<<' '<<rv<<endl;
	// cout<<"qry:";
	// for(int i=lp; i<=rp; ++i) cout<<seq[i]<<' ';
	// cout<<endl;
	if(lp>rp) return ;
	if(lv==rv){
		for(int i=lp; i<=rp; ++i) ans[seq[i]]=lv;
		return ;
	}
	int mid=(lv+rv)>>1;
	k=0;
	for(int i=lv; i<=mid; ++i){
		s[++k]=node[i], vis[node[i]]=2;
	}
	for(int i=lp; i<=rp; ++i) if(!vis[qx[seq[i]]]) s[++k]=qx[seq[i]], vis[qx[seq[i]]]=1;
	build();
	dfs2(1, 0);
	dfs3(1, 0, -1e18);
	for(int i=1;i<=k;i++) vis[s[i]]=0;
	int nlp=lp-1, nrp=rp+1;
	for(int i=lp; i<=rp; ++i){
		// cout<<seq[i]<<' '<<qx[seq[i]]<<' '<<qk[seq[i]]<<' '<<mxup[qx[seq[i]]]<<' '<<mxdown[qx[seq[i]]]<<endl;
		if(max(mxup[qx[seq[i]]], mxdown[qx[seq[i]]])>qk[seq[i]]){
			_seq[++nlp]=seq[i];
		}
		else{
			_seq[--nrp]=seq[i];
		}
	}
	for(int i=lp; i<=rp; ++i) seq[i]=_seq[i];
	solve(lv, mid, lp, nlp);
	solve(mid+1, rv, nrp, rp);
}
int main(){
	// freopen("D:\\nya\\acm\\C\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\C\\test.out","w",stdout);
	read(n); read(q);
	for(int i=1; i<=n; ++i) {
		read(w[i]);
		if(w[i]<=n) node[w[i]]=i;
	}
	for(int i=1, x, y, z; i<n; ++i){
		read(x); read(y); read(z);
		in(x, y, z);
	}
	dfs1(1, 0);
	LCA::lca_pre();
	for(int i=1; i<=q; ++i) read(qx[i]), read(qk[i]), seq[i]=i;
	int mxv=0;
	while(node[mxv]) ++mxv;
	solve(0, mxv, 1, q);
	for(int i=1; i<=q; ++i) printf("%d\n", ans[i]);
	return 0;
}


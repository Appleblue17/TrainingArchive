#pragma GCC optimize(2)
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
template <typename T>inline void read(T &x){
	x=0;char c=getchar();bool f=0;
	for(;c<'0'||c>'9';c=getchar()) f|=(c=='-');
	for(;c>='0'&&c<='9';c=getchar())
	x=(x<<1)+(x<<3)+(c^48);
	x=(f?-x:x);
}
const int N=40005, M=1e6+5; 
mt19937 rnd(time(0));
inline int ran(int l, int r){
	return rnd()%(r-l+1)+l;
}
int n, m;
int fx[M], fy[M];
int fa[N], sz[N], val[N];
inline int getf(int x){
	if(x==fa[x]) return x;
	return getf(fa[x]);
}
int stk[M*2], top;
int memfa[M*2], memsz[M*2], memval[M*2];
inline bool merge(int x, int y){
	x=getf(x); y=getf(y);
	if(x==y) return false;
	if(sz[x]<sz[y]) swap(x, y);
	stk[++top]=y; 
	memfa[top]=fa[y]; memsz[top]=sz[x]; memval[top]=val[x];
	fa[y]=x;
	sz[x]+=sz[y]; val[x]+=val[y];
	return true;
}
inline void back(){
	int y=stk[top];
	int x=fa[y];
	fa[y]=memfa[top]; sz[x]=memsz[top]; val[x]=memval[top];
	--top;
}
unordered_map<int, int> h;
bitset<10005> dp, fdp[10005];
const int bs=5005;
inline bool check(bool flg){
	if(!flg) return true;
	h.clear();
	for(int i=1; i<=n*2; ++i) if(getf(i)==i) h[abs(val[i])]+=1;
	dp.reset();
	dp[bs]=1;
	int cnt1=0;
	for(auto t:h) {
		if(t.fi==0) continue;
		if(t.fi==1) {
			cnt1=t.se>>1; continue;
		}
		int lim=ran(n-800, n);
		if(t.se>lim) dp=(dp<<t.fi)|(dp>>t.fi);
		else {
			for(int j=min(t.se>>1, 50); j>=1; --j) dp=(dp<<t.fi)|(dp>>t.fi);
		}
	}
	for(int i=cnt1; i>=-cnt1; i-=2) if(bs-i>=0&&bs-i<10005&&dp[bs-i]==1) return true;
	return false;
}
int res[N];
bool vis[N];
vector<int> e[N];
vector<pii> vec;
inline void dfs(int x){
	if(vis[(x>n)?x-n:x]) return ;
	vis[(x>n)?x-n:x]=1;
	vis[(x<=n)?x+n:x]=1;
	for(auto y:e[x]) dfs(y);
}
int main(){
	// freopen("D:\\nya\\test.in","r",stdin);
	// freopen("D:\\nya\\test.out","w",stdout);
	read(n); read(m);
	memset(res, -1, sizeof res);
	for(int i=1; i<=m; ++i){
		read(fx[i]); read(fy[i]);
	}
	n<<=1;
	for(int i=1; i<=n*2; ++i){
		fa[i]=i; sz[i]=1; val[i]=(i<=n)?1:-1;
	}
	for(int i=m; i>=1; --i){
		int lst=top;
		bool flg=1;
		flg&=merge(fx[i], fy[i]+n); flg&=merge(fy[i], fx[i]+n);
		if(getf(fx[i])!=getf(fx[i]+n)&&getf(fy[i])!=getf(fy[i]+n)&&check(flg)){
			e[fx[i]].emplace_back(fy[i]);
			e[fy[i]].emplace_back(fx[i]);
			continue;
		}
		while(top>lst) back();
	}
	for(int i=1; i<=2*n; ++i) if(!vis[i]&&getf(i)==i){
		dfs(i); vec.emplace_back(i, val[i]);
	}
	fdp[0][bs]=1;
	for(int i=1; i<=(int)vec.size(); ++i) fdp[i]=(fdp[i-1]>>abs(vec[i-1].se))|(fdp[i-1]<<abs(vec[i-1].se));
	int lst=bs;
	for(int i=(int)vec.size(); i>=1; --i){
		if(fdp[i-1][lst-vec[i-1].se]){
			for(int j=1; j<=n; ++j) {
				int f1=getf(j), f2=getf(j+n);
				if(f1==vec[i-1].fi) res[j]=0;
				else if(f2==vec[i-1].fi) res[j]=1;
			}
			lst-=vec[i-1].se;
		}
		else if(fdp[i-1][lst+vec[i-1].se]){
			for(int j=1; j<=n; ++j) {
				int f1=getf(j), f2=getf(j+n);
				if(f1==vec[i-1].fi) res[j]=1;
				else if(f2==vec[i-1].fi) res[j]=0;
			}
			lst+=vec[i-1].se;
		}
	}
	for(int i=1; i<=n; ++i) putchar(res[i]+'0');
	return 0;
}

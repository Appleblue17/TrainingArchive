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
template <typename T>inline void read(T &x){
	x=0;char c=getchar();bool f=0;
	for(;c<'0'||c>'9';c=getchar()) f|=(c=='-');
	for(;c>='0'&&c<='9';c=getchar())
	x=(x<<1)+(x<<3)+(c^48);
	x=(f?-x:x);
}
const int N=3e5+5;
const int mod=993244853;
inline int plu(int x, int y){x+=y; return (x>=mod)?(x-mod):x;}
inline int sub(int x, int y){x-=y; return (x<0)?(x+mod):x;}
int hs[N], bs, pw[N];
int n, m;
char s[N], o[2];
inline int get(int l, int r){
	return sub(hs[r], (ll)hs[l-1]*pw[r-l+1]%mod);
}
vector<pii> a[N], b[N];
int op[N];
vector<int> lena[N], lenb[N];
vector<int> prea[N], preb[N];
inline void init(int x){
	lena[x].emplace_back(0);
	prea[x].emplace_back(0);
	for(auto t:a[x]) lena[x].emplace_back(lena[x].back()+t.se-t.fi+1), prea[x].emplace_back(plu((ll)prea[x].back()*pw[t.se-t.fi+1]%mod, get(t.fi, t.se)));
	lenb[x].emplace_back(0);
	preb[x].emplace_back(0);
	for(auto t:b[x]) lenb[x].emplace_back(lenb[x].back()+t.se-t.fi+1), preb[x].emplace_back(plu((ll)preb[x].back()*pw[t.se-t.fi+1]%mod, get(t.fi, t.se)));
}
inline int getsa(int x, int len){
	int l=0, r=lena[x].size()-1, mid, ret=0;
	while(l<=r){
		mid=(l+r)>>1;
		if(lena[x][mid]<len) ret=mid, l=mid+1;
		else r=mid-1;
	}
	return plu((ll)prea[x][ret]*pw[len-lena[x][ret]]%mod, get(a[x][ret].fi, a[x][ret].fi+(len-lena[x][ret])-1));
}
inline char getssa(int x, int len){
	int l=1, r=lena[x].size()-1, mid, ret=0;
	while(l<=r){
		mid=(l+r)>>1;
		if(lena[x][mid]<len) ret=mid, l=mid+1;
		else r=mid-1;
	}
	return s[a[x][ret].fi+(len-lena[x][ret])-1];
}
inline bool cmp1(int x, int y){
	int l=1, r=min(lena[x].back(), lena[y].back()), mid, ret=0;
	while(l<=r){
		mid=(l+r)>>1;
		if(getsa(x, mid)==getsa(y, mid)) {ret=mid, l=mid+1;}
		else {r=mid-1;}
	}
	if(ret==min(lena[x].back(), lena[y].back())){
		if(lena[x].back()==lena[y].back()) return op[x]>op[y];
		return lena[x].back()<lena[y].back();
	}
	return getssa(x, ret+1)<getssa(y, ret+1);
}
inline int getsb(int x, int len){
	int l=1, r=lenb[x].size()-1, mid, ret=0;
	while(l<=r){
		mid=(l+r)>>1;
		if(lenb[x][mid]<len) ret=mid, l=mid+1;
		else r=mid-1;
	}
	return plu((ll)preb[x][ret]*pw[len-lenb[x][ret]]%mod, get(b[x][ret].fi, b[x][ret].fi+(len-lenb[x][ret])-1));
}
inline char getssb(int x, int len){
	int l=1, r=lenb[x].size()-1, mid, ret=0;
	while(l<=r){
		mid=(l+r)>>1;
		if(lenb[x][mid]<len) ret=mid, l=mid+1;
		else r=mid-1;
	}
	return s[b[x][ret].fi+(len-lenb[x][ret])-1];
}
inline bool cmp2(int x, int y){
	int l=1, r=min(lenb[x].back(), lenb[y].back()), mid, ret=0;
	while(l<=r){
		mid=(l+r)>>1;
		if(getsb(x, mid)==getsb(y, mid)) {ret=mid, l=mid+1;}
		else {r=mid-1;}
	}
	if(ret==min(lenb[x].back(), lenb[y].back())){
		if(lenb[x].back()==lenb[y].back()) return op[x]>op[y];
		return lenb[x].back()<lenb[y].back();
	}
	return getssb(x, ret+1)<getssb(y, ret+1);
}
int rk[N], tt;
int ban[N];
int la[N], ra[N], lb[N], rb[N];
struct node{
	int x, ly, ry, id, val;
}que[N], _que[N];
int tot;
int ans[N];
int tr[N];
inline void add(int x, int v){
	for(; x<=tt; x+=(x&-x)) tr[x]+=v;
}
inline int qry(int l, int r){
	int ret=0;
	for(; r; r-=(r&-r)) ret+=tr[r];
	for(; l; l-=(l&-l)) ret-=tr[l];
	return ret;
}
inline void solve(int l, int r){
	if(l==r) return ;
	int mid=(l+r)>>1;
	solve(l, mid); solve(mid+1, r);
	int lp=l, rp=mid+1, it=l;
	while(lp<=mid||rp<=r){
		if(rp==r+1){
			_que[it]=que[lp]; ++it;
			if(que[lp].id==0) add(que[lp].ly, que[lp].val);
			++lp;
		}
		else if(lp==mid+1){
			_que[it]=que[rp]; ++it;
			if(que[rp].id!=0) ans[que[rp].id]+=qry(que[rp].ly, que[rp].ry)*que[rp].val;
			++rp;
		}
		else if(que[lp].x<=que[rp].x){
			_que[it]=que[lp]; ++it;
			if(que[lp].id==0) add(que[lp].ly, que[lp].val);
			++lp;
		}
		else{
			_que[it]=que[rp]; ++it;
			if(que[rp].id!=0) ans[que[rp].id]+=qry(que[rp].ly, que[rp].ry)*que[rp].val;
			++rp;
		}
	}
	for(int i=l; i<=mid; ++i) if(que[i].id==0) add(que[i].ly, -que[i].val);
	for(int i=l; i<=r; ++i) que[i]=_que[i];
}
int main(){
	// freopen("D:\\nya\\acm\\A\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\A\\test.out","w",stdout);
	read(n); read(m);
	scanf("%s", s+1);
	for(int i=1; i<=n; ++i) s[2*n+1-i]=s[i];
	bs=137;
	pw[0]=1;
	for(int i=1; i<=n*2; ++i) hs[i]=plu((ll)hs[i-1]*bs%mod, s[i]^100), pw[i]=(ll)pw[i-1]*bs%mod;
	int _k, _l, _r;
	for(int i=1; i<=m; ++i){
		scanf("%s", o);
		if(o[0]=='+'){
			read(_k);
			while(_k--){
				read(_l); read(_r); a[i].emplace_back(_l, _r);
			}
			b[i]=a[i];
			reverse(b[i].begin(), b[i].end());
			for(auto &t:b[i]) t.fi=2*n+1-t.fi, t.se=2*n+1-t.se, swap(t.fi, t.se);
			init(i);
			rk[++tt]=i; 
			op[i]=1;
		}
		else if(o[0]=='?') {
			read(_k);
			while(_k--){
				read(_l); read(_r); a[i].emplace_back(_l, _r);
			}
			read(_k);
			while(_k--){
				read(_l); read(_r); b[i].emplace_back(_l, _r);
			}
			reverse(b[i].begin(), b[i].end());
			for(auto &t:b[i]) t.fi=2*n+1-t.fi, t.se=2*n+1-t.se, swap(t.fi, t.se);
			init(i);
			rk[++tt]=i; 
			op[i]=2;
		}
		else {
			read(ban[i]);
		}
	}
	sort(rk+1, rk+tt+1, cmp1);
	for(int i=1; i<=tt; ++i){
		la[rk[i]]=i; 
		int l=i+1, r=tt, mid, ret=i;
		while(l<=r){
			mid=(l+r)>>1;
			if(lena[rk[mid]].back()>=lena[rk[i]].back()&&getsa(rk[mid], lena[rk[i]].back())==prea[rk[i]].back()) {ret=mid; l=mid+1;}
			else {r=mid-1;}
		}
		ra[rk[i]]=ret;
	}
	sort(rk+1, rk+tt+1, cmp2);
	for(int i=1; i<=tt; ++i){
		lb[rk[i]]=i; 
		int l=i+1, r=tt, mid, ret=i;
		while(l<=r){
			mid=(l+r)>>1;
			if(lenb[rk[mid]].back()>=lenb[rk[i]].back()&&getsb(rk[mid], lenb[rk[i]].back())==preb[rk[i]].back()) {ret=mid; l=mid+1;}
			else {r=mid-1;}
		}
		rb[rk[i]]=ret;
	}
	for(int i=1; i<=m; ++i){
		if(op[i]==1){
			que[++tot]=(node){la[i], lb[i], lb[i], 0, 1};
		}
		else if(op[i]==0){
			que[++tot]=(node){la[ban[i]], lb[ban[i]], lb[ban[i]], 0, -1};
		}
		else {
			que[++tot]=(node){la[i]-1, lb[i], rb[i], i, -1};
			que[++tot]=(node){ra[i], lb[i], rb[i], i, 1};
		}
	}
	solve(1, tot);
	for(int i=1; i<=m; ++i) if(op[i]==2) printf("%d\n", ans[i]);
	return 0;
}


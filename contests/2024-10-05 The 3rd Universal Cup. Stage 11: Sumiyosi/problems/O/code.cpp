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
const int mod=998244353;
inline int plu(int x, int y){x+=y; return x>=mod?x-mod:x;}
inline int sub(int x, int y){x-=y; return x<0?x+mod:x;}
const int N=40005, M=1e6+5;
int n, m;
int fx[M], fy[M], fa[N], s1[N], s2[N];
inline int get(int x){
	if(x==fa[x]) return x;
	return fa[x]=get(fa[x]);
}
vector<int> bin[N];
int col[N];
int f[N];
int tag;
inline void add(int x, int y){
	tag+=min(x, y);
	if(x==y) return ;
	int dt=abs(x-y);
	for(int i=n-dt; i>=0; --i) f[i+dt]=plu(f[i+dt], f[i]);
}
inline void del(int x, int y){
	tag-=min(x, y);
	if(x==y) return ;
	int dt=abs(x-y);
	for(int i=0; i<=n-dt; ++i) f[i+dt]=sub(f[i+dt], f[i]);
}
int main(){
	// freopen("D:\\nya\\acm\\B\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\B\\test.out","w",stdout);
	read(n); read(m);
	for(int i=1; i<=m; ++i){
		read(fx[i]); read(fy[i]);
	}
	n<<=1;
	for(int i=1; i<=n; ++i){
		fa[i]=i; s1[i]=1; bin[i].emplace_back(i);
	}
	f[0]=1;
	for(int i=1; i<=n; ++i){
		for(int j=i; j>=1; --j) f[j]=plu(f[j], f[j-1]);
	}
	for(int i=m; i>=1; --i){
		int x=get(fx[i]), y=get(fy[i]);
		int a=fx[i], b=fy[i];
		if(x==y) continue;
		if(bin[x].size()<bin[y].size()) swap(x, y), swap(a, b);
		if(col[a]!=col[b]){
			del(s1[x], s2[x]);
			del(s1[y], s2[y]);
			add(s1[x]+s1[y], s2[x]+s2[y]);
			if(!f[n/2-tag]){
				del(s1[x]+s1[y], s2[x]+s2[y]);
				for(auto t:bin[y]) col[t]^=1;
				add(s1[x]+s2[y], s2[x]+s1[y]);
				s1[x]+=s2[y]; s2[x]+=s1[y];
			}
			else{
				s1[x]+=s1[y]; s2[x]+=s2[y];
			}
		}
		else{
			del(s1[x], s2[x]);
			del(s1[y], s2[y]);
			add(s1[x]+s2[y], s2[x]+s1[y]);
			if(!f[n/2-tag]){
				del(s1[x]+s2[y], s2[x]+s1[y]);
				add(s1[x]+s1[y], s2[x]+s2[y]);
				s1[x]+=s1[y]; s2[x]+=s2[y];
			}
			else{
				for(auto t:bin[y]) col[t]^=1;
				s1[x]+=s2[y]; s2[x]+=s1[y];
			}
		}
		fa[y]=x;
		for(auto t:bin[y]) bin[x].emplace_back(t);
		bin[y].clear();
	}
	for(int i=n; i>=2; --i){
		int x=get(1), y=get(i);
		int a=1, b=i;
		if(x==y) continue;
		if(bin[x].size()<bin[y].size()) swap(x, y), swap(a, b);
		if(col[a]!=col[b]){
			del(s1[x], s2[x]);
			del(s1[y], s2[y]);
			add(s1[x]+s1[y], s2[x]+s2[y]);
			if(!f[n/2-tag]){
				del(s1[x]+s1[y], s2[x]+s2[y]);
				for(auto t:bin[y]) col[t]^=1;
				add(s1[x]+s2[y], s2[x]+s1[y]);
				s1[x]+=s2[y]; s2[x]+=s1[y];
			}
			else{
				s1[x]+=s1[y]; s2[x]+=s2[y];
			}
		}
		else{
			del(s1[x], s2[x]);
			del(s1[y], s2[y]);
			add(s1[x]+s2[y], s2[x]+s1[y]);
			if(!f[n/2-tag]){
				del(s1[x]+s2[y], s2[x]+s1[y]);
				add(s1[x]+s1[y], s2[x]+s2[y]);
				s1[x]+=s1[y]; s2[x]+=s2[y];
			}
			else{
				for(auto t:bin[y]) col[t]^=1;
				s1[x]+=s2[y]; s2[x]+=s1[y];
			}
		}
		fa[y]=x;
		for(auto t:bin[y]) bin[x].emplace_back(t);
		bin[y].clear();
	}
	for(int i=1; i<=n; ++i) putchar(col[i]+'0');
	return 0;
}

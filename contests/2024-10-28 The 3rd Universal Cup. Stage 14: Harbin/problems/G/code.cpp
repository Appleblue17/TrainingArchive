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
#define ep emplace_back
const int N=2e5+5;
int n, m, K;
int tag[N];
unordered_map<int, bool> e[N];
vector<int> vec[N];
inline int calc(int x){
	if(vec[x].empty()) return 0;
	int ret=1;
	for(auto t:vec[x]) ret+=calc(t);
	return ret;
}
inline void work(int x){
	if(vec[x].empty()) return ;
	printf("%d %d ", x, (int)vec[x].size());
	for(auto t:vec[x]) printf("%d ", t);
	putchar('\n');
	for(auto t:vec[x]) work(t);
}
bool vis[N];
int fa[N];
inline int get(int x){
	while(x!=fa[x]){
		x=fa[x]=fa[fa[x]];
	}
	return x;
}
inline void merge(int x, int y){
	x=get(x); y=get(y);
	fa[x]=y;
}
inline void dfs(int x){
	vis[x]=1;
	for(auto t:e[x]) {
		int y=t.fi;
		if(!vis[y]){
			vec[x].emplace_back(y);
			if(!tag[y]) dfs(y);
			else vis[y]=1;
		}
	}
}
int main(){
	// freopen("D:\\nya\\test.in","r",stdin);
	// freopen("D:\\nya\\test.out","w",stdout);
	read(n); read(m); read(K);
	if(K==n){
		printf("No\n");
		return 0;
	}
	for(int i=1; i<=n; ++i) fa[i]=i;
	for(int i=1, x; i<=K; ++i) read(x), tag[x]=1;
	for(int i=1, x, y; i<=m; ++i){
		read(x); read(y);
		e[x][y]=e[y][x]=1;
		if(tag[x]||tag[y]) continue;
		merge(x, y);
	}
	int be=1;
	while(tag[be]) ++be;
	for(int i=be+1; i<=n; ++i) if((!tag[i])&&(get(i)!=get(be))){
		printf("No\n");
		return 0;
	}
	dfs(be);
	for(int i=1; i<=n; ++i) if(tag[i]&&(!vis[i])){
		printf("No\n");
		return 0;
	}
	printf("Yes\n");
	printf("%d\n", calc(be));
	work(be);
	return 0;
}

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
const int N=1e5+5;
int n;
int fa[N];
vector<int> e[N];
char s[6]; int tp[N], dep[N];
bool vis[N];
int match[N];
void fail(){
	printf("NO\n");
	exit(0);
}
//Duan 1
//Chang 2
//Tong 3
inline bool cmp(int x, int y){
	return dep[x]<dep[y];
}
inline int dfs(int x){
	dep[x]=dep[fa[x]]+1;
	vector<int> Tong, Duan, Chang;
	if(tp[x]==3) Tong.ep(x);
	if(tp[x]==1) Duan.ep(x);
	if(tp[x]==2) Chang.ep(x);
	for(auto y:e[x]) {
		int u=dfs(y);
		if(u==0) continue;
		if(tp[u]==3) Tong.ep(u);
		if(tp[u]==2) Chang.ep(u);
		if(tp[u]==1) Duan.ep(u);
	}
	vector<int> Tres, Dres, Cres;
	/*
	cout<<"cur:"<<x<<endl;
	for(auto t:Tong) cout<<t<<' ';
	cout<<endl;
	for(auto t:Duan) cout<<t<<' ';
	cout<<endl;
	for(auto t:Chang) cout<<t<<' ';
	cout<<endl;
	*/
	//Tong
	sort(Tong.begin(), Tong.end(), cmp);
	for(int l=0, r; l<(int)Tong.size(); ){
		r=l;
		while(r+1<(int)Tong.size()&&dep[Tong[r+1]]==dep[Tong[l]]) ++r;
		for(int i=l; i+1<=r; i+=2) match[Tong[i]]=Tong[i+1], match[Tong[i+1]]=Tong[i];
		if((r-l+1)&1) Tres.ep(Tong[r]);
		l=r+1;
	}
	//Duan & Chang
	set<pair<int, int> > s;
	sort(Duan.begin(), Duan.end(), cmp);
	for(auto t:Chang) s.insert(mapa(dep[t], t));
	for(int i=(int)Duan.size()-1; i>=0; --i){
		// cout<<Duan[i]<<' '<<dep[Duan[i]]<<endl;
		set<pair<int, int> >::iterator it=s.lower_bound(mapa(dep[Duan[i]]+1, 0));
		if(it==s.end()){
			Dres.ep(Duan[i]);
			continue;
		}
		match[Duan[i]]=(*it).se;
		match[(*it).se]=Duan[i];
		s.erase(it);
	}
	for(auto t:s) Cres.ep(t.se);
	vector<int> up;
	for(auto t:Tres) up.ep(t);
	for(auto t:Dres) up.ep(t);
	for(auto t:Cres) up.ep(t);
	if(up.empty()) return 0;
	if(up.size()>1) fail();
	return up[0];
}
int main(){
	// freopen("D:\\nya\\acm\\C\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\C\\test.out","w",stdout);
	read(n); 
	for(int i=2, x; i<=n; ++i){
		read(x); read(fa[x]); scanf("%s", s);
		if(s[0]=='D') tp[x]=1;
		else if(s[0]=='C') tp[x]=2;
		else if(s[0]=='T') tp[x]=3;
		e[fa[x]].ep(x);
	}
	if(dfs(1)) fail();
	printf("YES\n");
	for(int i=1; i<=n; ++i) if(match[i]&&!vis[i]){
		printf("%d %d\n", i, match[i]);
		vis[i]=vis[match[i]]=1;
	}
	return 0;
}

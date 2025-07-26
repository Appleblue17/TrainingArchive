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
#define ep emplace_back
template <typename T>inline void read(T &x){
	x=0;char c=getchar();bool f=0;
	for(;c<'0'||c>'9';c=getchar()) f|=(c=='-');
	for(;c>='0'&&c<='9';c=getchar())
	x=(x<<1)+(x<<3)+(c^48);
	x=(f?-x:x);
}
const int N=1e5+5;
int n, w;
char s[N];
int a[N], p[N];
vector<int> occ[26];
vector<int> ban[N];
int sa[N], rk[N], oldrk[N];
void get_sa(){
  	for(int i=1; i<=n; ++i) sa[i]=i, rk[i]=a[i];
	for(w=1; w<n; w<<=1) {
    	sort(sa+1, sa+n+1, [&](int x, int y) {return rk[x]==rk[y]?rk[x+w]<rk[y+w]:rk[x]<rk[y];});  
		memcpy(oldrk, rk, sizeof(rk));
    	for (int p=0, i=1; i<=n; ++i) {
			if (oldrk[sa[i]]==oldrk[sa[i-1]]&&oldrk[sa[i]+w]==oldrk[sa[i-1]+w]) {
				rk[sa[i]]=p;
			} else {
				rk[sa[i]]=++p;
			}
		}
  	}
}
int ht[N];
void get_ht(){
	for(int i=1; i<=n; ++i) rk[sa[i]]=i;
	for(int i=1, k=0; i<=n; ++i){
		if(rk[i]==1) continue;
		if(k) k--;
		int j=sa[rk[i]-1];
		while(i+k<=n&&j+k<=n&&a[i+k]==a[j+k]) k++;
		ht[rk[i]]=k;
	}
}
int st[N][20], lg[N];
void build(){
	for(int i=2; i<=n; ++i) lg[i]=lg[i>>1]+1;
	for(int i=1; i<=n; ++i) st[i][0]=ht[i];
	for(int t=1; t<=lg[n]; ++t){
		for(int i=1; i+(1<<t)-1<=n; ++i){
			st[i][t]=min(st[i][t-1], st[i+(1<<(t-1))][t-1]);
		}
	}
}
inline int lcp(int x, int y){
	if(x==y) return n-x+1;
	x=rk[x]; y=rk[y];
	if(x>y) swap(x, y);
	++x;
	int t=lg[y-x+1];
	return min(st[x][t], st[y-(1<<t)+1][t]);
}
inline int getv(int l, int len){
	for(auto t:ban[l]) if(t==len) {
		return 0;
	}
	return a[l+len-1];
}
inline int lcpp(int x, int y){
	if(x>y) swap(x, y);
	vector<pii> tem;
	int it1=0, it2=0;
	while(it1<(int)ban[x].size()||it2<(int)ban[y].size()){
		if(it1==(int)ban[x].size()){
			if(!tem.empty()&&tem.back().fi==ban[y][it2]){
				tem.back().se+=2;
			}
			else tem.ep(ban[y][it2], 2); 
			++it2;
		}
		else if(it2==(int)ban[y].size()){
			if(!tem.empty()&&tem.back().fi==ban[x][it1]){
				tem.back().se+=1;
			}
			else tem.ep(ban[x][it1], 1); 
			++it1;
		}
		else {
			if(ban[x][it1]<=ban[y][it2]){
				if(!tem.empty()&&tem.back().fi==ban[x][it1]){
					tem.back().se+=1;
				}
				else tem.ep(ban[x][it1], 1); 
				++it1;
			}
			else{	
				if(!tem.empty()&&tem.back().fi==ban[y][it2]){
					tem.back().se+=2;
				}
				else tem.ep(ban[y][it2], 2);
				++it2;
			}
		}
	}
	while(!tem.empty()&&tem.back().fi>n-y+1) tem.pop_back();
	int ret=0; 
	for(auto t:tem){
		int w=lcp(x+ret, y+ret);
		if(w<t.fi-ret-1){
			ret+=w;
			return ret;
		}
		ret=t.fi-1;
		if(t.se==3){
			++ret;
		}
		else if(t.se==2&&a[x+ret]==0){
			++ret;
		}
		else if(t.se==1&&a[y+ret]==0){
			++ret;
		}
		else{
			return ret;
		}
	}
	if(ret!=n-y+1) ret+=lcp(x+ret, y+ret);
	return ret;
}
inline bool cmp(int x, int y){
	int t=lcpp(x, y);
	if(t==n-max(x, y)+1){
		return x>y;
	}
	else{
		return getv(x, t+1)<getv(y, t+1);
	}
}
int main(){
	// freopen("D:\\nya\\acm\\A\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\A\\test.out","w",stdout);
	read(n);
	scanf("%s", s+1);
	for(int i=1; i<=n; ++i){
		if(occ[s[i]-'a'].empty()) a[i]=0;
		else a[i]=i-occ[s[i]-'a'].back();
		occ[s[i]-'a'].ep(i);
		p[i]=i;
	}
	for(int i=1; i<=n; ++i){
		for(int j=0; j<26; ++j){
			if(lower_bound(occ[j].begin(), occ[j].end(), i)!=occ[j].end()){
				ban[i].ep((*lower_bound(occ[j].begin(), occ[j].end(), i))-i+1);
			}
		}
		sort(ban[i].begin(), ban[i].end());
	}
	get_sa();
	get_ht();
	build();
	sort(p+1, p+n+1, cmp);
	// for(int i=1; i<=n; ++i){
	// 	cout<<p[i]<<endl;
	// }
	ll ans=n-p[1]+1;
	for(int i=2; i<=n; ++i){
		// cout<<p[i-1]<<' '<<p[i]<<' '<<lcpp(p[i-1], p[i])<<endl;
		ans+=n-p[i]+1-lcpp(p[i-1], p[i]);
	}
	printf("%lld\n", ans);
	return 0;
}


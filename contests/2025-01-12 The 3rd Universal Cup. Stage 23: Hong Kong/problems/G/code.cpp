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
int T, n;
char s[N];
int tr[N][26], sz[N], idx;
vector<int> d[N];
ll cnt[N];
int main(){
	// freopen("D:\\nya\\acm\\B\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\B\\test.out","w",stdout);
	read(T);
	for(int i=1; i<N; ++i) for(int j=i; j<N; j+=i) d[j].ep(i);
	while(T--){
		read(n);
		for(int i=0; i<=n; ++i) cnt[i]=0;
		for(int i=1; i<=idx; ++i) {
			sz[i]=0;
			for(int j=0; j<26; ++j) tr[i][j]=0;
		}
		idx=1;
		ll ans=0;
		while(n--){
			scanf("%s", s+1);
			int p=1;
			for(int i=1; s[i]; ++i){
				int c=s[i]-'a';
				if(!tr[p][c]) tr[p][c]=++idx;
				p=tr[p][c];
				++sz[p];
				for(auto t:d[sz[p]]){
					ans^=cnt[t]*t; ++cnt[t]; ans^=cnt[t]*t;
				}
			}
			printf("%lld ", ans);
		}
		putchar('\n');
	}
	return 0;
}


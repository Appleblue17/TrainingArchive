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
int T, A, B, n;
struct node{
	int tp, id, h;
	bool operator <(const node &t)const{
		return h>t.h;
	}
}c[N];
int a[N], b[N];
bitset<N> f;
ll sum[N];
void solve(){
	read(A); read(B); read(n);
	ll suma=0;
	for(int i=1; i<=n; ++i) {
		read(a[i]), read(b[i]);
		c[i].tp=(b[i]>B-b[i]);
		c[i].id=i;
		if(c[i].tp) c[i].h=B-b[i];
		else c[i].h=b[i];
		suma+=a[i];
	}
	sort(c+1, c+n+1);
	sum[n+1]=0;
	for(int i=n; i>=1; --i){
		sum[i]=sum[i+1];
		if(c[i].tp) sum[i]+=a[c[i].id];
	}
	if(sum[1]>A){
		printf("NIE\n");
		return ;
	}
	f.reset();
	f[0]=1;
	int pre=0;
	for(int i=1; i<=n; ++i){
		int w=a[c[i].id];
		pre+=w;
		f|=f<<w;
		if(i==n||c[i].h!=c[i+1].h){
			int l=max(0ll, pre-(A-sum[i+1])), r=min(N-1ll, A-sum[i+1]);
			if(l>r){
				printf("NIE\n");
				return ;
			}
			f>>=l; f<<=l;
			f<<=(N-r-1); f>>=(N-r-1);
		}
		if(!f.any()){
			printf("NIE\n");
			return ;
		}
	}
	printf("TAK\n");
}
int main(){
	// freopen("D:\\nya\\acm\\A\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\A\\test.out","w",stdout);
	read(T);
	while(T--){
		solve();
	}
	return 0;
}


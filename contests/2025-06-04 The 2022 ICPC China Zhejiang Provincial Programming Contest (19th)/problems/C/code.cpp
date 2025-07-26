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
const int N=2e5+5;
int n, m, x;
int a[N], b[N];
int main(){
	// freopen("D:\\nya\\acm\\A\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\A\\test.out","w",stdout);
	read(n); read(m); read(x);
	int cnt=0;
	for(int i=1; i<=n; ++i){
		read(a[i]);
		cnt+=(a[i]>=x);
	}
	for(int i=1; i<=m; ++i){
		read(b[i]);
		cnt+=(b[i]<=x);
	}
	cout<<cnt<<endl;
	return 0;
}


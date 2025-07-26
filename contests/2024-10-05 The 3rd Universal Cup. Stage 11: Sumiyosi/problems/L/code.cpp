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
const int N=105;
int n, m;
int a[N];
int main(){
	// freopen("D:\\nya\\test.in","r",stdin);
	// freopen("D:\\nya\\test.out","w",stdout);
	read(n); read(m);
	for(int i=1; i<n; ++i) read(a[i]);
	for(int i=1; i<=n; ++i){
		for(int j=i+1; j<=n; ++j){
			--m;
			printf("%d %d\n", i, j);
			if(m==0) return 0;
		}
	}
	return 0;
}

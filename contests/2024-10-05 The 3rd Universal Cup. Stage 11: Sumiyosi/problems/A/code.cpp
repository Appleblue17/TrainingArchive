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
int n=48;
int id(int x, int y){
	return x*7+y;
}
struct mat{
	int a[50][50];
	mat(){memset(a, 0, sizeof a);}
}bs, pw[40];
inline mat mul(mat x, mat y){
	mat ret;
	memset(ret.a, 0, sizeof ret.a);
	for(int i=0; i<=n; ++i){
		for(int j=0; j<=n; ++j){
			for(int k=0; k<=n; ++k){
				ret.a[i][j]=((ll)x.a[i][k]*y.a[k][j]%mod+ret.a[i][j])%mod;
			}
		}
	}
	return ret;
}
inline mat mul2(mat x, mat y){
	mat ret;
	memset(ret.a, 0, sizeof ret.a);
	for(int j=0; j<=n; ++j){
		for(int k=0; k<=n; ++k){
			ret.a[0][j]=((ll)x.a[0][k]*y.a[k][j]%mod+ret.a[0][j])%mod;
		}
	}
	return ret;
}
int main(){
	// freopen("D:\\nya\\test.in","r",stdin);
	// freopen("D:\\nya\\test.out","w",stdout);
	for(int i=0; i<6; ++i){
		for(int j=0; j<6; ++j){
			pw[0].a[id(i, j)][id(i, j)]+=50;
			pw[0].a[id(i, j)][id(i+1, j)]+=1;
			pw[0].a[id(i, j)][id(i, j+1)]+=1;
		}
	}
	for(int i=0; i<6; ++i) {
		pw[0].a[id(i, 6)][id(i+1, 6)]+=1;
		pw[0].a[id(i, 6)][id(i, 6)]+=51;
		pw[0].a[id(6, i)][id(6, i+1)]+=1;
		pw[0].a[id(6, i)][id(6, i)]+=51;
	}
	pw[0].a[id(6, 6)][id(6, 6)]+=52;
	for(int i=1; i<=31; ++i) pw[i]=mul(pw[i-1], pw[i-1]);
	int TEST, m;
	read(TEST);
	while(TEST--){
		read(m);
		memset(bs.a, 0, sizeof bs.a);
		bs.a[0][0]=1;
		for(int i=0; i<=31; ++i) if((m>>i)&1) bs=mul2(bs, pw[i]);
		printf("%d\n", bs.a[0][id(6, 6)]);
	}
	return 0;
}

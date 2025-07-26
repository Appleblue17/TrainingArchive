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
int n, m, _;
struct mat{
	ull a[64], b;
}tr[N<<2], emp;
void work(ull x){
	for(int i=0; i<64; ++i) putchar('0'+((x>>i)&1));
	putchar('\n');
}
inline int md(int x){return (x>=64)?x-64:x;}
mat gen(){
	int k;
	read(k);
	mat ret=emp;
	int s, o; ull A;
	for(int i=1; i<=k; ++i){
		read(s); read(o); read(A);
		for(int j=0; j<64; ++j){
			if(o){
				ret.a[j]^=((ull)(A>>j)&1)<<(md(j+64-s));
			}
			else{
				ret.a[j]^=((ull)(1^((A>>j)&1)))<<(md(j-s+64));
				ret.b^=((ull)((A>>j)&1))<<j;
			}
		}
	}
	ull _b;
	read(_b);
	ret.b^=_b;
	// for(int i=0; i<64; ++i) printf("%d ", i), work(ret.a[i]);
	// work(ret.b);
	// cout<<"-------------------------------------------\n";
	return ret;
}
inline mat operator *(const mat &x, const mat &y){
	mat ret=emp;
	ret.b=y.b;
	for(int i=0; i<64; ++i){
		for(int j=0; j<64; ++j) if((y.a[i]>>j)&1){
			ret.a[i]^=x.a[j];
			ret.b^=(ull)((x.b>>j)&1)<<i;
		}
	}
	return ret;
}
inline ull operator &(ull x, const mat &y){
	ull ret=0;
	for(int i=0; i<64; ++i) {
		ret|=((ull)__builtin_parityll(x&y.a[i]))<<i;
	}
	return ret^y.b;
}
void build(int p, int l, int r){
	if(l==r){
		tr[p]=gen();
		return ;
	}
	int mid=(l+r)>>1;
	build(p<<1, l, mid); build(p<<1|1, mid+1, r);
	tr[p]=tr[p<<1]*tr[p<<1|1];
}
void mdf(int p, int l, int r, int x){
	if(l==r){
		tr[p]=gen();
		return ;
	}
	int mid=(l+r)>>1;
	if(x<=mid) mdf(p<<1, l, mid, x);
	else mdf(p<<1|1, mid+1, r, x);
	tr[p]=tr[p<<1]*tr[p<<1|1];
}
void get(int p, int l, int r, int L, int R, ull &x){
	if(L<=l&&r<=R){
		x=x&tr[p];
		return ;
	}
	int mid=(l+r)>>1;
	if(L<=mid) get(p<<1, l, mid, L, R, x);
	if(R>mid) get(p<<1|1, mid+1, r, L, R, x);
}
int main(){
	// freopen("D:\\nya\\acm\\A\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\A\\test.out","w",stdout);
	read(n); read(m); read(_);
	build(1, 1, n);
	while(m--){
		int op, l;
		read(op); read(l);
		if(op){
			mdf(1, 1, n, l);
		}
		else{
			int r; ull x; read(r); read(x);
			get(1, 1, n, l, r, x);
			printf("%llu\n", x);
		}
	}
	return 0;
}


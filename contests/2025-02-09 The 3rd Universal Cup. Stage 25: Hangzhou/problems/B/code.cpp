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
const ull FULL=(1ull<<63)-1;
int n, m;
ull a[N<<2], b[N<<2], sum[N<<2];
bool isleaf[N<<2];
inline void up(int p){
	b[p]=(a[p<<1]&b[p<<1|1])|(b[p<<1]&a[p<<1|1]);
	a[p]=a[p<<1]&a[p<<1|1];
	sum[p]=sum[p<<1]&sum[p<<1|1];
}
ull tag[N<<2];
void build(int p, int l, int r){
	tag[p]=FULL;
	if(l==r){
		isleaf[p]=true;
		read(a[p]); b[p]=FULL^a[p]; sum[p]=a[p];
		return;
	}
	int mid=(l+r)>>1;
	build(p<<1, l, mid); build(p<<1|1, mid+1, r);
	up(p);
}
void push_and(int p, ull v){
	tag[p]&=v;
	a[p]=(a[p]&(FULL^v))^a[p];
	if(isleaf[p]) b[p]=FULL^a[p];
	else b[p]=b[p]^(b[p]&(FULL^v));
	sum[p]&=v;
}
void down(int p){
	if(tag[p]^FULL){
		push_and(p<<1, tag[p]); push_and(p<<1|1, tag[p]);
		tag[p]=FULL;
	}
}
void mdf(int p, int l, int r, int x){
	if(l==r){
		read(a[p]); b[p]=FULL^a[p]; sum[p]=a[p];
		return ;
	}
	down(p);
	int mid=(l+r)>>1;
	if(x<=mid) mdf(p<<1, l, mid, x);
	else mdf(p<<1|1, mid+1, r, x);
	up(p);
}
void And(int p, int l, int r, int L, int R, ull v){
	if(L<=l&&r<=R){
		push_and(p, v);
		return ;
	}
	down(p);
	int mid=(l+r)>>1;
	if(L<=mid) And(p<<1, l, mid, L, R, v);
	if(R>mid) And(p<<1|1, mid+1, r, L, R, v);
	up(p);
}
pair<ull, ull> get(int p, int l, int r, int L, int R){
	if(L<=l&&r<=R) return mapa(a[p], b[p]);
	down(p);
	int mid=(l+r)>>1;
	if(L<=mid&&R>mid){
		pair<ull, ull> l_info=get(p<<1, l, mid, L, R);
		pair<ull, ull> r_info=get(p<<1|1, mid+1, r, L, R);
		return mapa(l_info.fi&r_info.fi, (l_info.fi&r_info.se)|(l_info.se&r_info.fi));
	}
	if(L<=mid) return get(p<<1, l, mid, L, R);
	else return get(p<<1|1, mid+1, r, L, R);
}
ull Sum(int p, int l, int r, int L, int R){
	if(L>R) return FULL;
	if(L<=l&&r<=R) return sum[p];
	down(p);
	int mid=(l+r)>>1;
	ull ret=FULL;
	if(L<=mid) ret&=Sum(p<<1, l, mid, L, R);
	if(R>mid) ret&=Sum(p<<1|1, mid+1, r, L, R);
	return ret;
}
int find(int p, int l, int r, int L, int R, ull v){
	if(L<=l&&r<=R){
		if(!(b[p]&v)) return 0;
		if(l==r) return l;
		down(p);
		int mid=(l+r)>>1;
		if(b[p<<1]&v) return find(p<<1, l, mid, L, R, v);
		else return find(p<<1|1, mid+1, r, L, R, v);
	}
	down(p);
	int mid=(l+r)>>1;
	int ret=0;
	if(L<=mid) ret=find(p<<1, l, mid, L, R, v);
	if(R>mid&&ret==0) ret=find(p<<1|1, mid+1, r, L, R, v);
	return ret;
}
int main(){
	// freopen("D:\\nya\\acm\\A\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\A\\test.out","w",stdout);
	read(n); read(m);
	build(1, 1, n);
	while(m--){
		int op;
		read(op);
		if(op==1){
			int l, r; ull v;
			read(l); read(r); read(v);
			And(1, 1, n, l, r, v);
		}
		else if(op==2){
			int x; 
			read(x); 
			mdf(1, 1, n, x);
		}
		else if(op==3){
			int l, r;
			read(l); read(r);
			pair<ull, ull> info=get(1, 1, n, l, r);
			ull ans=FULL;
			if(!info.se) ans=Sum(1, 1, n, l, r);
			else{
				// cout<<"info:"<<info.se<<endl;
				// cout<<"mask:"<<(1ull<<(63-__builtin_clzll(info.se)))<<endl;
				int x=find(1, 1, n, l, r, 1ull<<(63-__builtin_clzll(info.se)));
				// cout<<"x:"<<x<<endl;
				// cout<<Sum(1, 1, n, l, x-1)<<' '<<Sum(1, 1, n, x+1, r)<<endl;
				ans=Sum(1, 1, n, l, x-1)&Sum(1, 1, n, x+1, r);
			}
			printf("%llu\n", ans);
		}
	}
	return 0;
}


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
const int N=2e5+5;
int n;
char s[N], t[N];
int ans=0;
const int m1=998244353, m2=993244853;
struct hsh{
	int x, y;
	inline hsh operator +(const hsh &t){
		return (hsh){(x+t.x)%m1, (y+t.y)%m2};
	}
	inline hsh operator -(const hsh &t){
		return (hsh){(x-t.x+m1)%m1, (y-t.y+m2)%m2};
	}
	inline hsh operator *(const hsh &t){
		return (hsh){(int)((ll)x*t.x%m1), (int)((ll)y*t.y%m2)};
	}
	inline void operator +=(const hsh &t){
		x=(x+t.x)%m1, y=(y+t.y)%m2;
	}
	inline bool operator ==(const hsh &t){
		return x==t.x&&y==t.y;
	}
}hs[N], ht[N], pw[N]; 
const hsh bs=(hsh){137, 13331};
inline hsh gs(int l, int r){
	return hs[r]-hs[l-1]*pw[r-l+1];
}
inline hsh gt(int l, int r){
	return ht[r]-ht[l-1]*pw[r-l+1];
}
inline int lcs1(int x, int y){
	int l=1, r=x, mid, ret=0;
	while(l<=r){
		mid=(l+r)>>1;
		if(gt(x-mid+1, x)==gt(y-mid+1, y)) {ret=mid; l=mid+1;}
		else r=mid-1;
	}
	return ret;
}
inline int lcs2(int x, int y){
	int l=1, r=x, mid, ret=0;
	while(l<=r){
		mid=(l+r)>>1;
		if(gs(x-mid+1, x)==gt(y-mid+1, y)) {ret=mid; l=mid+1;}
		else r=mid-1;
	}
	return ret;
}
inline int lcs3(int x, int y){
	int l=1, r=x, mid, ret=0;
	while(l<=r){
		mid=(l+r)>>1;
		if(gs(x-mid+1, x)==gs(y-mid+1, y)) {ret=mid; l=mid+1;}
		else r=mid-1;
	}
	return ret;
}
inline int lcp1(int x, int y){
	int l=1, r=n-y+1, mid, ret=0;
	while(l<=r){
		mid=(l+r)>>1;
		if(gt(x, x+mid-1)==gt(y, y+mid-1)) {ret=mid; l=mid+1;}
		else r=mid-1;
	}
	return ret;
}
inline int lcp2(int x, int y){
	int l=1, r=n-y+1, mid, ret=0;
	while(l<=r){
		mid=(l+r)>>1;
		if(gs(x, x+mid-1)==gt(y, y+mid-1)) {ret=mid; l=mid+1;}
		else r=mid-1;
	}
	return ret;
}
inline void solve(){
	pw[0]=(hsh){1, 1};
	for(int i=1; i<=n; ++i) pw[i]=pw[i-1]*bs, hs[i]=hs[i-1]*bs+(hsh){s[i], s[i]}, ht[i]=ht[i-1]*bs+(hsh){t[i], t[i]};
	for(int i=1; i<n; ++i) if(s[i]==s[i+1]||s[i]==t[i+1]){
		ans=max(ans, 2); break;
	}
	for(int i=2; i<=n/2; ++i){
		bool flg=0;
		for(int j=1; j+i-1<=n; j+=i){
			if(lcp2(j, j+i)+lcs3(j-1, j+i-1)>=i){
				flg=1; break;
			}
			int p2=j-lcs1(j-1, j+i-1);
			int p3=j+i+lcp1(j, j+i);
			int p1=p2-lcs2(p2-1, p2-1+i);
			if(p3-p1>=2*i) {flg=1; break;}
		}
		if(flg) ans=max(ans, 2*i);
	}
}
int main(){
	// freopen("D:\\nya\\acm\\A\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\A\\test.out","w",stdout);
	read(n); 
	scanf("%s", s+1);
	scanf("%s", t+2);
	s[n+1]='?'; t[1]='!';
	++n;
	solve();
	reverse(s+1, s+n+1);
	reverse(t+1, t+n+1);
	swap(s, t);
	solve();
	printf("%d\n", ans);
	return 0;
}


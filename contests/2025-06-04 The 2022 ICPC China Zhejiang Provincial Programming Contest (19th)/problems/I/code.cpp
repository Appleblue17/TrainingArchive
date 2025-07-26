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
const int N=2e6+5;
int n, m;
char s[N];
int lt[N], rt[N], rd[N];
const int p1=998244353, p2=993244853;
struct hsh{
	int x, y;
	inline hsh operator +(const hsh &t){
		return (hsh){(x+t.x)%p1, (y+t.y)%p2};
	}
	inline hsh operator -(const hsh &t){
		return (hsh){(x-t.x+p1)%p1, (y-t.y+p2)%p2};
	}
	inline hsh operator *(const hsh &t){
		return (hsh){(int)((ll)x*t.x%p1), (int)((ll)y*t.y%p2)};
	}
	inline void operator +=(const hsh &t){
		x=(x+t.x)%p1, y=(y+t.y)%p2;
	}
	inline bool operator ==(const hsh &t){
		return x==t.x&&y==t.y;
	}
}hs1[N], hs2[N], bs, pw[N];
inline hsh get1(int l, int r){
	return hs1[r]-hs1[l-1]*pw[r-l+1];
}
inline hsh get2(int l, int r){
	return hs2[r]-hs2[l-1]*pw[r-l+1];
}
void manacher(){
	int mr=0, mid=0;
	for(int i=1; i<=n; ++i){
		if(i<=mr) rd[i]=min(rd[mid*2-i], mr-i+1);
		else rd[i]=1;
		while(s[i-rd[i]]==s[i+rd[i]]) ++rd[i];
		if(rd[i]+i>mr){
			mr=rd[i]+i-1;
			mid=i;
		}
	}
}
inline bool solve(int l, int r){
	int mid=(l+r)/2;
	int p=min(rd[mid], mid-l+1);
	if(lt[mid]==p&&rt[mid]>p){
		return false;
	}
	if(lt[mid]>p&&rt[mid]==p){
		return false;
	}
	return true;
}
inline bool check(int l, int r){
	return get1(l, r)==get2(n-r+1, n-l+1);
}
int main(){
	// freopen("D:\\nya\\acm\\A\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\A\\test.out","w",stdout);
	read(n); read(m);
	scanf("%s", s+1);
	bs=(hsh){137, 13331};
	pw[0]=(hsh){1, 1};
	for(int i=1; i<=n; ++i){
		pw[i]=pw[i-1]*bs;
		hs1[i]=hs1[i-1]*bs+(hsh){s[i], s[i]};
	}
	s[0]='!'; s[n+1]='?';
	manacher();
	reverse(s+1, s+n+1);
	for(int i=1; i<=n; ++i){
		hs2[i]=hs2[i-1]*bs+(hsh){s[i], s[i]};
	}
	for(int i=1; i<=n; ++i) {
		if(s[i]==s[i-1]) lt[i]=lt[i-1]+1;
		else lt[i]=1;
	}
	for(int i=n; i>=1; --i) {
		if(s[i]==s[i+1]) rt[i]=rt[i-1]+1;
		else rt[i]=1;
	}
	while(m--){
		int l, r; read(l); read(r);
		if(check(l, r)){
			printf("Budada\n");
			continue;
		}
		if((r-l+1)&1){
			printf("Putata\n");
		}
		else{
			printf("Budada\n");
		}
	}
	return 0;
}


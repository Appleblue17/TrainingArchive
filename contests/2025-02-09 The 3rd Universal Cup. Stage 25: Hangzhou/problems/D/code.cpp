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
const int N=5005;
int T, n, m;
int a[N], b[N];
vector<int> pos;
bool check(int l1, int r1, int l2, int r2){
	if(r1-l1!=r2-l2) return false;
	for(int i=0; i<=r1-l1; ++i) if(a[i+l1]!=a[i+l2]) return false;
	return true;
}
void Duval(){
	pos.clear();
	pos.ep(0);
	for(int i=1; i<=n; ){
		int k=i, j=i+1;
		while(j<=n){
			if(a[j]==a[k]) {
				++j; ++k;
			}
			else if(a[j]>a[k]){
				k=i; ++j;
			}
			else{
				break;
			}
		}
		while(i<=k){
			pos.ep(i+(j-k)-1);
			i+=j-k;
		}
	}
}
struct node{
	int l, r, cnt;
	node(int _l=0, int _r=0, int _cnt=0){l=_l; r=_r; cnt=_cnt;}
};
vector<int> ans;
void opt(){
	printf("%d\n", (int)ans.size());
	for(auto t:ans) printf("%d ", t);
	ans.clear();
	putchar('\n');
}
void paint(int l, int r){for(int i=l; i<=r; ++i) ans.ep(b[a[i]]);}
void solve(){
	read(n);
	for(int i=1; i<=n; ++i) read(a[i]), b[i]=a[i];
	sort(b+1, b+n+1);
	m=unique(b+1, b+n+1)-b-1;
	for(int i=1; i<=n; ++i) a[i]=lower_bound(b+1, b+m+1, a[i])-b;
	Duval();
	vector<node> str;
	for(int l=1, r; l<(int)pos.size(); ){
		r=l+1;
		while(r<(int)pos.size()&&check(pos[l-1]+1, pos[l], pos[r-1]+1, pos[r])) ++r;
		str.ep(pos[l-1]+1, pos[l], r-l);
		l=r;
	}
	for(auto t:str){
		if(t.cnt&1){
			for(int i=0; 2*i<=t.cnt; ++i) paint(t.l, t.r);
			opt();
			return ;
		}
		else{
			for(int i=1; 2*i<=t.cnt; ++i) paint(t.l, t.r);
		}
	}
	opt();
}
int main(){
	// freopen("D:\\nya\\acm\\B\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\B\\test.out","w",stdout);
	read(T);
	while(T--) solve();
	return 0;
}


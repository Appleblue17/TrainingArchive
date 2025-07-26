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
int T, n, m;
int p[N];
int A, l1, l2;
bool vis[N];
vector<int> vec;
int tr[N];
void upd(int x, int v){
	for(; x<=m; x+=(x&-x)) tr[x]=max(tr[x], v);
}
int get(int x){
	int ret=0;
	for(; x; x-=(x&-x)) ret=max(ret, tr[x]);
	return ret;
}
inline int solve1(){
	for(int i=1; i<=m; ++i) tr[i]=0;
	for(int i=1; i<=n; ++i) upd(p[i], get(p[i])+1);
	for(int i=0; i<m-n; ++i) upd(vec[i], get(vec[i])+1);
	return get(m);
}
inline int solve2(){
	for(int i=1; i<=m; ++i) tr[i]=0;
	for(int i=0; i<m-n; ++i) upd(vec[i], get(vec[i])+1);
	for(int i=1; i<=n; ++i) upd(p[i], get(p[i])+1);
	return get(m);
}
void upd2(int x, int v){
	for(; x; x-=(x&-x)) tr[x]=max(tr[x], v);
}
int get2(int x){
	int ret=0;
	for(; x<=m; x+=(x&-x)) ret=max(ret, tr[x]);
	return ret;
}
void work1(){
	for(int i=1; i<=m; ++i) tr[i]=0;
	for(int i=n; i>=1; --i) upd2(p[i], get2(p[i])+1);
	int pos=-1;
	for(int i=m-n-1; i>=0; --i) {
		if(get2(vec[i])+m-n-i==A+1) {
			pos=i; break;
		}
	}
	if(pos==-1) {
		printf("No\n");
		return ;
	}
	for(int i=pos, j=m-n-1; i<j; ++i, --j) swap(vec[i], vec[j]);
	if(solve1()==solve2()){
		printf("Yes\n");
		for(auto t:vec) printf("%d ", t);
		putchar('\n');
	}
	else{
		printf("No\n");
	}
}
void work2(){
	for(int i=1; i<=m; ++i) tr[i]=0;
	for(int i=1; i<=n; ++i) upd(p[i], get(p[i])+1);
	int pos=-1;
	for(int i=0; i<m-n; ++i) {
		if(get(vec[i])+i+1==A+1) {
			pos=i; break;
		}
	}
	if(pos==-1) {
		printf("No\n");
		return ;
	}
	for(int i=0, j=pos; i<j; ++i, --j) swap(vec[i], vec[j]);
	if(solve1()==solve2()){
		printf("Yes\n");
		for(auto t:vec) printf("%d ", t);
		putchar('\n');
	}
	else{
		printf("No\n");
	}
}
int main(){
	// freopen("D:\\nya\\acm\\A\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\A\\test.out","w",stdout);
	read(T);
	while(T--){
		read(n); read(m);
		for(int i=1; i<=m; ++i) vis[i]=0;
		for(int i=1; i<=m; ++i) tr[i]=0;
		for(int i=1; i<=n; ++i) read(p[i]), vis[p[i]]=1, upd(p[i], get(p[i])+1);
		A=get(m);
		vec.clear();
		for(int i=1; i<=m; ++i) if(!vis[i]) vec.ep(i);
		sort(vec.begin(), vec.end(), greater<int>());
		l1=solve1(), l2=solve2();
		if(l1==l2){
			printf("Yes\n");
			for(auto t:vec) printf("%d ", t);
			putchar('\n');
			continue;
		}
		if(l1==A+1) work1();
		else work2();
	}
	return 0;
}


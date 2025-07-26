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
int n;
int a[N];
int f[25];
char s[2]={'-', '+'};
struct node{
	int x, op, y; 
};
vector<node> vec;
void perform(int x, int op, int y){
	assert(abs(x-y)==1);
	vec.push_back((node){x, op, y});
	if(op==0){
		a[x]-=a[y];
	}
	else{
		a[x]+=a[y];
	}
}
int main(){
	// freopen("D:\\nya\\acm\\A\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\A\\test.out","w",stdout);
	read(n);
	for(int i=1; i<=n; ++i) read(a[i]);
	f[0]=1; f[1]=1;
	for(int i=2; i<=24; ++i) f[i]=f[i-1]+f[i-2];
	a[0]=n+1; a[n+1]=n+1;
	int pos=0;
	for(int i=1; i<=n; ++i){
		if(a[i]!=1) continue;
		int x=i-1;
		if(a[i+1]<a[i-1]) x=i+1;
		while(a[x]!=1) perform(x, 0, i);
		if(x<i) pos=x;
		else pos=i;
	}
	for(int i=pos+2; i<=n; ++i){
		int cur=0;
		while(f[cur+2]<a[i]) {
			if(cur==0){
				perform(i-1, 1, i-2);
			}
			else{
				perform(i-2, 1, i-1);
				perform(i-1, 1, i-2);
			}
			cur+=2;
		}
		while(a[i]!=1){
			if(f[cur]<a[i]){
				perform(i, 0, i-1);
			}
			else{
				perform(i-1, 0, i-2);
				cur-=2;
				if(cur!=0) perform(i-2, 0, i-1);
			}
		}
		while(a[i-1]!=1||a[i-2]!=1){
			if(a[i-2]>a[i-1]) perform(i-2, 0, i-1);
			else perform(i-1, 0, i-2);
		}
	}
	for(int i=pos-1; i>=1; --i){
		int cur=0;
		while(f[cur+2]<a[i]) {
			if(cur==0){
				perform(i+1, 1, i+2);
			}
			else{
				perform(i+2, 1, i+1);
				perform(i+1, 1, i+2);
			}
			cur+=2;
		}
		while(a[i]!=1){
			if(f[cur]<a[i]){
				perform(i, 0, i+1);
			}
			else{
				perform(i+1, 0, i+2);
				cur-=2;
				if(cur!=0) perform(i+2, 0, i+1);
			}
		}
		while(a[i+1]!=1||a[i+2]!=1){
			if(a[i+2]>a[i+1]) perform(i+2, 0, i+1);
			else perform(i+1, 0, i+2);
		}
	}
	for(int i=2; i<=n; ++i) perform(i, 1, i-1);
	// for(int i=1; i<=n; ++i) cout<<a[i]<<' '; cout<<endl;
	printf("%d\n", (int)vec.size());
	for(auto t:vec){
		printf("%d %c %d\n", t.x, s[t.op], t.y);
	}
	return 0;
}


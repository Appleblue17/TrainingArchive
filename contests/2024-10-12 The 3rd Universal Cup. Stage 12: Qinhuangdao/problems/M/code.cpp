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
const int N=105;
int Test, n, m1, m2;
ll dis(int x, int y){
	return (ll)x*x+(ll)y*y;
}
vector<int> vec;
int main(){
	// freopen("D:\\nya\\acm\\A\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\A\\test.out","w",stdout);
	read(Test);
	while(Test--){
		read(n); read(m1); read(m2);
		bool flg=0; int ans=0; ll mn=1e18;
		vec.clear();
		for(int i=1, x, y; i<=n; ++i){
			read(x); read(y);
			if(m1-m2*2>=0&&dis(x, y)<=(ll)(m1-m2*2)*(m1-m2*2)) {
				if(!flg) flg=1, ans=1, vec.clear(), vec.ep(i);
				else ++ans, vec.ep(i);
			}
			else if(m2*2-m1>=0&&(ll)(2*m2-m1)*(2*m2-m1)>=dis(x, y)){
				if(!flg) flg=1, ans=1, vec.clear(), vec.ep(i);
				else ++ans, vec.ep(i);
			}
			else{
				if(!flg){
					if(dis(x, y)<mn){
						mn=dis(x, y); ans=1; vec.clear(); vec.ep(i);
					}
					else if(dis(x, y)==mn){
						++ans; vec.ep(i);
					}
				}
				else continue;
			}
		}
		printf("%d\n", ans);
		for(int i=0; i<(int)vec.size()-1; ++i) printf("%d ", vec[i]);
		printf("%d", vec.back());
		putchar('\n');
	}
	return 0;
}

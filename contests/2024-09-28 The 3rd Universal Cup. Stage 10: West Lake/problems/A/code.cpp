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
const int N=2e5+5;
int Test, n;
int xc, yc, r;
int fx[N], fy[N]; 
inline ll cross(int i, int j){
	return (ll)fx[i]*fy[j]-(ll)fx[j]*fy[i];
}
typedef __int128 lint;
inline bool chk(int a, int b){
	ll dtx=fx[b]-fx[a], dty=fy[b]-fy[a];
	lint C=-dtx*fy[a]+dty*fx[a];
	lint A=-dty;
	lint B=dtx;
	return (A*xc+B*yc+C)*(A*xc+B*yc+C)>=(A*A+B*B)*r*r;
}
inline bool op(int a, int b){
	ll S=(ll)(fx[a]-xc)*(fy[b]-yc)-(ll)(fy[a]-yc)*(fx[b]-xc);
	return S>0;
}
int main(){
	// freopen("D:\\nya\\acm\\A\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\A\\test.out","w",stdout);
	read(Test);
	while(Test--){
		read(n); read(xc); read(yc); read(r);
		for(int i=1; i<=n; ++i){
			read(fx[i]); read(fy[i]); fx[i+n]=fx[i]; fy[i+n]=fy[i];
		}
		ll ans=0;
		ll cur=cross(1, 2);
		for(int i=1, j=2; i<=n; ++i){
			if(j==i) ++j, cur+=cross(i, i+1); 
			while(j+1!=i+n&&chk(i, j+1)&&op(i, j+1)) cur+=cross(j, j+1), ++j;
			cur+=cross(j, i);
//			cout<<i<<' '<<j<<' '<<cur<<endl;
			ans=max(ans, cur); 
			cur-=cross(j, i);
			cur-=cross(i, i+1);
		}
		printf("%lld\n", ans);
	}
	return 0;
}

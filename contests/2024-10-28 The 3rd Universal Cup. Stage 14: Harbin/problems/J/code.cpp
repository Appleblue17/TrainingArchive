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
template <typename T>inline void read(T &x){
	x=0;char c=getchar();bool f=0;
	for(;c<'0'||c>'9';c=getchar()) f|=(c=='-');
	for(;c>='0'&&c<='9';c=getchar())
	x=(x<<1)+(x<<3)+(c^48);
	x=(f?-x:x);
}
#define ep emplace_back
const int N=1e5+5;
int Test, n, m; 
int a[N], v[N], px[N], pt[N];
vector<int> vec[N]; 
int main(){
	// freopen("D:\\nya\\test.in","r",stdin);
	// freopen("D:\\nya\\test.out","w",stdout);
	read(Test);
	while(Test--){
		read(n); read(m);
		for(int i=1; i<=n; ++i) read(a[i]), v[i]=a[i], vec[i].clear();
		for(int i=1; i<=m; ++i) read(px[i]), read(pt[i]);
		for(int i=1; i<=n; ++i) vec[i].ep(m+1);
		for(int i=m; i>=1; --i) vec[pt[i]].ep(i);
		set<pii> s;
		for(int i=1; i<=n; ++i){
			s.insert(mapa(vec[i].back(), i));
		}
		ll ans=0;
		for(int i=1; i<=m; ++i){
			while((!s.empty())&&((ans+a[(*s.begin()).se])<px[i])){
				ans+=a[(*s.begin()).se];
				a[(*s.begin()).se]=0;
				s.erase(s.begin());
			}
			if(s.empty()) break;
			a[(*s.begin()).se]-=px[i]-ans;
			if(a[(*s.begin()).se]==0) s.erase(s.begin());
			ans=px[i];
			if(a[pt[i]]!=0){
				s.erase(s.find(mapa(i, pt[i])));
			}
			a[pt[i]]=v[pt[i]];
			vec[pt[i]].pop_back();
			s.insert(mapa(vec[pt[i]].back(), pt[i]));
//			for(int j=1; j<=n; ++j) cout<<a[j]<<' ';
//			cout<<endl;
		}
		for(int i=1; i<=n; ++i) ans+=a[i];
		printf("%lld\n", ans);
	}
	return 0;
}

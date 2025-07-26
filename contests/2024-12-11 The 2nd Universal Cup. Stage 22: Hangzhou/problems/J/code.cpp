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
const int N=1005;
int T, n;
bool vis[N];
bool f[N][N];
inline bool ask(int x, int y){
	cout<<"? "<<x<<' '<<y<<endl;
	int v; cin>>v;
	return v;
}
inline void work(){
	for(int i=1; i<=n; ++i) for(int j=1; j<=n; ++j) f[i][j]=0;
	for(int i=1; i<=n; ++i) vis[i]=0, f[i][i]=1;
	for(int i=1; i<=n/2; ++i){
		f[i][i+n/2]=f[i+n/2][i]=1;
		if(ask(i, i+n/2)) vis[i]=1, vis[i+n/2]=1;
	}
	if(n&1){
		f[1][n]=f[n][1]=1;
		if(ask(1, n)) vis[1]=1, vis[n]=1;
	}
	int cnt=0;
	for(int i=1; i<=n; ++i) cnt+=vis[i];
	if(cnt>=4){
		cout<<"! 1"<<endl;
		return ;
	}
	if(cnt==0){
		cout<<"! 1"<<endl;
		return ;
	}
	for(int i=1; i<=n/2; ++i) if(vis[i]){
		for(int j=1; j<=n; ++j) if(!f[i][j]){
			f[i][j]=1;
			if(ask(i, j)){
				for(int k=1; k<=n; ++k) if(!f[i][k]){
					if(ask(i, k)) {
						cout<<"! 2"<<endl;
					}
					else{
						cout<<"! 1"<<endl;
					}
					return ;
				}
			}
			break;
		}
	}
	for(int i=n; i>n/2; --i) if(vis[i]){
		for(int j=1; j<=n; ++j) if(!f[i][j]){
			f[i][j]=1;
			if(ask(i, j)){
				for(int k=1; k<=n; ++k) if(!f[i][k]){
					if(ask(i, k)) {
						cout<<"! 2"<<endl;
					}
					else{
						cout<<"! 1"<<endl;
					}
					return ;
				}
			}
			break;
		}
	}
	cout<<"! 1"<<endl;
}
int main(){
	// freopen("D:\\nya\\acm\\C\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\C\\test.out","w",stdout);
	cin>>T;
	while(T--){
		cin>>n;
		work();
	}
	// system("pause");
	return 0;
}


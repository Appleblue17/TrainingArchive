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
const int N=3005, M=3e7+5;
int n, m, T;
pii pos[M];
char s[N][N];
int dis[N][N];
int ban[N][N];
int dx[4]={-1, 1, 0, 0};
int dy[4]={0, 0, -1, 1};
inline void decode(int &x, int &y, int z){
	y=(z-1)%m+1;
	x=(z-y)/m+1;
}
int main(){
	// freopen("D:\\nya\\acm\\C\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\C\\test.out","w",stdout);
	read(n); read(m); read(T);
	for(int i=1; i<=T; ++i) read(pos[i].fi), read(pos[i].se), ban[pos[i].fi][pos[i].se]=T-i;
	for(int i=1; i<=n; ++i) ban[i][0]=ban[i][m+1]=1e9;
	for(int i=1; i<=m; ++i) ban[0][i]=ban[n+1][i]=1e9;
	for(int i=1; i<=n; ++i){
		scanf("%s", s[i]+1);
		for(int j=1; j<=m; ++j) if(s[i][j]=='#') ban[i][j]=1e9;
	}
	memset(dis, 0x3f, sizeof dis);
	dis[pos[1].fi][pos[1].se]=0;
	priority_queue<pii> q2;
	queue<pii> q;
	q.push(mapa((pos[1].fi-1)*m+pos[1].se, 0));
	while(!q.empty()||!q2.empty()){
		if(q.empty()||(!q2.empty()&&-q2.top().fi<q.front().se)){
			q.push(mapa(q2.top().se, -q2.top().fi));
			q2.pop();
		}
		int x, y, w=q.front().se;
		decode(x, y, q.front().fi);
		q.pop();
		for(int k=0; k<4; ++k){
			int xx=x+dx[k], yy=y+dy[k];
			if(w>=ban[xx][yy]&&dis[xx][yy]>w+1){
				dis[xx][yy]=w+1;
				q.push(mapa((xx-1)*m+yy, dis[xx][yy]));
			}
			else if(ban[xx][yy]!=1e9&&dis[xx][yy]>w+1){
				q2.push(mapa(-ban[xx][yy], (x-1)*m+y));
			}
		}
	}
	ull ans=0;
	for(int i=1; i<=n; ++i){
		for(int j=1; j<=m; ++j) if(dis[i][j]<1e9){
			// cout<<dis[i][j]<<' ';
			ans+=1ull*dis[i][j]*dis[i][j];
		}
		// cout<<endl;
	}
	printf("%llu", ans);
	return 0;
}


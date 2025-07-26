#include<bits/stdc++.h>
using namespace std;
const int N=105, M=3e6;
typedef pair<int, int> pii;
#define fi first
#define se second
#define mapa make_pair
int Test, n, m;
char s[N][N];
int f[N][N];
bool vis[N][N];
inline bool inr(int x, int y){
    return x>=1&&x<n&&y>=1&&y<m;
}
inline int sum(int i, int j){
	return (f[i][j]+f[i+1][j]+f[i][j+1]+f[i+1][j+1]);
}
inline bool check(int x, int y){
	if(s[x][y]==s[x+1][y+1]&&s[x+1][y]==s[x][y+1]&&s[x][y]!=s[x+1][y]) return true;
	else return false;
}
int dx[4]={0, 0, -1, -1};
int dy[4]={0, -1, 0, -1};
queue<pii> q, q2;
inline bool ins(int x, int y){
	for(int k=0; k<4; ++k){
		int xx=x+dx[k], yy=y+dy[k];
		if(inr(xx, yy)&&sum(xx, yy)<=1){
			if(sum(xx, yy)==0){
				if(check(xx, yy)) {
					return false;
				}
			}
			else if(!vis[xx][yy]){
				vis[xx][yy]=1;
				q.push(mapa(xx, yy));
			}
		}
	}
	return true;
}
inline void work(){
	scanf("%d%d", &n, &m);
	while(!q.empty()) q.pop();
	while(!q2.empty()) q2.pop();
	for(int i=1; i<=n; ++i) {
		scanf("%s", s[i]+1);
		for(int j=1; j<=m; ++j) {
			f[i][j]=(s[i][j]=='?'), vis[i][j]=0;
			if(s[i][j]=='?') q2.push(mapa(i, j));
		}
	}
	for(int i=1; i<n; ++i){
		for(int j=1; j<m; ++j){
			int cur=sum(i, j);
			if(cur==0){
				if(s[i][j]==s[i+1][j+1]&&s[i+1][j]==s[i][j+1]&&s[i][j]!=s[i+1][j]){
					printf("NO\n");
					return ;
				}
			}
			if(cur==1){
				q.push(mapa(i, j));
				vis[i][j]=1;
			}
		}
	}
	while(!q.empty()||!q2.empty()){
		while(q.empty()){
			while(!q2.empty()&&s[q2.front().fi][q2.front().se]!='?') q2.pop();
			if(q2.empty()) break;
			s[q2.front().fi][q2.front().se]='B'; f[q2.front().fi][q2.front().se]=0;
			ins(q2.front().fi, q2.front().se);
			q2.pop();
		}
		if(q.empty()) break;
		int x=q.front().fi, y=q.front().se; q.pop();
		int fx=x, fy=y;
		if(s[x+1][y]=='?') fx=x+1;
		else if(s[x][y+1]=='?') fy=y+1;
		else if(s[x+1][y+1]=='?') fx=x+1, fy=y+1;
		if(((fx+fy)&1)==((x+y)&1)){
			if(s[x+1][y]==s[x][y+1]&&s[x][y]!=s[x+1][y]&&s[x+1][y+1]!=s[x+1][y]){
				s[fx][fy]=s[x+1][y];
				f[fx][fy]=0;
				if(!ins(fx, fy)){
					cout<<"NO\n";
					return ;
				}
			}
		}
		else{
			if(s[x][y]==s[x+1][y+1]&&s[x][y]!=s[x+1][y]&&s[x][y]!=s[x][y+1]){
				s[fx][fy]=s[x][y];
				f[fx][fy]=0;
				if(!ins(fx, fy)){
					cout<<"NO\n";
					return ;
				}
			}
		}
	}
	cout<<"YES\n";
	for(int i=1; i<=n; ++i){
		for(int j=1; j<=m; ++j){
			putchar(s[i][j]);
		}
		putchar('\n');
	}
}
int main(){
	// freopen("D:\\nya\\acm\\C\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\C\\test.out","w",stdout);
    scanf("%d", &Test);
    while(Test--){
		work();
    }
}

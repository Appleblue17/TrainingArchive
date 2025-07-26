#pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;
const int N=1100;
int T,n,m;
char s[N][N];
bool vis[N][N];

int fx[4][2]={{0,1},{0,-1},{1,0},{-1,0}};
int A[N],B[N],id;
void dfs(int x,int y){
    if(vis[x][y]) return ;
    vis[x][y]=1;
    A[++id]=x,B[id]=y;
    for(int t=0;t<4;t++){
        int nx=x+fx[t][0],ny=y+fx[t][1];
        if(nx<1 || nx>n || ny<1 || ny>m || s[nx][ny]!='.') continue;
        dfs(nx,ny);
    }
}

int main(){
    scanf("%d",&T);
    while(T--){
        int ans=0;
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++){
            scanf("\n%s",s[i]+1);
            for(int j=1;j<=m;j++) vis[i][j]=0;
        }
        
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(vis[i][j] || s[i][j]=='O') continue;
                id=0;
                dfs(i,j);
                
                // cout<<i<<" "<<j<<": ";
                // for(int t=1;t<=id;t++) cout<<A[t]<<" "<<B[t]<<endl;
                
                bool flag=1;
                for(int x=1;x<=n && flag;x++){
                    for(int y=1;y<=m && flag;y++){
                        if(i==x && j==y) continue;
                        
                        bool fl=1;
                        for(int t=1;t<=id && fl;t++){
                            int nx=A[t]-i+x,ny=B[t]-j+y;
                            if(nx<1 || nx>n || ny<1 || ny>m || s[nx][ny]!='.'){
                                fl=0;
                            }
                        }
                        if(fl) flag=0;
                    }
                }
                
                if(flag) ans+=id;
            }
        }
        printf("%d\n",ans);
    }
    
}

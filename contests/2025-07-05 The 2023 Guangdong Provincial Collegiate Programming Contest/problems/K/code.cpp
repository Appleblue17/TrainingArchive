#include<bits/stdc++.h>
using namespace std;
const int N=11;
int T,n,m,k,ans;

bool f[N][N];
int fx[4][2]={{0,-1},{0,1},{-1,0},{1,0}};

void dfs(int dep){
    ans=max(ans,dep);
    
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(f[i][j]){
                for(int t=0;t<4;t++){
                    int nx=i+fx[t][0],ny=j+fx[t][1];
                    if(f[nx][ny]){
                        int mx=nx*2-i,my=ny*2-j;
                        if(!f[mx][my] && mx>=1 && mx<=n && my>=1 && my<=m){
                            f[i][j]=f[nx][ny]=0;
                            f[mx][my]=1;
                            dfs(dep+1);
                            f[i][j]=f[nx][ny]=1;
                            f[mx][my]=0;
                        }
                    }
                }
            }
            
        }
    }
    
}

int main(){
    cin>>T;
    while(T--){
        memset(f,0,sizeof(f));
        cin>>n>>m>>k;
        for(int i=1;i<=k;i++){
            int x,y; cin>>x>>y;
            f[x][y]=1;
        }
        
        ans=0;
        dfs(0);
        cout<<k-ans<<endl;
    }
    
}

#pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;
const int N=5500,INF=1e9;

int T,n;
char S[N];

int f[N][N][2],g[N][N][2];
int F[N],G[N];

void gmin(int &x,int y){
    if(y<x) x=y;
}

signed main(){
    scanf("%d",&T);
    int num=0;
    while(T--){
        scanf("\n%s",S+1);
        n=strlen(S+1);
        
        for(int i=0;i<=n+1;i++)
            for(int j=0;j<=n;j++)
                for(int t=0;t<=1;t++)
                    f[i][j][t]=g[i][j][t]=INF;
        
        f[0][0][0]=0;
        for(int i=1;i<=n;i++){
            for(int j=0;j<=n;j++){
                if(S[i]=='>' || S[i]=='?'){
                    gmin(f[i][j+1][1],min(f[i-1][j][0],f[i-1][j][1]));
                }
                if(S[i]=='<' || S[i]=='?'){
                    if(j) gmin(f[i][j-1][0],min(f[i-1][j][0],f[i-1][j][1]+1)); // delete
                    gmin(f[i][j][0],min(f[i-1][j][0],f[i-1][j][1])+1); // do not delete
                }
            }
            // cout<<i<<": ";
            // for(int j=0;j<=n;j++) cout<<f[i][j][0]<<"/"<<f[i][j][1]<<" ";
            
            F[i]=min(f[i][0][0],f[i][0][1]);
        }
        
        g[n+1][0][0]=0;
        for(int i=n;i>=0;i--){
            for(int j=0;j<=n;j++){
                if(S[i]=='<' || S[i]=='?'){
                    gmin(g[i][j+1][1],min(g[i+1][j][0],g[i+1][j][1]));
                }
                if(S[i]=='>' || S[i]=='?'){
                    if(j) gmin(g[i][j-1][0],min(g[i+1][j][0],g[i+1][j][1]+1)); // delete
                    gmin(g[i][j][0],min(g[i+1][j][0],g[i+1][j][1])+1); // do not delete
                }
            }
            G[i]=min(g[i][0][0],g[i][0][1]);
        }
        
        // for(int i=0;i<=n+1;i++) cout<<F[i]<<" ";
        // cout<<endl;
        // for(int i=0;i<=n+1;i++) cout<<G[i]<<" ";
        // cout<<endl;
        
        int ans=INF;
        for(int i=0;i<=n;i++) ans=min(ans,F[i]+G[i+1]);
        printf("%d\n",n-ans);
    }
    
}

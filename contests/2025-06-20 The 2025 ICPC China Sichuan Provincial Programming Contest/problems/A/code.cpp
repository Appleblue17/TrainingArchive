#include <bits/stdc++.h>
using namespace std;
const int N=330,M=6e4+5,W=200,INF=1e9;
int T,n,m;
struct nod{
    int v,a,b;
};
vector <nod> G[N];

int dis[N][M];

signed main(){
    cin>>T;
    while(T--){
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++) G[i].clear();
        for(int i=1;i<=n;i++){
            for(int j=0;j<=n*W;j++) dis[i][j]=INF;
        }
        
        dis[1][0]=0;
        for(int i=1;i<=m;i++){
            int u,v,a,b;
            scanf("%d%d%d%d",&u,&v,&a,&b);
            G[u].push_back({v,a,b});
        }
        long long ans=1e18;
        int A,B;
        for(int t=0;t<=n*W;t++){
            for(int u=1;u<=n;u++){
                if(dis[u][t]>=INF) continue;
                for(auto e: G[u]){
                    dis[e.v][t+e.a]=min(dis[e.v][t+e.a],dis[u][t]+e.b);
                }
            }
            if(dis[n][t]<INF){
                if(1ll*t*dis[n][t]<ans) ans=1ll*t*dis[n][t],A=t,B=dis[n][t];
            }
        }
        printf("%d %d\n",A,B);
        
    }
}

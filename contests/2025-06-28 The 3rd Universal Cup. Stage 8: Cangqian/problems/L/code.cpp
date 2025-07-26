#include<bits/stdc++.h>
using namespace std;
// #define int long long
const int N=1e6+5;
int n,m,ans[N];
vector <int> G[N];
vector <int> IF[N];

int in[N],out[N];
bool vis[N];

bool g[61][N];
int mx[N];

signed main(){
    // freopen("1.txt","w",stdout);
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v; scanf("%d%d",&u,&v);
        u=n+1-u,v=n+1-v;
        swap(u,v);
        G[u].push_back(v);
        in[v]++,out[u]++;
    }
    for(int i=1;i<=n;i++){
        if(in[i]>out[i]){
            int del=in[i]-out[i];
            for(int t=1;t<=del;t++){
                G[i].push_back(n+1);
                out[i]++,in[n+1]++;
            }
        }
        else{
            int del=out[i]-in[i];
            for(int t=1;t<=del;t++){
                G[0].push_back(i);
                out[0]++,in[i]++;
            }
        }
    }
    int k=out[0];
    assert(k<=60);
    for(int i=0;i<k;i++){
        int v=G[0][i];
        IF[v].push_back(i);
    }
    
    for(int u=1;u<=n;u++){
        for(int i=0;i<in[u];i++){
            int col=IF[u][i];
            g[col][u]=1;
            int v=G[u][i];
            IF[v].push_back(col);
        }
    }
    
    for(int i=1;i<=n;i++) vis[i]=1;
    for(int t=0;t<k;t++){
        int sum=0;
        for(int u=1;u<=n;u++){
            if(g[t][u]){
                sum+=vis[u];
                mx[u]=sum;
            }
            else mx[u]=0;
        }
        
        for(int u=1;u<=n;u++){
            for(int v: G[u]){
                mx[v]=max(mx[v],mx[u]);
            }
        }
        for(int u=1;u<=n;u++){
            ans[u]+=mx[u];
        }
        
        for(int u=1;u<=n;u++){
            if(g[t][u]){
                vis[u]=0;
            }
        }
    }
    
    for(int i=n;i>=1;i--){
        ans[i]=max(ans[i],1);
        printf("%d ",ans[i]);
    }
}

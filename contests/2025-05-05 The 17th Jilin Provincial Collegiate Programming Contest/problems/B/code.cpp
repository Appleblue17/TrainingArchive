// #pragma GCC optimize(2)
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=4e5+5;
int T,n;
int w[N];

vector <int> G[N];
int f[N][2],siz[N];

void dfs(int u,int fa){
    siz[u]=1;
    for(int v: G[u]){
        if(v==fa) continue;
        dfs(v,u);
        siz[u]+=siz[v];
    }
    
    int tot=0;
    vector <int> P,Q;
    for(int v: G[u]){
        if(v==fa) continue;
        if(siz[v]%2){
            P.push_back(v);
            tot+=f[v][0];
        }
        else Q.push_back(v);
    }
    
    f[u][0]=tot; f[u][1]=w[u]+tot;
    
    sort(P.begin(),P.end(),[&](int x,int y){
        return f[x][1]-f[x][0]>f[y][1]-f[y][0];
    });
    int len=P.size();
    if(len){
        for(int t=0;t<(len+1)/2;t++){
            int v=P[t];
            f[u][0]+=f[v][1]-f[v][0];
        }
        for(int t=0;t<len/2;t++){
            int v=P[t];
            f[u][1]+=f[v][1]-f[v][0];
        }
        for(int v: Q){
            f[u][0]+=max(f[v][0],f[v][1]);
            f[u][1]+=max(f[v][0],f[v][1]);
        }
    }
    else{
        for(int v: Q){
            f[u][0]+=f[v][1];
            f[u][1]+=f[v][0];
        }
    }
    // cout<<u<<": "<<f[u][0]<<" "<<f[u][1]<<endl;
}

signed main(){
    cin>>T;
    while(T--){
        scanf("%lld",&n);
        for(int i=1;i<=n;i++) G[i].clear();
        
        for(int i=1;i<=n;i++) scanf("%lld",&w[i]);
        for(int i=1;i<n;i++){
            int u,v; scanf("%lld%lld",&u,&v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        
        dfs(1,0);
        printf("%lld\n",f[1][0]);
        // cout<<endl;
    }
    
}

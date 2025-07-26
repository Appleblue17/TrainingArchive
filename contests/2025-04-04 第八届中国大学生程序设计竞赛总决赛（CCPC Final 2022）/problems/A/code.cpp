#include <bits/stdc++.h>
using namespace std;
const int N=1e6+5,mod=998244353;

int n,ans=1;
vector <int> G[N];

int in[N];
bool vis[N];
int num,sum;
void dfs(int u){
    if(vis[u]) return ;
    num++,sum+=in[u];
    vis[u]=1;
    for(int v: G[u]){
        if(!vis[v]) dfs(v);
    }
}

int main(){
    cin>>n;
    for(int i=1;i<=2*n-2;i++){
        int u,v; scanf("%d%d",&u,&v);
        if(u==v){
            puts("0");
            return 0;
        }
        if(u>v) swap(u,v);
        G[u+n].push_back(v);
        G[v].push_back(u+n);
        in[u+n]++,in[v]++;
    }
    
    for(int i=2;i<=2*n-1;i++){
        if(vis[i]) continue;
        num=sum=0;
        dfs(i);
        if(!G[i].size() || sum!=num*2){
            puts("0");
            return 0;
        }
        ans=ans*2%mod;
    }
    cout<<ans;
    
}

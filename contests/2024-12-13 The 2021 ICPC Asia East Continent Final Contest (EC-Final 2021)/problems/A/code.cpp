#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int T,n;
vector <int> G[N];
int dep[N],siz[N];
void dfs(int u){
    siz[u]=1;
    for(int v: G[u]){
        dep[v]=dep[u]+1;
        dfs(v);
        siz[u]+=siz[v];
    }
}
int main(){
    cin>>T;
    while(T--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++) G[i].clear();
        for(int i=1;i<n;i++){
            int u,v; scanf("%d%d",&u,&v);
            G[u].push_back(v);
        }
        dfs(1);
        for(int i=1;i<=n;i++){
            printf("%d %d\n",dep[i]+1,n-siz[i]+1);
        }
    }
    
}

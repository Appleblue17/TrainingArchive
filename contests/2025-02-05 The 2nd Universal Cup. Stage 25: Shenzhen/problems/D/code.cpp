#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int T,n,m;

vector <int> G[N];

int siz[N],dep[N],mx[N],layer[N];
void dfs(int u,int fa){
    dep[u]=dep[fa]+1;
    for(int v: G[u]){
        if(v==fa) continue;
        dfs(v,u);
        siz[u]+=siz[v];
        mx[u]=max(mx[u],mx[v]);
    }
}

bool solve(){
    for(int i=1;i<=n;i++) layer[i]=-1;
    for(int i=1;i<=n;i++){
        int d=dep[i];
        if(layer[d]==-1) layer[d]=siz[i];
        else if(layer[d]!=siz[i]){
            return 0;
        }
    }

    for(int u=1;u<=n;u++){
        int p=m/siz[u],r=-1;
        for(int v: G[u]){
            if(dep[v]<dep[u]) continue;
            if(r==-1) r=mx[v]%p;
            else if(r!=mx[v]%p) return 0;
        }
    }

    return 1;
}

int main(){
    cin>>T;
    while(T--){
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++) G[i].clear(),siz[i]=layer[i]=dep[i]=mx[i]=0;
        for(int i=1;i<n;i++){
            int u,v; scanf("%d%d",&u,&v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        for(int i=1;i<=m;i++) mx[i]=i,siz[i]=1;
        dfs(n,0);

        if(solve()) puts("Doddle");
        else puts("Tie");
    }

}

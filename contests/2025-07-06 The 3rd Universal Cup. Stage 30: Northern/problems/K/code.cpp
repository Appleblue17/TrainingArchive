#include<bits/stdc++.h>
using namespace std;
// #define int long long
#define ull unsigned long long
const int N=5e5+5,mod=1e9+7;

const ull mask = mt19937_64(123)();
ull shift(ull x) {
  x ^= mask;
  x ^= x << 13;
  x ^= x >> 7;
  x ^= x << 17;
  x ^= mask;
  return x;
}


int n;
vector <int> G[N],V;

int siz[N];
void dfs0(int u,int fa){
    siz[u]=1;
    int mx=0;
    for(int v: G[u]){
        if(v==fa) continue;
        dfs0(v,u);
        siz[u]+=siz[v];
        mx=max(mx,siz[v]);
    }
    if(max(mx,n-siz[u])<=n/2) V.push_back(u);
}


ull has[N];
int dfn[N],id;
void dfs(int u,int fa){
    has[u]=1;
    for(int v: G[u]){
        if(v==fa) continue;
        dfs(v,u);
        has[u]+=shift(has[v]);
    }
    sort(G[u].begin(),G[u].end(),[&](int x,int y){
        return has[x]<has[y];
    });
}

void dfss(int u,int fa){
    dfn[++id]=u;
    for(int v: G[u]){
        if(v==fa) continue;
        dfss(v,u);
    }
}


signed main(){
    cin>>n;
    for(int i=1;i<n;i++){
        int u,v; scanf("%d%d",&u,&v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dfs0(1,0);
    
    // cout<<V.size()<<endl;
    if(V.size()==1){
        dfs(V[0],0);
        dfss(V[0],0);
        for(int i=1;i<=n;i++) printf("%d ",dfn[i]);
    }
    else if(V.size()==2){
        int x=V[0],y=V[1];
        dfs(x,y);
        dfs(y,x);
        // cout<<has[x]<<" "<<has[y]<<" "<<x<<" "<<y<<endl;
        
        if(has[x]>has[y]) swap(x,y);
        dfss(x,y);
        dfss(y,x);
        
        for(int i=1;i<=n;i++) printf("%d ",dfn[i]);
    }
    
}

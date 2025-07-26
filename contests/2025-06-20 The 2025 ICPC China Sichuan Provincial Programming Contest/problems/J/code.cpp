#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=1000010;
vector<ll> g[MAXN];
ll cs[MAXN],pc[MAXN],f[MAXN];
char s[MAXN];
void dfs0(int u,int fa){
    for(int i=0;i<g[u].size();i++){
        int v = g[u][i];
        if(s[v] == 'S' && s[u] == 'C')cs[u]++;
        if(s[v] == 'C' && s[u] == 'P')pc[u]++;
        if(v == fa)continue;
        dfs0(v,u);
    }
}
void dfs(int u,int fa){
    ll sm1=0,sm2=0;
    for(int i=0;i<g[u].size();i++){
        int v = g[u][i];
        if(s[v]=='C')sm1 += cs[v];
        if(s[v]=='P')sm2 += pc[v]-1;
        if(v == fa)continue;
        dfs(v,u);
    }
    if(s[u] == 'C')f[u]=sm1*sm2;
}
void solve(){
    int n;
    scanf("%d",&n);
    for(int i=0;i<=n;i++){
        g[i].clear();cs[i]=pc[i]=0;f[i]=0;
    }
    scanf("%s",s+1);
    for(int i=1;i<n;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs0(1,0);
    dfs(1,0);
    ll fans=0;
    for(int i=1;i<=n;i++){
        fans += f[i];
        //printf("i=%d,cs=%lld,pc=%lld\n",i,cs[i],pc[i]);
    }
    printf("%lld\n",fans);
    return;
}
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        solve();
    }
}

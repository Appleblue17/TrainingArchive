#pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;
const int N=1e6+5;

int n,m;
vector <int> G[N];
map < pair<int,int>, bool> mp;

int p[N],cur;
vector < pair<int,int> > ANS;


bool vis[N];
int in[N];
void dfs(int u){
    
    for(int v: G[u]){
        in[v]--;
    }
    vis[u]=1;
    
    
    while(in[u]){
        // cout<<u<<" "<<in[u]<<endl;
        int x=p[++cur];
        if(mp[make_pair(u,x)]){
            dfs(x);
        }
        else{
            ANS.push_back(make_pair(u,x));
            dfs(x);
        }
    }
    
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v; scanf("%d%d",&u,&v);
        G[u].push_back(v);
        G[v].push_back(u);
        mp[make_pair(u,v)]=1;
        mp[make_pair(v,u)]=1;
        in[u]++,in[v]++;
    }
    for(int i=1;i<=n;i++) scanf("%d",&p[i]);
    
    while(cur<n){
        cur++;
        dfs(p[cur]);
    }
    
    cout<<ANS.size()<<endl;
    for(auto tmp: ANS) printf("%d %d\n",tmp.first,tmp.second);
}

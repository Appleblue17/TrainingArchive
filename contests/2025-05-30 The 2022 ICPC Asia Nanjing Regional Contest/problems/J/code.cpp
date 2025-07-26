#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
typedef long long ll;
int T;
vector<int> nodes[N];
vector<int> g[N];
vector<int> va[N];
map<int,vector<int> > ma[2];
int bel[N][2];
int a[N],del[N],vis[N];
vector<int> ans;

void addedge(int u,int v,int i){
    g[u].push_back(v);
    g[v].push_back(u);
    va[u].push_back(i);
    va[v].push_back(i);
}

bool failed=0;

void dfs(int u,int sav){
    vector<int> curnodes;
    for(int i=0;i<g[u].size();i++){
        int v = g[u][i];
        if(vis[v])continue;//new nodes indexes, scale to ncnt
        vis[v]=1;
        dfs(v,va[u][i]);
    }
    for(int i=0;i<nodes[u].size();i++){
        int v = nodes[u][i];
        if(del[v])continue;//original indexes, scale to n
        curnodes.push_back(v);
    }
    if(curnodes.size()&1){
        if(sav == -1)failed = 1;
        for(int v:curnodes){
            if(v == sav)continue;
            ans.push_back(v);
            del[v]=1;
        }
    }
    else{
        for(int v:curnodes){
            ans.push_back(v);
            del[v]=1;
        }
    }
}

void solve(){
    int n,ncnt=0;
    scanf("%d", &n);
    ma[0].clear();ma[1].clear();ans.clear();
    for(int i=0;i<=n*4;i++){
        del[i]=vis[i]=0;
        bel[i][0]=bel[i][1]=0;
        g[i].clear();
        nodes[i].clear();
        va[i].clear();
    }
    for(int i=1; i<=n; ++i) {
        scanf("%d", &a[i]);
        ma[0][a[i]+i].push_back(i);
        ma[1][a[i]-i].push_back(i);
    }
    //cout << '*'<< endl;
    
    //create nodes
    
    map<int,vector<int> >::iterator it;
    for(it=ma[0].begin();it!=ma[0].end();it++){
        ncnt++;
        for(int v:it->second){
        //    printf("%d ",v);
            nodes[ncnt].push_back(v);
            bel[v][0]=ncnt;
        }
        //cout << "ncnt = " << ncnt << endl;
    }
    //cout << '*' << endl;
    for(it=ma[1].begin();it!=ma[1].end();it++){
        ncnt++;
        for(int v:it->second){
            //printf("%d ",v);
            nodes[ncnt].push_back(v);
            bel[v][1]=ncnt;
        }
        //cout << "ncnt = " << ncnt << endl;
    }
    
    //add edges
    
    for(int i=1;i<=n;i++){
        addedge(bel[i][0],bel[i][1],i);
        //printf("add edge %d %d %d\n",bel[i][0],bel[i][1],i);
    }
    
    fflush(stdout);
    
    
    
    for(int i=1;i<=ncnt;i++){
        if(!vis[i]){
            failed=0;
            dfs(i,-1);
            if(failed){
                printf("No\n");
                return;
            }
        }
    }
    printf("Yes\n");
    int tcnt=0;
    for(int i:ans){
        tcnt++;
        printf("%d ",i);
        if(!(tcnt&1))printf("\n");
    }
}
int main(){
    scanf("%d", &T);
    while(T--){
        solve();
    }
}

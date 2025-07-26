#include <bits/stdc++.h>
using namespace std;
const int N=2550;
int T;
map < pair<int,int>, bool > ANS;

int U,D;
void query(int x){
    cout<<"> "<<x<<endl;
    cin>>U>>D;
}

int n;
int fa[N],fae[N],rec[N];
bool vis[N];
int cur[N];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    cin>>T;
    while(T--){
        n=0;
        ANS.clear();
        
        int u,d; cin>>u>>d;
        
        while(1){
            if(!vis[u]){
                vis[u]=1;
                n++;
            }
            // cout<<" at "<<u<<" "<<d<<"  "<<cur[u]+1<<"  "<<fa[u]<<endl;
            
            if(cur[u]==d){
                // cout<<" complete "<<u<<endl;
                if(u==1) break ;
                query(rec[u]);
                u=U,d=D;
                continue;
            }
            
            query(++cur[u]);
            int v=U,vd=D;
            ANS[make_pair(min(u,v),max(u,v))]=1;
            if(v==fa[u]){
                query(fae[u]);
                rec[u]=cur[u];
                continue;
            }
            if(!vis[v]){
                fa[v]=u;
                fae[v]=cur[u];
                
            }
            u=v,d=vd;
        }
        
        
        cout<<"! ";
        for(auto tmp: ANS) cout<<tmp.first.first<<" "<<tmp.first.second<<" ";
        cout<<endl;
        
        string Correct;
        cin>>Correct;
        for(int i=1;i<=n;i++) fa[i]=fae[i]=vis[i]=rec[i]=cur[i]=0;
    }
    
}

#include<bits/stdc++.h>
using namespace std;
const int N=5e5+10,M=1e6+5;
int T,n,m;
bool fl;

struct abc{
    int to,nxt;
}e[M*2];
int head[N],cnt;
void add(int u,int v){
    e[++cnt]={v,head[u]};
    head[u]=cnt;
}

int dfn[N],low[N],id;
bool vis[N];
stack <int> st;
stack < pair<int,int> > ste;

bool check();
vector <int> ANS;
vector < pair<int,int> > ANSE;
void tarjan(int u,int fa){
    low[u]=dfn[u]=++id;
    vis[u]=1;
    st.push(u);
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;
        if(v==fa) continue;
        if(!dfn[v]){
            ste.push(make_pair(u,v));
            tarjan(v,u);
            low[u]=min(low[u],low[v]);
            if(low[v]>=dfn[u]){
                ANS.clear();
                ANSE.clear();
                while(st.size()){
                    int x=st.top();
                    vis[x]=0;
                    ANS.push_back(x);
                    st.pop();
                    if(x==v) break;
                }
                while(ste.size()){
                    pair<int,int> tmp=ste.top();
                    ANSE.push_back(tmp);
                    ste.pop();
                    if(tmp.first==u && tmp.second==v) break;
                }
                ANS.push_back(u);
                
                // cout<<u<<" "<<v<<": ";
                // for(int x: ANS) cout<<x<<" "; cout<<endl;
                // cout<<"     ";
                // for(pair<int,int> tmp: ANSE) cout<<tmp.first<<","<<tmp.second<<" "; cout<<endl;
                if(fl) fl &= check();
            }
        }
        else{
            if(vis[v]){
                if(dfn[v]<=dfn[u]) ste.push(make_pair(u,v));
                // cout<<"  add "<<u<<" "<<v<<endl;
                low[u]=min(low[u],dfn[v]);
            }
        }
    }
}

int deg[N];

int C=-1;
int D=-1;

vector <int> G[N];

bool upd(int &x,int w){
    if(x==-1){
        x=w;
        return 1;
    }
    else return (x==w);
}
bool dfs(int u,int fa,int goal,int d){
    if(u==goal){
        return upd(D,d);
    }
    for(int v: G[u]){
        if(v==fa) continue;
        if(!dfs(v,u,goal,d+1)) return 0;
    }
    return 1;
}

bool check(){
    if(ANS.size()<=2) return 1;
    // cout<<t<<": ";
    // for(int u: ANS) cout<<u<<" ";
    // cout<<endl;
    
    for(int u: ANS){
        deg[u]=0;
        G[u].clear();
    }
    for(pair<int,int> tmp: ANSE){
        int u=tmp.first,v=tmp.second;
        deg[u]++,deg[v]++;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    
    // cout<<"  ";
    // for(int u: ANS) cout<<deg[u]<<" ";
    // cout<<endl;
    
    vector <int> SP;
    for(int u: ANS){
        if(deg[u]!=2) SP.push_back(u);
    }
    
    if(SP.size()==0){
        if(!upd(C,ANS.size())) return 0;
    }
    else if(SP.size()==2){
        int x=SP[0],y=SP[1];
        if(deg[x]!=deg[y]) return 0;
        D=-1;
        if(!dfs(x,0,y,0)) return 0;
        else if(!upd(C,D*2)) return 0;
    }
    else return 0;
    
    return 1;
}

int main(){
    scanf("%d", &T);
    while(T--){
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++){
            dfn[i]=low[i]=head[i]=vis[i]=0;
            deg[i]=0;
        }
        cnt=id=0;
        C=-1;
        while(st.size()) st.pop();
        while(ste.size()) ste.pop();
        
        for(int i=1;i<=m;i++){
            int u,v;
            scanf("%d%d",&u,&v);
            add(u,v);
            add(v,u);
        }
        
        fl=1;
        tarjan(1,0);

        if(fl) puts("Yes");
        else puts("No");
    }
}

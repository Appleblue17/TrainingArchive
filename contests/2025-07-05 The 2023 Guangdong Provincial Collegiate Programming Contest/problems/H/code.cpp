#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int T,n,m;

bool inans[N];
bool vs[N],tag[N];

struct abc{
    int to,nxt,num;
}e[N*2];
int head[N],cnt;
void add(int u,int v,int num){
    e[++cnt]={v,head[u],num};
    head[u]=cnt;
}

vector <int> G[N];

vector <int> P,Q,R;

int dfn[N],low[N],id;
int col[N],cid,repr[N];
bool indeg[N];
bool vis[N];
stack <int> st;
void tarjan(int u){
    low[u]=dfn[u]=++id;
    vis[u]=1;
    st.push(u);
    
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;
        if(!dfn[v]){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else if(vis[v]) low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u]==low[u]){
        cid++;
        repr[cid]=-u;
        while(st.size()){
            int x=st.top();
            vis[x]=0;
            col[x]=cid;
            // cout<<cid<<": "<<x<<endl;
            if(tag[x]) repr[cid]=x;
            st.pop();
            if(x==u) break;
        }
    }
}

void dfs(int u){
    if(vis[u]) return ;
    vis[u]=1;
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;
        if(vis[v]) continue;
        Q.push_back(e[i].num);
        inans[e[i].num]=1;
        dfs(v);
    }
}

signed main(){
    cin>>T;
    while(T--){
        scanf("%d%d",&n,&m);
        P.clear(),Q.clear(),R.clear();
        for(int i=1;i<=max(n,m);i++){
            vs[i]=tag[i]=vis[i]=0;
            head[i]=0;
            G[i].clear();
            
            dfn[i]=low[i]=col[i]=0;
            repr[i]=indeg[i]=0;
            inans[i]=0;
        }
        cnt=id=cid=0;
        
        for(int i=1;i<=m;i++){
            int l,x,r,y; scanf("%d%d%d%d",&l,&x,&r,&y);
            vs[l]=vs[r]=1;
            
            if(x==1 && y==1){
                P.push_back(i);
                inans[i]=1;
            }
            else if(x==2 && y==2){
                R.push_back(i);
                inans[i]=1;
                tag[l]=tag[r]=1;
            }
            else{
                if(x==1 && y==2) add(l,r,i);
                else add(r,l,i);
            }
        }
        
        int ans=0;
        for(int i=1;i<=n;i++) ans+=vs[i]*2;
        
        for(int u=1;u<=n;u++){
            if(!vs[u] || dfn[u]) continue;
            tarjan(u);
        }
        for(int u=1;u<=n;u++){
            if(!vs[u]) continue;
            for(int i=head[u];i;i=e[i].nxt){
                int v=e[i].to;
                if(col[u]!=col[v]) indeg[col[v]]=1;
            }
        }
        
        for(int i=1;i<=n;i++) vis[i]=0;
        for(int i=1;i<=cid;i++){
            if(indeg[i]) continue;
            int u=repr[i];
            if(u<0){
                u=-u;
                ans--;
            }
            dfs(u);
        }
        
        printf("%d\n",ans);
        for(int x: P) printf("%d ",x);
        for(int i=1;i<=m;i++){
            if(!inans[i]) printf("%d ",i);
        }
        reverse(Q.begin(),Q.end());
        for(int x: Q) printf("%d ",x);
        for(int x: R) printf("%d ",x);
        printf("\n");
    }
    
}

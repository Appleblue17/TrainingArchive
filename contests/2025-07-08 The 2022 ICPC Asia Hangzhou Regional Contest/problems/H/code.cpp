#include <bits/stdc++.h>
using namespace std;
#define int long long
#define MP make_pair
const int N=5e5+5,INF=1e18;
int n,qry,y[N];
int col[N],buc[8],ans;
int num[N];
bool tag[N],del[N];


char S[6];
int G[8][4]={
    {0,0,0,0},
    
    {1,0,1,0},
    {0,1,1,0},
    {1,1,1,0},
    
    {0,0,0,1},
    {1,0,1,1},
    {0,1,1,1},
    {1,1,1,1},
};

int IG[8][4];

bool vis[2][8];

int R[4];
bool ACT;
bool dfs0(bool fl,int u){
    if(vis[fl][u]) return 0;
    
    if(fl && R[u]){
        if(ACT) R[u]--;
        return 1;
    }
    
    vis[fl][u]=1;
    
    if(!fl){
        for(int i=0;i<4;i++){
            if(G[u][i]){
                if(dfs0(1,i)){
                    if(ACT) IG[u][i]++;
                    return 1;
                }
            }
        }
    }
    else{
        for(int i=1;i<=7;i++){
            if(IG[i][u]){
                if(dfs0(0,i)){
                    if(ACT) IG[i][u]--;
                    return 1;
                }
            }
        }
    }
    return 0;
}

int GOAL;
bool dfs1(bool fl,int u){
    if(vis[fl][u]) return 0;
    
    if(!fl && u==GOAL){
        return 1;
    }
    
    vis[fl][u]=1;
    
    if(!fl){
        for(int i=0;i<4;i++){
            if(G[u][i]){
                if(dfs1(1,i)){
                    IG[u][i]++;
                    return 1;
                }
            }
        }
    }
    else{
        for(int i=1;i<=7;i++){
            if(IG[i][u]){
                if(dfs1(0,i)){
                    IG[i][u]--;
                    return 1;
                }
            }
        }
    }
    return 0;
}


bool dfs2(bool fl,int u){
    if(vis[fl][u]) return 0;
    
    if(!fl && u==GOAL){
        return 1;
    }
    
    vis[fl][u]=1;
    
    if(!fl){
        for(int i=0;i<4;i++){
            if(G[u][i]){
                if(dfs2(1,i)){
                    if(ACT) IG[u][i]++;
                    return 1;
                }
            }
        }
    }
    else{
        for(int i=1;i<=7;i++){
            if(IG[i][u]){
                if(dfs2(0,i)){
                    if(ACT) IG[i][u]--;
                    return 1;
                }
            }
        }
    }
    return 0;
}

bool check(int k){
    for(int i=0;i<4;i++) R[i]=k;
    int tot=0;
    
    memset(IG,0,sizeof(IG));
    for(int t=1;t<=7;t++){
        for(int i=1;i<=buc[t];i++){
            memset(vis,0,sizeof(vis));
            ACT=1;
            int ret=dfs0(0,t);
            tot+=ret;
        }
    }
    return (tot==k*4);
}

priority_queue < pair<int,int> > P[8],Q[8];

void update(){
    int mn=INF,mner=-1;
    for(int t=1;t<=7;t++){
        while(P[t].size()){
            int x=P[t].top().second;
            if(del[x] || tag[x]) P[t].pop();
            else break;
        }
        
        if(!P[t].size()) continue;
        pair<int,int> tmp=P[t].top();
        if(-tmp.first>=mn) continue;
        
        memset(vis,0,sizeof(vis));
        ACT=0;
        int ret=dfs0(0,t);
        
        if(ret){
            mn=-tmp.first,mner=t;
        }
    }
    
    pair<int,int> u=P[mner].top(); P[mner].pop();
    
    memset(vis,0,sizeof(vis));
    ACT=1;
    dfs0(0,mner);
    ans+=mn; tag[u.second]=1;
    Q[mner].push(MP(-u.first,u.second));
}

signed main(){
    scanf("%lld",&n);
    for(int i=1;i<=n;i++){
        scanf("\n%s %lld",S,&y[i]);
        int len=strlen(S);
        int mac=0;
        for(int t=0;t<len;t++){
            char c=S[t];
            if(c=='D') mac |= 1;
            else if(c=='S') mac |= 2;
            else if(c=='B') mac |= 4;
        }
        col[i]=mac;
        buc[mac]++;
        P[mac].push(MP(-y[i],i));
        num[i]=i;
    }
    
    int l=0,r=n/4,mx=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid)) mx=mid,l=mid+1;
        else r=mid-1;
    }
    
    for(int i=0;i<4;i++) R[i]=mx;
    int tot=0;
    
    memset(IG,0,sizeof(IG));
    for(int i=1;i<=mx*4;i++){
        update();
    }
    
    scanf("%lld",&qry);
    for(int T_=1;T_<=qry;T_++){
        int x,w; scanf("%lld%lld",&x,&w);
        int u=num[x];
        
        if(tag[u]){
            memset(vis,0,sizeof(vis));
            GOAL=col[u];
            
            int sp=-1;
            for(int i=0;i<4;i++){
                if(dfs1(1,i)){
                    sp=i;
                    break;
                }
            }
            del[u]=1; tag[u]=0;
            ans-=y[x]; R[sp]++;
            n++; num[x]=n; col[n]=col[u];
            
            P[col[u]].push(MP(-w,n));
            
            update();
        }
        else{
            int mx=-INF,mxer;
            
            del[u]=1;
            n++; num[x]=n; col[n]=col[u];
            
            for(int t=1;t<=7;t++){
                
                while(Q[t].size()){
                    int x=Q[t].top().second;
                    if(del[x] || !tag[x]) Q[t].pop();
                    else break;
                }
                if(!Q[t].size()) continue;
                
                pair<int,int> tmp=Q[t].top();
                if(tmp.first<=mx) continue;
                
                memset(vis,0,sizeof(vis));
                GOAL=t;
                ACT=0;
                
                int ret=dfs2(0,col[u]);
                if(ret){
                    mx=tmp.first,mxer=t;
                }
            }
            if(-mx+w<0){
                pair<int,int> v=Q[mxer].top(); Q[mxer].pop();
                
                memset(vis,0,sizeof(vis));
                ACT=1;
                GOAL=mxer;
                int ret=dfs2(0,col[u]);
                
                ans+=-mx+w;
                tag[n]=1; Q[col[u]].push(MP(w,n));
                tag[v.second]=0; P[mxer].push(MP(-v.first,v.second));
            }
            else{
                P[col[u]].push(MP(-w,n));
            }
        }
        
        y[x]=w;
        printf("%lld\n",ans);
    }
}

#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5,INF=1e9;
int T,n,m,A,B,ans;
vector <int> G[N];
int L[N],V[N];


int dis[N];
queue <int> q;

int solve(int st,int ed){
    for(int i=1;i<=n;i++) dis[i]=INF;
    while(q.size()) q.pop();
    
    dis[st]=0;
    q.push(st);
    while(q.size()){
        int u=q.front(); q.pop();
        if(dis[u]>V[u]) continue;
        
        for(int v: G[u]){
            if(dis[v]==INF){
                dis[v]=dis[u]+1;
                q.push(v);
            }
        }
    }
    if(dis[ed]>V[ed]) return INF;
    else return dis[ed];
}

bool check(int k){
    for(int i=1;i<=n;i++) V[i]=k-V[i];
    int res=solve(n,1);
    for(int i=1;i<=n;i++) V[i]=k-V[i];
    return (res<INF);
}


struct abc{
    int x;
};
bool operator <(abc X,abc Y){
    return V[X.x]>V[Y.x];
}
priority_queue <abc> Q;
bool vis[N];
bool chk(){
    for(int i=1;i<=n;i++) vis[i]=0;
    while(Q.size()) Q.pop();
    
    int cur=0;
    Q.push({1});
    vis[1]=1;
    while(Q.size()){
        int u=Q.top().x; Q.pop();
        if(V[u]>cur) return 0;
        if(u==n) return 1;
        for(int v: G[u]){
            if(!vis[v]) Q.push({v}),vis[v]=1;
        }
        cur++;
    }
    return 0;
}

int main(){
    cin>>T;
    while(T--){
        scanf("%d%d%d%d",&n,&m,&A,&B);
        for(int i=1;i<=n;i++) G[i].clear();
        
        for(int i=1;i<=m;i++){
            int u,v; scanf("%d%d",&u,&v);
            if(u==v) continue;
            G[u].push_back(v);
            G[v].push_back(u);
        }
        for(int i=1;i<=n;i++) scanf("%d",&L[i]);
        L[1]-=A;
        
        if(n==1){
            puts("0");
            continue;
        }
        
        if(A<=B){
            V[1]=INF;
            // >V[u] lock
            for(int i=2;i<=n;i++){
                if(L[i]>=L[1]) V[i]=0;
                else if(A==B) V[i]=INF;
                else V[i]=(L[1]-L[i]-1)/(B-A);
            }
            
            // cout<<"lock: ";
            // for(int i=1;i<=n;i++) cout<<V[i]<<" ";
            // cout<<endl;
            
            ans=solve(1,n);
            if(ans==INF) puts("-1");
            else printf("%d\n",ans);
        }
        else{
            int mx=0;
            V[1]=0;
            // >=V[u] unlock
            for(int i=2;i<=n;i++){
                if(L[i]<L[1]) V[i]=0;
                else V[i]=(L[i]-L[1])/(A-B)+1;
                mx=max(mx,V[i]);
            }
            
            // cout<<"unlock: ";
            // for(int i=1;i<=n;i++) cout<<V[i]<<" ";
            // cout<<endl;
            
            if(!chk()){
                puts("-1");
                continue;
            }
            
            int l=V[n],r=mx+n,tot=r+1;
            while(l<=r){
                int mid=(l+r)>>1;
                if(check(mid)) r=mid-1,tot=mid;
                else l=mid+1;
            }
            
            printf("%d\n",tot);
        }
    }
}

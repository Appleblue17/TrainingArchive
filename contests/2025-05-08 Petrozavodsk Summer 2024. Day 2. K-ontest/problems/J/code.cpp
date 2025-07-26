#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+5,INF=1e18;

int n,m;
struct abc{
    int x,y,c,num;
}p[N];

struct edg{
    int to,nxt,w;
}e[N*10];
int head[N],cnt;
void add(int u,int v,int w){
    // cout<<u<<" "<<v<<" "<<w<<endl;
    e[++cnt]={v,head[u],w};
    head[u]=cnt;
}

int id;


int dis[N],vis[N];
struct def{
    int num,dis;
};
bool operator <(def x,def y){
    return x.dis>y.dis;
}
priority_queue <def> q;
void dijkstra(){
    for(int i=1;i<=id;i++) dis[i]=INF;
    dis[1]=0;
    q.push((def){1,0});
    
    while(!q.empty()){
        def tmp=q.top();
        q.pop();
        int u=tmp.num;
        if(vis[u]) continue;
        vis[u]=1;
        for(int i=head[u];i;i=e[i].nxt){
            int v=e[i].to;
            if(!vis[v] && dis[u]+e[i].w<dis[v]){
                dis[v]=dis[u]+e[i].w;
                q.push((def){v,dis[v]});
            }
        }
    }
}

signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        scanf("%lld%lld%lld",&p[i].x,&p[i].y,&p[i].c);
        p[i].num=i;
    }
    id=n;
    
    sort(p+1,p+n+1,[&](abc X,abc Y){
        if(X.x==Y.x) return X.c<Y.c;
        return X.x<Y.x;
    });
    bool fl=0;
    for(int l=1,r;l<=n;l=r+1){
        r=l;
        while(r+1<=n && p[r+1].c==p[l].c) r++;
        
        // cout<<" "<<l<<" "<<r<<": "<<id+1<<","<<id+4<<endl;
        for(int i=l;i<=r;i++){
            add(id+1,p[i].num,p[i].x-p[l].x);
            add(id+2,p[i].num,p[r].x-p[i].x);
            add(p[i].num,id+3,p[i].x-p[l].x);
            add(p[i].num,id+4,p[r].x-p[i].x);
        }
        if(fl){
            add(id-4+4,id+1,p[l].x-p[l-1].x);
            add(id+3,id-4+2,p[l].x-p[l-1].x);
        }
        else fl=1;
        id+=4;
    }
    // return 0;
    
    sort(p+1,p+n+1,[&](abc X,abc Y){
        if(X.y==Y.y) return X.c<Y.c;
        return X.y<Y.y;
    });
    fl=0;
    for(int l=1,r;l<=n;l=r+1){
        r=l;
        while(r+1<=n && p[r+1].c==p[l].c) r++;
        
        for(int i=l;i<=r;i++){
            add(id+1,p[i].num,p[i].y-p[l].y);
            add(id+2,p[i].num,p[r].y-p[i].y);
            add(p[i].num,id+3,p[i].y-p[l].y);
            add(p[i].num,id+4,p[r].y-p[i].y);
        }
        if(fl){
            add(id-4+4,id+1,p[l].y-p[l-1].y);
            add(id+3,id-4+2,p[l].y-p[l-1].y);
        }
        else fl=1;
        id+=4;
    }
    
    dijkstra();
    // for(int i=1;i<=n;i++) cout<<dis[i]<<" ";
    // cout<<endl;
    
    sort(p+1,p+n+1,[&](abc X,abc Y){
        return X.num<Y.num;
    });
    int ans=dis[n];
    for(int i=1;i<=n;i++){
        ans=min(ans,dis[i]+max(abs(p[i].x-p[n].x),abs(p[i].y-p[n].y)));
        // cout<<dis[i]<<" "<<max(abs(p[i].x-p[n].x),abs(p[i].y-p[n].y))<<endl;
    }
    cout<<ans;
    
}

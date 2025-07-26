#include <bits/stdc++.h>
using namespace std;
const int N=1e5+5,M=1e5+5,INF=1e9;

struct nod{
    int to,nxt,f;
}e[M*2];
int head[N],cnt=1;
void add(int u,int v,int f){
    e[++cnt]={v,head[u],f};
    head[u]=cnt;
}
void qadd(int u,int v,int f){
    add(u,v,f);
    add(v,u,0);
}


int siz,st,ed;
int dis[N];
queue <int> q;
bool bfs(){
    for(int i=1;i<=siz;i++) dis[i]=INF;
    dis[st]=0;
    q.push(st);
    while(q.size()){
        int u=q.front(); q.pop();
        for(int i=head[u];i;i=e[i].nxt){
            int v=e[i].to;
            if(!e[i].f || dis[v]<INF) continue;
            dis[v]=dis[u]+1;
            q.push(v);
        }
    }
    return dis[ed]<INF;
}

int cur[N];
int dfs(int u,int flow){
    if(u==ed) return flow;
    int del=flow;
    for(int i=cur[u];i && del;i=e[i].nxt){
        cur[u]=i;
        int v=e[i].to;
        if(e[i].f && dis[v]==dis[u]+1){
            int x=dfs(v,min(del,e[i].f));
            del-=x;
            e[i].f-=x,e[i^1].f+=x;
            
        }
        
    }
    return flow-del;
}

int dinic(){
    int tot=0;
    while(bfs()){
        for(int i=1;i<=siz;i++) cur[i]=head[i];
        tot+=dfs(st,INF);
    }
    return tot;
}


int n,m;
int a[55][55],ans[110][110];
int rec[55][55][4];

int rd(){
    char c=getchar();
    int x=0;
    while(!isdigit(c)) c=getchar();
    while(isdigit(c)) x=(x<<1)+(x<<3)+c-'0',c=getchar();
    return x;
}
int typ(int x,int y){
    bool fx=(x==1 || x==n),fy=(y==1 || y==m);
    if(fx && fy) return 0;
    else if(!fx && !fy) return 2;
    else return 1;
}
int mp[3]={3,5,8};
int ID(int x,int y){
    return (x-1)*m+y;
}

int fx[4][2]={{0,-1},{0,1},{-1,0},{1,0}};

int main(){
    n=rd(),m=rd();
    for(int i=1;i<=n*2-1;i++){
        for(int j=1;j<=m*2-1;j++){
            ans[i][j]='#';
        }
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++){
            int x=rd();
            ans[i*2-1][j*2-1]=x+'0';
            a[i][j]=mp[typ(i,j)]-x;
        }
    
    
    // for(int i=1;i<=n;i++){
    //     for(int j=1;j<=m;j++){
    //         cout<<a[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
    
    st=n*m+1,ed=n*m+2; siz=ed;
    int tot=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(!a[i][j]) continue;
            tot++;
            int u=ID(i,j);
            if((i+j)%2==0){
                qadd(st,u,1);
                for(int t=0;t<4;t++){
                    int nx=i+fx[t][0],ny=j+fx[t][1],v=ID(nx,ny);
                    if(nx<1 || nx>n || ny<1 || ny>m || !a[nx][ny]) continue;
                    int t1=typ(i,j),t2=typ(nx,ny);
                    if(j>1 && j<m && i==1 && nx==2) continue;
                    if(j>1 && j<m && i==2 && nx==1) continue;
                    if(j>1 && j<m && i==n-1 && nx==n) continue;
                    if(j>1 && j<m && i==n && nx==n-1) continue;
                    
                    if(i>1 && i<n && j==1 && ny==2) continue;
                    if(i>1 && i<n && j==2 && ny==1) continue;
                    if(i>1 && i<n && j==m-1 && ny==m) continue;
                    if(i>1 && i<n && j==m && ny==m-1) continue;
                    rec[i][j][t]=cnt;
                    qadd(u,v,1);
                }
            }
            else qadd(u,ed,1);
            
        }
    }
    
    int ret=dinic();
    // cout<<ret<<" "<<tot<<endl;
    
    if(ret*2<tot){
        cout<<"NO";
        return 0;
    }
    cout<<"YES\n";
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(!a[i][j]) continue;
            if((i+j)%2==0){
                for(int t=0;t<4;t++){
                    int num=rec[i][j][t];
                    if(!num) continue;
                    if(e[num+2].f){
                        ans[i*2-1+fx[t][0]][j*2-1+fx[t][1]]='.';
                        // cout<<i<<" "<<j<<" "<<t<<endl;
                    }
                }
            }
            
        }
    }
    
    for(int i=1;i<=n*2-1;i++){
        for(int j=1;j<=m*2-1;j++){
            putchar(ans[i][j]);
        }
        putchar('\n');
    }
}

#pragma GCC optimize(2)
#include<bits/stdc++.h>
using namespace std;
// #define int long long
const int N=6600,M=2e6+5,INF=1e9;
int T,n,k;

int pr[M],pct;
bool vis[M];
void init(int lim){
    for(int i=2;i<=lim;i++){
        if(!vis[i]) pr[++pct]=i;
        for(int j=1;j<=pct && i*pr[j]<=lim;j++){
            vis[i*pr[j]]=1;
            if(i%pr[j]==0) break;
        }
    }
}

struct nod{
    int to,nxt,f;
}e[N*N/4];
int head[N],cnt;
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
queue <int> que;
bool bfs(){
    for(int i=1;i<=siz;i++) dis[i]=INF;
    dis[st]=0;
    que.push(st);
    while(que.size()){
        int u=que.front(); que.pop();
        for(int i=head[u];i;i=e[i].nxt){
            int v=e[i].to;
            if(!e[i].f || dis[v]<INF) continue;
            dis[v]=dis[u]+1;
            que.push(v);
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

int a[N],p[N],q[N],pid,qid;

int cal(int t,int d){
	if(t+d/2>=k) return 2*k;
	else return 2*(t+d/2)+min(k-t-d/2,(pid+qid-d-2*t)+d%2);
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
    init(M-5);
//    for(int i=1;i<=10;i++) cout<<pr[i]<<" ";
//    return 0;
	cin>>T;
	
	while(T--){
        cin>>n>>k;
        pid=qid=0;
        for(int i=1;i<=n;i++) cin>>a[i];
        sort(a+1,a+n+1);
        for(int i=1;i<=n;i++){
            bool fl=0;
            for(int j=1;j<=n && !fl;j++){
                if(i==j) continue;
                if(!vis[a[i]+a[j]]) fl=1;
            }
            if(!fl) continue;
            if(a[i]%2) p[++pid]=a[i];
            else q[++qid]=a[i];
        }
        int one=0;
        while(one+1<=pid && p[one+1]==1) one++;
        
        st=pid+qid+1,ed=pid+qid+2; siz=ed;
        for(int i=1;i<=siz;i++) head[i]=0;
        cnt=1;
        
//        for(int i=1;i<=pid;i++) cout<<p[i]<<" "; cout<<endl;
//        for(int i=1;i<=qid;i++) cout<<q[i]<<" "; cout<<endl;
        
        
        for(int i=one+1;i<=pid;i++) qadd(st,i,1);
        for(int j=1;j<=qid;j++) qadd(j+pid,ed,1);
        for(int i=1;i<=pid;i++){
            for(int j=1;j<=qid;j++){
                if(!vis[p[i]+q[j]])
					qadd(i,j+pid,1);
//					,cout<<"edg "<<i<<" "<<j<<endl;
            }
        }
        
        int tot=dinic(),ans=0;
        ans=max(ans,cal(tot,one));
        
        for(int i=1;i<=one;i++) qadd(st,i,1);
        int tmax=tot+dinic();
//        cout<<0<<": "<<tot<<endl;
		
        for(int i=1;i<=one;i++){
            ans=max(ans,cal(min(tmax,tot+i),one-i));
//            cout<<i<<": "<<tot<<endl;
        }
        cout<<ans<<endl;
	}
	
}

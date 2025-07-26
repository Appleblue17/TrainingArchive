#pragma GCC optimize(2)
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5,INF=1e9;
#define Pii pair<int,int>
#define MP make_pair

int n,m,q,ans[N];
vector < pair<int,int> > Gr[N],L[N],R[N],iL[N],iR[N];
int num[N],id;

int in[N];
bool vis[N];
queue <int> qu;

struct que{
    int st,ed,num,bias;
};
vector <que> G,H;
vector <que> P[N],Q[N];
int tmp[N];
int sav[N],ct;

int rd(){
    char c=getchar();
    int tot=0;
    while(!isdigit(c)) c=getchar();
    while(isdigit(c)) tot=(tot<<1)+(tot<<3)+(c^'0'),c=getchar();
    return tot;
}

void wt(int x){
    if(!x) return ;
    wt(x/10);
    putchar(x%10+'0');
}


void solveF(que x){
    int st=x.st,ed=x.ed,num=x.num,bias=x.bias;
    for(Pii e: R[st]){
        if(e.first==ed) ans[num]=min(ans[num],bias+e.second);
    }
    //L
    for(Pii e: iL[ed]){
        if(e.first==st) ans[num]=min(ans[num],bias+e.second);
    }
}

int main(){
    n=rd(),m=rd();
    memset(ans,0x7f,sizeof(ans));
    for(int i=1;i<=n;i++) tmp[i]=INF;
    
    for(int i=1;i<=m;i++){
        int u=rd(),v=rd(),w=rd();
        Gr[u].push_back(MP(v,w));
        Gr[v].push_back(MP(u,w));
        in[u]++,in[v]++;
    }
    
    for(int i=1;i<=n;i++)
        if(in[i]<=5) qu.push(i),vis[i]=1;
    while(qu.size()){
        int u=qu.front(); qu.pop();
        num[u]=++id;
        for(Pii e: Gr[u]){
            int v=e.first;
            if(vis[v]) continue;
            in[v]--;
            if(in[v]<=5) qu.push(v),vis[v]=1;
        }
    }
    
    // for(int i=1;i<=n;i++) cout<<num[i]<<" ";
    // cout<<endl;
    
    for(int u=1;u<=n;u++){
        for(Pii e: Gr[u]){
            int v=e.first,w=e.second;
            if(num[u]>num[v]) L[u].push_back(MP(v,w)),iL[v].push_back(MP(u,w));
            else R[u].push_back(MP(v,w)),iR[v].push_back(MP(u,w));
        }
    }
    
    for(int i=1;i<=n;i++)
        assert(R[i].size()<=5 && iL[i].size()<=5);
    
    q=rd();
    for(int i=1;i<=q;i++){
        int st,ed; scanf("%d%d",&st,&ed);
        H.push_back((que){st,ed,i,0});
        G.push_back((que){st,ed,i,0});
        solveF((que){st,ed,i,0});
    }
    
    // k=3
    for(que x: H){
        int st=x.st,ed=x.ed,num=x.num;
        //R__
        for(Pii e: R[st]){
            G.push_back((que){e.first,ed,num,e.second});
        }
        //__L
        for(Pii e: iL[ed]){
            G.push_back((que){st,e.first,num,e.second});
        }
        //LRR
        P[st].push_back(x);
        //LLR
        Q[ed].push_back(x);
    }
    
    for(int u=1;u<=n;u++){
        if(!P[u].size()) continue;
        ct=0;
        for(Pii e: L[u]){
            int v=e.first;
            for(Pii e1: R[v]){
                int x=e1.first;
                for(Pii e2: R[x]){
                    int y=e2.first;
                    sav[++ct]=y;
                    tmp[y]=min(tmp[y],e.second+e1.second+e2.second);
                }
            }
        }
        for(que x: P[u]) ans[x.num]=min(ans[x.num],tmp[x.ed]);
        while(ct) tmp[sav[ct]]=INF,ct--;
    }
    for(int u=1;u<=n;u++){
        if(!Q[u].size()) continue;
        ct=0;
        for(Pii e: iR[u]){
            int v=e.first;
            for(Pii e1: iL[v]){
                int x=e1.first;
                for(Pii e2: iL[x]){
                    int y=e2.first;
                    sav[++ct]=y;
                    tmp[y]=min(tmp[y],e.second+e1.second+e2.second);
                }
            }
        }
        for(que x: Q[u]) ans[x.num]=min(ans[x.num],tmp[x.st]);
        while(ct) tmp[sav[ct]]=INF,ct--;
    }
    
    // k=2
    for(que x: G){
        int st=x.st,ed=x.ed,num=x.num,bias=x.bias;
        //R_
        for(Pii e: R[st]){
            solveF((que){e.first,ed,num,bias+e.second});
        }
        //_L
        for(Pii e: iL[ed]){
            solveF((que){st,e.first,num,bias+e.second});
        }
        //LR
        P[st].push_back(x);
    }
    for(int u=1;u<=n;u++){
        if(!P[u].size()) continue;
        ct=0;
        for(Pii e: L[u]){
            int v=e.first;
            for(Pii e1: R[v]){
                int x=e1.first;
                sav[++ct]=x;
                tmp[x]=min(tmp[x],e.second+e1.second);
            }
        }
        for(que x: P[u]) ans[x.num]=min(ans[x.num],x.bias+tmp[x.ed]);
        while(ct) tmp[sav[ct]]=INF,ct--;
    }
    
    
    for(int i=1;i<=q;i++){
        if(ans[i]>=INF) puts("-1");
        else wt(ans[i]),putchar('\n');
    }
}

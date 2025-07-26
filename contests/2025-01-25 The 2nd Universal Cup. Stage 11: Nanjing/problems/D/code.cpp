#pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+5,INF=1e9;

int T,n,fa[N];
char S[N];
vector <int> G[N];

priority_queue <int> P[N],Q[N];
int tagP[N],tagQ[N];
int siz[N],f[N],mn[N];

void ins(int u,int x,int typ){
    if(!typ){
        int s=-Q[u].top()+tagQ[u];
        if(x<=s) P[u].push(x-tagP[u]);
        else{
            Q[u].pop();
            P[u].push(s-tagP[u]);
            Q[u].push(-(x-tagQ[u]));
            f[u]+=x-s;
        }
    }
    else{
        int s=P[u].top()+tagP[u];
        if(x>=s) Q[u].push(-(x-tagQ[u]));
        else{
            P[u].pop();
            Q[u].push(-(s-tagQ[u]));
            P[u].push(x-tagP[u]);
            f[u]+=s-x;
        }
    }
}

void dfs(int u){
    int son=0;
    mn[u]=INF;
    for(int v: G[u]){
        dfs(v);
        if(siz[v]>siz[son]) son=v;
        mn[u]=min(mn[u],mn[v]+1);
    }
    if(!son){
        P[u].push(0);
        Q[u].push(0);
        mn[u]=0;
    }
    else{
        swap(P[u],P[son]); swap(tagP[u],tagP[son]);
        swap(Q[u],Q[son]); swap(tagQ[u],tagQ[son]);
        f[u]=f[son];
        
        for(int v: G[u]){
            if(v==son) continue;
            //merge
            while(P[v].size()){
                int x=P[v].top()+tagP[v]; P[v].pop();
                ins(u,x,0);
            }
            while(Q[v].size()){
                int x=-Q[v].top()+tagQ[v]; Q[v].pop();
                ins(u,x,1);
            }
            f[u]+=f[v];
            
        }
    }
    
    while(1){
        int x=mn[u];
        int s=P[u].top()+tagP[u];
        if(x>=s){
            Q[u].push(-(x-tagQ[u]));
            break;
        }
        else{
            P[u].pop();
            Q[u].push(-(s-tagQ[u]));
            P[u].push(x-tagP[u]);
            f[u]+=s-x;
        }
    }
    
    if(S[u]=='0'){ //red
        if(Q[u].size()){
            int x=-Q[u].top(); Q[u].pop();
            Q[u].push(-(x-1));
            tagQ[u]++;
        }
    }
    else{
        tagP[u]++; tagQ[u]++;
        if(P[u].size()){
            int x=P[u].top(); P[u].pop();
            P[u].push(x+1);
            tagP[u]--;
        }
    }
    siz[u]=P[u].size()+Q[u].size();
}

int main(){
    cin>>T;
    while(T--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            G[i].clear();
            while(P[i].size()) P[i].pop();
            while(Q[i].size()) Q[i].pop();
            f[i]=0;
            tagP[i]=tagQ[i]=0;
        }
        
        scanf("\n%s",S+1);
        for(int i=2;i<=n;i++){
            scanf("%d",&fa[i]);
            G[fa[i]].push_back(i);
        }
        
        dfs(1);
        
        for(int i=1;i<=n;i++) printf("%d ",f[i]);
        printf("\n");
    }
}



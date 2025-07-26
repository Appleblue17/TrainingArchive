#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#include<bits/stdc++.h>
using namespace std;
const int N=105, M=1e7;
int lin[M], nxt[M], to[M], val[M], tot=1;
inline void in(int x, int y, int z){
    nxt[++tot]=lin[x]; lin[x]=tot; to[tot]=y; val[tot]=z;
    nxt[++tot]=lin[y]; lin[y]=tot; to[tot]=x; val[tot]=0;
}
const int inf=1e9;
int Test, n, m;
char s[N][N];
int id[N][N][2], idx;
bool ban[N][N][2];
int S, T;
int dis[M];
int cur[M];
int dx[4]={1, 1, -1, -1};
int dy[4]={1, -1, 1, -1};
int q[M], hh, tt;
inline bool bfs(){
    for(int i=1; i<=idx; ++i) dis[i]=inf, cur[i]=lin[i];
    dis[S]=0; q[hh=tt=1]=S;
    while(hh<=tt){
        int x=q[hh++];
        for(int i=lin[x]; i; i=nxt[i]){
            int y=to[i];
            if(!val[i]||dis[y]<inf) continue;
            dis[y]=dis[x]+1;
            q[++tt]=y;
        }
    }
    return dis[T]<inf;
}
inline int dfs(int x, int flow){
    if(x==T) return flow;
    int del=flow;
    for(int &i=cur[x]; i&&del; i=nxt[i]){
        int y=to[i];
        if(val[i]&&dis[y]==dis[x]+1){
            int z=dfs(y, min(del, val[i]));
            del-=z;
            val[i]-=z; val[i^1]+=z;
        }
    }
    return flow-del;
}
inline bool inr(int x, int y){
    return x>=1&&x<n&&y>=1&&y<m;
}
int main(){
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    scanf("%d", &Test);
    while(Test--){
        scanf("%d%d", &n, &m);
        for(int i=1; i<=n; ++i) scanf("%s", s[i]+1);
        for(int i=1; i<n; ++i){
            for(int j=1; j<m; ++j){
                for(int o=0; o<2; ++o) id[i][j][o]=++idx, ban[i][j][o]=0;
            }
        }
        S=++idx; T=++idx;
        for(int i=1; i<n; ++i){
            for(int j=1; j<m; ++j){
                if(s[i][j]=='W') ban[i][j][0]=1;
                if(s[i][j]=='B') ban[i][j][1]=1;
                if(s[i+1][j]=='W') ban[i][j][1]=1;
                if(s[i+1][j]=='B') ban[i][j][0]=1;
                if(s[i][j+1]=='W') ban[i][j][1]=1;
                if(s[i][j+1]=='B') ban[i][j][0]=1;
                if(s[i+1][j+1]=='W') ban[i][j][0]=1;
                if(s[i+1][j+1]=='B') ban[i][j][1]=1;
            }
        }
        int all=2*(n-1)*(m-1);
        for(int i=1; i<n; ++i){
            for(int j=1; j<m; ++j){
                all-=ban[i][j][0]+ban[i][j][1];
                if(ban[i][j][0]&&ban[i][j][1]){
                    continue;
                }
                if((i+j)&1){
                    if(!ban[i][j][0]) in(S, id[i][j][0], 1);
                    else in(id[i][j][0], T, inf);
                    if(!ban[i][j][1]) in(id[i][j][1], T, 1);
                    else in(S, id[i][j][1], inf);
                    in(id[i][j][0], id[i][j][1], inf);
                }
                else{
                    if(!ban[i][j][0]) in(id[i][j][0], T, 1);
                    else in(S, id[i][j][0], inf);
                    if(!ban[i][j][1]) in(S, id[i][j][1], 1);
                    else in(id[i][j][1], T, inf);
                    in(id[i][j][1], id[i][j][0], inf);
                }
            }
        }
        for(int i=1; i<n; ++i){
            for(int j=1; j<m; ++j){
                for(int k=0; k<4; ++k){
                    int ii=i+dx[k], jj=j+dy[k];
                    if((i+j)&1){
                        if(inr(ii, j)){
                            in(id[i][j][0], id[ii][j][0], inf);
                            in(id[ii][j][1], id[i][j][1], inf);
                        }
                        if(inr(i, jj)){
                            in(id[i][j][0], id[i][j][0], inf);
                            in(id[i][jj][1], id[i][j][1], inf);
                        }
                        if(inr(ii, jj)){
                            in(id[i][j][0], id[ii][jj][1], inf);
                            in(id[ii][jj][0], id[i][j][1], inf);
                        }
                    }
                    else{
                        if(inr(ii, j)){
                            in(id[i][j][1], id[ii][j][1], inf);
                            in(id[ii][j][0], id[i][j][0], inf);
                        }
                        if(inr(i, jj)){
                            in(id[i][j][1], id[i][j][1], inf);
                            in(id[i][jj][0], id[i][j][0], inf);
                        }
                        if(inr(ii, jj)){
                            in(id[i][j][1], id[ii][jj][0], inf);
                            in(id[ii][jj][1], id[i][j][0], inf);
                        }
                    }
                }
            }
        }
        int mincut=0;
        while(bfs()){
            int fl=dfs(S, inf);
            while(fl) mincut+=fl, fl=dfs(S, inf);
        }
        printf("%d\n", all-mincut);
        for(int i=1; i<=idx; ++i) lin[i]=0;
        tot=1;
        idx=0;
        for(int i=1; i<n; ++i){
            for(int j=1; j<m; ++j){
                if(ban[i][j][0]&&ban[i][j][1]) continue;
                if((i+j)&1){
                    if(dis[id[i][j][0]]<inf){
                        s[i][j]=s[i+1][j+1]='B';
                        s[i+1][j]=s[i][j+1]='W';
                    }
                    if(dis[id[i][j][1]]==inf){
                        s[i][j]=s[i+1][j+1]='W';
                        s[i+1][j]=s[i][j+1]='B';
                    }
                }
                else{
                    if(dis[id[i][j][0]]==inf){
                        s[i][j]=s[i+1][j+1]='B';
                        s[i+1][j]=s[i][j+1]='W';
                    }
                    if(dis[id[i][j][1]]<inf){
                        s[i][j]=s[i+1][j+1]='W';
                        s[i+1][j]=s[i][j+1]='B';
                    }
                }
            }
        }
        for(int i=1; i<=n; ++i){
            for(int j=1; j<=m; ++j){
                if(s[i][j]=='?') s[i][j]='B';
                putchar(s[i][j]);
            }
            putchar('\n');
        }
    }
}

#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const int N=1e6+5;
int T, n, m;
mt19937_64 rnd(time(0));
ull msk=rnd();
ull xorshift(ull x){
    x^=msk;
    x^=x<<13;
    x^=x>>7;
    x^=x<<17;
    x^=msk;
    return x;
}
vector<int> e[N];
bool flag=0;
int stk[N], top;
bool oncir[N], vis[N];
vector<int> cir;
void dfs(int x, int fa){
    if(flag) return ;
    vis[x]=1; stk[++top]=x;
    for(auto y:e[x]) if(y!=fa){
        if(!vis[y]){
            dfs(y, x);
            if(flag) return ;
        }
        else{
            oncir[y]=1;
            cir.push_back(y);
            do{
                oncir[stk[top]]=1;
                cir.push_back(stk[top]);
                --top;
            }while(stk[top]!=y);
            flag=1; return ;
        }
    }
    vis[x]=0; --top;
}
ull hs[N];
void dfs2(int x, int fa){
    hs[x]=1;
    for(auto y:e[x]) if(y!=fa&&oncir[y]==0){
        dfs2(y, x);
        hs[x]+=xorshift(hs[y]);
    }
}
int main(){
    scanf("%d", &T);
    while(T--){
        scanf("%d%d", &n, &m);
        if(m==n-1){
            for(int i=1, x, y; i<=m; ++i){
                scanf("%d%d", &x, &y);
            }
            printf("YES\n");
            continue;
        }
        if(m>n){
            for(int i=1, x, y; i<=m; ++i){
                scanf("%d%d", &x, &y);
            }
            printf("NO\n");
            continue;
        }
        if(m==n){
            for(int i=1; i<=n; ++i) e[i].clear(), oncir[i]=0, vis[i]=0;
            for(int i=1, x, y; i<=m; ++i){
                scanf("%d%d", &x, &y);
                e[x].push_back(y); e[y].push_back(x);
            }
            top=0; flag=0;
            cir.clear();
            dfs(1, 0);
            bool ans1=1, ans2=1;
            for(auto t:cir) {
                dfs2(t, 0);
                if(hs[t]!=hs[cir[0]]) ans1=0;
            }
            if(cir.size()%2==0){
                for(int i=0; i<(int)cir.size(); ++i) {
                    if(hs[cir[i]]!=hs[cir[i&1]]) ans2=0;
                }
            }
            else{
                ans2=0;
            }
            if(ans1||ans2) printf("YES\n");
            else printf("NO\n");
        }
    }
    
}

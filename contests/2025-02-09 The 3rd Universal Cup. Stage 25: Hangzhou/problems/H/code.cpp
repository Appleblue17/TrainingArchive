#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int T;
int n, k;
int lp[N], rp[N], rk[N];
inline bool cmp(int x, int y){
    return rp[x]-lp[x]>rp[y]-lp[y];
}
int dep[N];
int fa[N];
void solve(){
    scanf("%d%d", &n, &k);
    for(int i=1; i<=k; ++i) scanf("%d%d", &lp[i], &rp[i]), rk[i]=i;
    sort(rk+1, rk+k+1, cmp);
    int mx=rp[rk[1]]-lp[rk[1]]+1;
    fa[lp[rk[1]]]=0;
    int sz=mx-1;
    for(int i=1; i<mx; ++i) dep[i]=rp[rk[1]]-i;
    for(int i=k; i>1; --i){
        int id=rk[i];
        int len=rp[id]-lp[id]+1;
        if(len==mx) break;
        fa[lp[id]]=dep[len];
        if(len!=mx-1) sz+=len;
    }
    for(int i=2; i<=k; ++i) {
        int id=rk[i];
        int len=rp[id]-lp[id]+1;
        if(len!=mx) break;
        if(sz<len){
            printf("IMPOSSIBLE\n");
            return ;
        } 
        fa[lp[id]]=lp[rk[1]];
    }
    for(int i=1; i<=k; ++i){
        for(int j=lp[i]+1; j<=rp[i]; ++j) fa[j]=j-1;
    }
    for(int i=1; i<=n; ++i) printf("%d ", fa[i]);
    putchar('\n');
    return ;
}
int main(){
    scanf("%d", &T);
    while(T--){
        solve();
    }
}

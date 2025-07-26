#include <bits/stdc++.h>
using namespace std;
const int N=305, M=60005, B=80;
const int m1=1e9+7, m2=998244353;
int n, q, m, K, len;
char s[N][M], t[M];
struct node{
    int x, y;
};
node bs=(node){131, 137};
inline node operator +(node x, node y){
    return (node){(x.x+y.x)%m1, (x.y+y.y)%m2};
}
inline node operator -(node x, node y){
    return (node){(x.x-y.x+m1)%m1, (x.y-y.y+m2)%m2};
}
inline node operator *(node x, node y){
    return (node){(int)(1ll*x.x*y.x%m1), (int)(1ll*x.y*x.y%m2)};
}
inline bool operator !=(node x, node y){
    return x.x!=y.x||x.y!=y.y;
}
int pos[M], lp[M], rp[M];
node hs[N][M], hs2[M];
int main(){
    scanf("%d%d%d%d", &n, &q, &m, &K);
    for(int i=1; i<=m; ++i) pos[i]=(i-1)/B+1;
    for(int i=1; i<=pos[m]; ++i) lp[i]=rp[i-1]+1, rp[i]=rp[i-1]+B;
    rp[pos[m]]=m;
    for(int i=1; i<=n; ++i){
        scanf("%s", s[i]+1);
        for(int j=1; j<=pos[m]; ++j){
            for(int p=lp[j]; p<=rp[j]; ++p) hs[i][j]=hs[i][j]*bs+(node){s[i][p], s[i][p]};
        }
    }
    while(q--){
        scanf("%s", t+1);
        int ans=0;
        for(int i=1; i<=pos[m]; ++i){
            hs2[i]=(node){0, 0};
            for(int p=lp[i]; p<=rp[i]; ++p) hs2[i]=hs2[i]*bs+(node){t[p], t[p]};
        }
        for(int i=1; i<=n; ++i){
            int diff=0;
            for(int j=1; j<=pos[m]; ++j) if(hs2[j]!=hs[i][j]){
                for(int p=lp[j]; p<=rp[j]; ++p) diff+=s[i][p]!=t[p];
                if(diff>K) break;
            }
            ans+=(diff<=K);
        }
        printf("%d\n", ans);
    }
}

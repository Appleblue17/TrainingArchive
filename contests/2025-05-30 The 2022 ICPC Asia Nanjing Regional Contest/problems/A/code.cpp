#include<bits/stdc++.h>
using namespace std;
const int N=2003, M=1e6+5;
int T, n, m, k;
char s[M];
int sum[N][N];
inline int get(int u, int d, int l, int r){
    return sum[d][r]-sum[u-1][r]-sum[d][l-1]+sum[u-1][l-1];
}
inline void solve(){
    scanf("%d%d%d", &n, &m, &k);
    scanf("%s", s+1);
    int len=strlen(s+1);
    int up=1, dp=n, lp=1, rp=m;
    int mxu=1, mnd=n, mxl=1, mnr=m;
    for(int i=1; i<=len; ++i){
        if(s[i]=='U'){
            ++up; ++dp;
            mxu=max(mxu, up);
        }
        if(s[i]=='D'){
            --up; --dp;
            mnd=min(mnd, dp);
        }
        if(s[i]=='L'){
            ++lp; ++rp;
            mxl=max(mxl, lp);
        }
        if(s[i]=='R'){
            --lp; --rp;
            mnr=min(mnr, rp);
        }
    }
    if(mxu>mnd||mxl>mnr){
        if(k==0) {
            printf("%d\n", n*m);
        }
        else{
            printf("0\n");
        }
        return ;
    }
    int goal=(mnd-mxu+1)*(mnr-mxl+1)-k;
    if(goal<0){
        printf("0\n");
        return ;
    }
    int sx=n, sy=m;
    for(int i=0; i<=n*2+1; ++i){
        for(int j=0; j<=m*2+1; ++j){
            sum[i][j]=0;
        }
    }
    sum[sx][sy]=1;
    for(int i=1; i<=len; ++i){
        if(s[i]=='U') ++sx;
        if(s[i]=='D') --sx;
        if(s[i]=='L') ++sy;
        if(s[i]=='R') --sy;
        sum[sx][sy]=1;
    }
    for(int i=0; i<=n*2+1; ++i){
        for(int j=0; j<=m*2+1; ++j){
            sum[i][j]+=sum[i][j-1]+sum[i-1][j]-sum[i-1][j-1];
        }
    }
    int ans=0;
    for(int i=0; i<=n-1; ++i){
        for(int j=0; j<=m-1; ++j){
            if(goal==get(mxu+i, mnd+i, mxl+j, mnr+j)){
                ++ans;
            }
        }
    }
    printf("%d\n", ans);
}
int main(){
    scanf("%d", &T);
    while(T--){
        solve();
    }
}

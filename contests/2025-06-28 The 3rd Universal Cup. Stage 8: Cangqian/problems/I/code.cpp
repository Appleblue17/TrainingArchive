#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=510,INF=1e9;
int n,m,x[N][N];
int t[N],se,s[N],vel[N],id[N],rk[N];
map<int,int> ma[N];

bool cmp(int a,int b){
    if(vel[a]!=vel[b])return vel[a]<vel[b];
    else return x[1][a]<x[1][b];
}

void solve(){
    scanf("%lld%lld",&n,&m);
    for(int i=0;i<=m;i++){
        vel[i]=0;
        s[i]=0;
        t[i]=0;
        id[i]=i;
        rk[i]=0;
        ma[i].clear();
    }
    se=0;
    t[1]=0;
    //cout << '*' << endl;
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            scanf("%lld",&x[i][j]);
            s[i]+=x[i][j];
            ma[i][x[i][j]]++;
        }
        if(i != 1)t[i]=s[i]-s[1];
    }
    if(t[2]==0){
        sort(id+1,id+n+1,cmp);
        for(int i=1;i<=n;i++){
            rk[id[i]]=i;
        }
        for(int i=1;i<=n;i++){
            printf("%lld ",rk[i]);
        }
        putchar('\n');
        return;
    }
    int mn = 1e18;
    for(int i=2;i<=m;i++){
        if(t[i] < mn){
            mn = t[i];
            se = i;
        }
    }
    for(int i=1;i<=n;i++){
        if(vel[i])continue;
        for(int j=1;j<=n;j++){
            bool f=0;
            int y1 = x[2][j]-x[1][i];
            if(y1<0)continue;
            for(int k=3;k<=m;k++){
                
                //int y = y1*t[k]/t[2]+x[1][i];
                //printf("y1=%lld,t[%lld]=%lld\n",y1,k,t[k]);fflush(stdout);
                if(y1*t[k]%t[2] != 0){
                    f=1;
                    break;
                }
                int y = y1*t[k]/t[2]+x[1][i];
                if(!ma[k][y]){
                    f=1;
                    break;
                }
            }
            if(!f){
                vel[i]=y1;
            }
        }
    }
    sort(id+1,id+n+1,cmp);
    for(int i=1;i<=n;i++){
        rk[id[i]]=i;
    }
    for(int i=1;i<=n;i++){
        printf("%lld ",rk[i]);
    }
    putchar('\n');
}


signed main(){
    //freopen("I.in","r",stdin);
    int T;
    scanf("%lld",&T);
    while(T--){
        solve();
    }
}

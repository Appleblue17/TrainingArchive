#include <bits/stdc++.h>
using namespace std;
const int N=5e5+5,INF=1e9;
int n,w[N],c[N];
bool npr[N];
vector <int> D[N];

void ins(int *f,int *g,int val,int col){
    if(g[0]==col){
        if(val>f[0]){
            f[0]=val,g[0]=col;
        }
    }
    else if(g[1]==col){
        if(val>f[1]){
            f[1]=val; g[1]=col;
        }
        if(f[1]>f[0]) swap(f[0],f[1]),swap(g[0],g[1]);
    }
    else{
        if(val>f[0]){
            f[1]=f[0],g[1]=g[0];
            f[0]=val,g[0]=col;
        }
        else if(val>f[1]){
            f[1]=val; g[1]=col;
        }
    }
}
int query(int *f,int *g,int col){
    if(g[0]!=col) return f[0];
    return f[1];
}

int f[N][2],g[N][2];
int dp[N];



signed main(){
    scanf("%d",&n);
    int mx=0;
    for(int i=1;i<=n;i++) scanf("%d",&w[i]),mx=max(mx,w[i]);
    for(int i=1;i<=n;i++) scanf("%d",&c[i]);
    
    for(int i=2;i<=mx;i++){
        if(npr[i]) continue;
        D[i].push_back(i);
        for(int j=i*2;j<=mx;j+=i){
            npr[j]=1;
            D[j].push_back(i);
        }
    }
    
    // for(int i=1;i<=mx;i++){
    //     cout<<i<<": ";
    //     for(int t: D[i]) cout<<t<<" ";
    //     cout<<endl;
    // }
    // return 0;
    int ans=0;
    for(int i=1;i<=n;i++){
        // if(i==3){
        //     cout<<f[2][0]<<" "<<f[2][1]<<"  "<<g[2][0]<<" "<<g[2][1]<<endl;
        // }
        dp[i]=1;
        for(int t: D[w[i]]){
            dp[i]=max(dp[i],query(f[t],g[t],c[i])+1);
        }
        for(int t: D[w[i]]){
            ins(f[t],g[t],dp[i],c[i]);
        }
        ans=max(ans,dp[i]);
        // cout<<i<<": "<<dp[i]<<endl;
    }
    cout<<ans;
}

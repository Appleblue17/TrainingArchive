#include <bits/stdc++.h>
using namespace std;
#define $ +w

const int N=502,mod=998244353;
int n,m,w;
int l[N],r[N],L[N],R[N];

int dp[N][N][N*2];
void gmod(int &x){
    x+=(x>>31) & mod;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>l[i]>>r[i],w=max(w,r[i]);
    for(int i=1;i<=m;i++) cin>>L[i]>>R[i],w=max(w,R[i]);
    
    dp[0][0][0 $]=1;
    for(int i=0;i<=n;i++){
        for(int j=0;j<=m;j++){
            if(i || j){
                for(int t=-w;t<=w;t++) gmod(dp[i][j][t $]+=dp[i][j][t-1 $]-mod);
            }
            
            for(int k=-w;k<0;k++){
                if(!dp[i][j][k $]) continue;
                gmod(dp[i+1][j][k+l[i+1] $]+=dp[i][j][k $]-mod);
                gmod(dp[i+1][j][k+r[i+1]+1 $]-=dp[i][j][k $]);
            }
            
            for(int k=0;k<=w;k++){
                if(!dp[i][j][k $]) continue;
                gmod(dp[i][j+1][k-R[j+1] $]+=dp[i][j][k $]-mod);
                gmod(dp[i][j+1][k-L[j+1]+1 $]-=dp[i][j][k $]);
            }
        }
    }
    
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cout<<dp[i][j][0 $]<<" ";
        }
        cout<<endl;
    }
}

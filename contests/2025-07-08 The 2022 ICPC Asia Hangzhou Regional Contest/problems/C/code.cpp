#include<bits/stdc++.h>
using namespace std;
// #define int long long
const int N=3300,M=11,INF=1e9;
int n,k,ans=-INF;
int pre[N][N],suf[N][N];

int p[N],w[N][M];

signed main(){
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        scanf("%d",&p[i]);
        for(int j=1;j<=p[i];j++) scanf("%d",&w[i][j]);
    }
    for(int i=0;i<=n+1;i++){
        for(int j=0;j<=k;j++) pre[i][j]=suf[i][j]=-INF;
    }
    
    pre[0][0]=0;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=k;j++){
            pre[i][j]=max(pre[i][j],pre[i-1][j]);
            if(j+p[i]<=k) pre[i][j+p[i]]=max(pre[i][j+p[i]],pre[i-1][j]+w[i][p[i]]);
        }
    }
    suf[n+1][0]=0;
    for(int i=n;i>=1;i--){
        for(int j=0;j<=k;j++){
            suf[i][j]=max(suf[i][j],suf[i+1][j]);
            if(j+p[i]<=k) suf[i][j+p[i]]=max(suf[i][j+p[i]],suf[i+1][j]+w[i][p[i]]);
        }
    }
    
    // for(int i=1;i<=n;i++){
    //     for(int j=0;j<=k;j++) cout<<pre[i][j]<<" ";
    //     cout<<endl;
    // }
    
    for(int j=0;j<=k;j++) ans=max(ans,pre[n][j]);
    
    for(int i=1;i<=n;i++){
        for(int t=1;t<p[i];t++){
            int tot=-INF;
            for(int j=0;j<=k-t;j++) tot=max(tot,pre[i-1][j]+suf[i+1][k-t-j]);
            ans=max(ans,tot+w[i][t]);
        }
    }
    cout<<ans;
}

#include<bits/stdc++.h>
using namespace std;
// #define int long long
const int N=8800,INF=1e9;
int T,n;
char typ[N];
int a[N],b[N];

int dp[N][N];

signed main(){
    
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        int alc=0;
        for(int i=1;i<=n;i++){
            scanf("\n%c",&typ[i]);
            if(typ[i]=='C'){
                scanf("%d%d",&a[i],&b[i]);
            }
            else alc++;
        }
        
        for(int i=0;i<=n;i++)
            for(int j=0;j<=n;j++)
                dp[i][j]=-INF;
        
        dp[0][0]=0;
        for(int i=1;i<=n;i++){
            for(int j=0;j<=n;j++){
                if(dp[i-1][j]==-INF) continue;
                if(typ[i]=='B'){
                    dp[i][j+1]=max(dp[i][j+1],dp[i-1][j]);
                    if(dp[i-1][j]>0) dp[i][j]=max(dp[i][j],dp[i-1][j]-1);
                }
                else{
                    dp[i][max(j-a[i],0)]=max(dp[i][max(j-a[i],0)],dp[i-1][j]);
                    dp[i][j]=max(dp[i][j],dp[i-1][j]+b[i]);
                }
            }
            // for(int j=n-1;j>=0;j--) dp[i][j]=max(dp[i][j],dp[i][j+1]);
            
            // for(int j=0;j<=n;j++) cout<<dp[i][j]<<" ";
            // cout<<endl;
        }
        int ans=0;
        for(int j=0;j<=n;j++)
            if(dp[n][j]!=-INF) ans=max(ans,alc-j);
        // cout<<ans<<endl;
        printf("%d\n",ans+alc);
    }
}

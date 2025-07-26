#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=3e5+5,INF=1e9;
int n,a[N],mn[N];

int dp[N];

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
    for(int i=1;i<=n;i++) dp[i]=INF;
    mn[0]=INF;
    
    int ans=n;
    for(int i=1;i<=n;i++){
        if(i>64) dp[i]=min(dp[i],mn[i-64]+i);
        for(int j=max(0ll,i-64);j<i;j++){
            if(!j || (i-j>=__builtin_popcountll(a[i]^a[j]))){
                dp[i]=min(dp[i],dp[j]+i-j-1);
            }
        }
        ans=min(ans,dp[i]+n-i);
        mn[i]=min(mn[i-1],dp[i]-i-1);
        // cout<<dp[i]<<" ";
    }
    cout<<ans;
    
}

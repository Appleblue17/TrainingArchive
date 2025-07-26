#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=22,M=3e6+5,mod=998244353;

int n,ans;
int a[N];

int dp[M];

signed main(){
    cin>>n;
    for(int i=0;i<n;i++) cin>>a[i];
    
    memset(dp,0x7f,sizeof(dp));
    dp[0]=0;
    for(int mac=0;mac<(1<<(n-1));mac++){
        // cout<<mac<<": "<<dp[mac]<<endl;
        for(int i=1;i<=n-1;i++){
            int x=mac | (mac<<i) | (1<<(i-1));
            int lbt=x & ((1<<(n-1))-1),hbt=x>>n;
            int nmac=lbt | hbt;
            dp[nmac]=min(dp[nmac],dp[mac]+a[i]);
            // cout<<mac<<" "<<i<<" -> "<<nmac<<endl;
        }
    }
    // for(int mac=0;mac<(1<<(n-1));mac++) cout<<dp[mac]<<" ";
    // cout<<endl;
    
    
    for(int k=1;k<(1<<(n-1));k<<=1){
        for(int i=0;i<(1<<(n-1));i+=k*2){
            for(int j=0;j<k;j++){
                int x=i+j,y=i+j+k;
                dp[x]=min(dp[x],dp[y]);
            }
        }
    }
    // for(int mac=0;mac<(1<<(n-1));mac++) cout<<dp[mac]<<" ";
    // cout<<endl;
    
    for(int mac=0;mac<(1<<(n-1));mac++){
        int nmac=0;
        for(int i=0;i<n-1;i++){
            if(mac>>i & 1) nmac|=1<<(n-2-i);
        }
        
        ans=(ans+dp[nmac]%mod*(mac*4%mod+1)%mod)%mod;
        // cout<<mac*2<<" "<<mac*2+1<<": "<<dp[nmac]<<endl;
    }
    cout<<ans;
}

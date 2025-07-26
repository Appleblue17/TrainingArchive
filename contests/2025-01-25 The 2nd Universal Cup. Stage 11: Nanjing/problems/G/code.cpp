#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=5500,M=1e4+5;
int n,W,k,ans;
pair<int,int> p[N];
int w[N],v[N],sufv[N];


int suf[N];
priority_queue <int> qu;

int dp[M];

signed main(){
    cin>>n>>W>>k;
    for(int i=1;i<=n;i++) scanf("%lld%lld",&p[i].second,&p[i].first);
    sort(p+1,p+n+1);
    for(int i=1;i<=n;i++) w[i]=p[i].second,v[i]=p[i].first;
    for(int i=n;i>=1;i--) sufv[i]=sufv[i+1]+v[i];
    
    int sum=0;
    for(int i=n;i>=1;i--){
        suf[i]=sum;
        
        qu.push(-w[i]);
        if(qu.size() > k){
            int x=-qu.top(); qu.pop();
            sum+=x;
        }
    }
    suf[0]=sum;
    // for(int i=1;i<=n;i++) cout<<suf[i]<<" ";
    // cout<<endl;
    
    if(suf[0]<=W) ans=max(ans,dp[W-suf[0]]+sufv[1]);
    for(int i=1;i<=n;i++){
        for(int j=W;j>=w[i];j--){
            dp[j]=max(dp[j],dp[j-w[i]]+v[i]);
        }
        if(suf[i]<=W) ans=max(ans,dp[W-suf[i]]+sufv[i+1]);
    }
    cout<<ans;
}

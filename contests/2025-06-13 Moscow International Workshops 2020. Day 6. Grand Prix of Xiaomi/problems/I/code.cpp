#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+5,INF=1e18;
int n,k,T,ans=INF;
int a[N],s[N];
int dp[N];

int f[N*4];
void modify(int l,int r,int o,int x,int k){
    if(l==r){
        f[o]=k;
        return ;
    }
    int mid=(l+r)>>1;
    if(x<=mid) modify(l,mid,o<<1,x,k);
    else modify(mid+1,r,o<<1|1,x,k);
    f[o]=min(f[o<<1],f[o<<1|1]);
}
int query(int l,int r,int o,int L,int R){
    if(L<=l && r<=R){
        return f[o];
    }
    int mid=(l+r)>>1,tot=INF;
    if(L<=mid) tot=min(tot,query(l,mid,o<<1,L,R));
    if(R>mid) tot=min(tot,query(mid+1,r,o<<1|1,L,R));
    return tot;
}

signed main(){
    for(int i=0;i<N*4;i++) f[i]=INF;
    
    scanf("%lld%lld%lld",&n,&k,&T);
    for(int i=1;i<=n;i++) scanf("%lld",&a[i]),s[i]=s[i-1]+a[i];
    
    modify(0,n,1,0,0);
    for(int i=1;i<=n;i++){
        dp[i]=dp[i-1]+a[i];
        
        if(i>k){
            int pos=lower_bound(s,s+i+1,s[i]-T)-s;
            // cout<<i<<" "<<s[i]-T<<" "<<pos<<endl;
            if(pos<=i-k-1){
                dp[i]=min(dp[i],query(0,n,1,pos,i-k-1));
                // dp[i]=min(dp[i],dp[pos]);
            }
        }
        
        modify(0,n,1,i,dp[i]);
        // cout<<dp[i]<<" ";
    }
    for(int i=0;i<=n;i++){
        if(s[n]-s[i]<=T){
            ans=min(ans,dp[i]);
        }
    }
    cout<<ans;
    
}

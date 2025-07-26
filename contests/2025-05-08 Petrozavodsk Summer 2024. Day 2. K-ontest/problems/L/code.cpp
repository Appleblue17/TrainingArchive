#pragma GCC optimize("O2")
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+5,M=330,INF=1e18;
int n,s,r,mx;
int val[M];

struct abc{
    int x,y;
};
bool operator <(abc X,abc Y){
    return (__int128)X.x*(__int128)Y.y<(__int128)Y.x*(__int128)X.y;
}
abc min(abc X,abc Y){
    return (X<Y)?X:Y;
}
abc max(abc X,abc Y){
    return (X<Y)?Y:X;
}
void reduce(abc &X){
    int g=__gcd(X.x,X.y);
    X=(abc){X.x/g,X.y/g};
}

void pr(abc X){
    cout<<X.x<<"/"<<X.y;
}

int dp[N];

signed main() {
    cin>>n>>s>>r;
    for(int i=1;i<=n;i++){
        int A,B;
        scanf("%lld%lld",&A,&B);
        val[A]=max(val[A],B);
        mx=max(mx,A);
    }
    
    for(int i=1;i<N;i++) dp[i]=-INF;
    for(int i=1;i<=mx;i++){
        if(val[i]){
            for(int j=0;j+i<N;j++){
                dp[j+i]=max(dp[j+i],dp[j]+val[i]);
            }
        }
    }
    // for(int i=0;i<=10;i++) cout<<dp[i]<<" ";
    // cout<<endl;
    
    abc mn={1,0};
    int mner;
    for(int i=1;i<=mx;i++){
        if(val[i]){
            abc tmp={i,val[i]};
            if(tmp<mn){
                mn=tmp;
                mner=i;
            }
        }
    }
    reduce(mn);
    // pr(mn);
    // cout<<" "<<mner<<endl;
    int a0=mner,b0=val[mner];
    
    double lim0=sqrt(1.0*r*s*(1.0*mn.x/mn.y));
    int lim=ceil(lim0);
    // cout<<"lim: "<<lim0<<" "<<lim<<endl;
    
    int K=lim/a0;
    // cout<<K<<endl;
    
    abc ans={1,0};
    int mink,mini;
    for(int k=K;k>=0 && lim-k*a0<N;k--){
        int del=lim-k*a0;
        for(int i=max(0ll,del-400);i<=min(N-1,del+400);i++){
            int sa=k*a0+i,sb=k*b0+dp[i];
            abc tmp=(abc){sa*sb+r*s,sb};
            if(tmp<ans){
                ans=tmp;
                mink=k,mini=i;
            }
        }
    }
    reduce(ans);
    cout<<ans.x<<" "<<ans.y;
    // pr(ans);
    // cout<<endl<<mink<<" "<<mini;
}

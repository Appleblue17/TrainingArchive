#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1.1e6+5,INF=1e18;
int T,len,m;
char S[N];
int a,b,n,ans;

int pw[13];

signed main(){
    scanf("%lld%lld%lld",&n,&a,&b);
    ans=0;
    for(int i=1;i<=n;i++){
        if(n-i+1>0)ans += (n-i+1)*(n-i+2)/2;
        if(n-2*i+1>0)ans += (n-2*i+1)*(n-2*i+2)/2;
    }
    for(int i=1;i<=n;i++){
        if(a-i+1 > 0){
            ans -= min(min(i,b),min(a-b+1,a-i+1));
            if(n-a >= i){
                ans -= min(min(i,b),min(a-b+1,a-i+1));
            }
        }
        
    }
    printf("%lld\n",ans);
}

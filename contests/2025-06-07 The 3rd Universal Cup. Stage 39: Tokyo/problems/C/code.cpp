#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1100,mod=998244353;
int T,k,m;
int ksm(int a,int x){
    int tot=1;
    while(x){
        if(x & 1ll) tot=tot*a%mod;
        a=a*a%mod;
        x>>=1ll;
    }
    return tot;
}

signed main(){
    cin>>T;
    while(T--){
        scanf("%lld%lld",&k,&m);
        int ans=m*(m+1)/2%mod*ksm(m+1,k-1)%mod*k%mod;
        printf("%lld\n",ans);
    }
}

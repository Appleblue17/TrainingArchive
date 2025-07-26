#include <bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 998244353;

int ksm(int a,int x){
    int tot=1;
    while(x){
        if(x & 1ll) tot=tot*a%mod;
        a=a*a%mod;
        x>>=1;
    }
    return tot;
}

int T,n,k;

signed main(){
    cin>>T;
    while(T--){
        scanf("%lld%lld",&n,&k);
        int tot=0;
        for(int i=2;i<=k+1;i++) tot=(tot+ksm(i,n))%mod;
        printf("%lld\n",tot);
    }
}

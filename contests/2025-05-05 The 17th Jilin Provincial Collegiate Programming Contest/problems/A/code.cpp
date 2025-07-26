// #pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+5,mod=998244353,inv2=(mod+1)/2;

int ksm(int a,int x){
    int tot=1;
    while(x){
        if(x & 1ll) tot=tot*a%mod;
        a=a*a%mod;
        x>>=1ll;
    }
    return tot;
}

int n;
int pw2[N],f[N],s[N],g[N];

signed main() {
    cin>>n;
    pw2[0]=1;
    for(int i=1;i<=n;i++) pw2[i]=pw2[i-1]*2%(mod-1);
    
    for(int i=1;i<=n;i++){
        f[i]=(ksm(2,pw2[i-1])+mod-1)%mod;
        
        int A=(ksm(2,pw2[i-1])+mod-1)%mod;
        int B=ksm(2,pw2[i-1])*(ksm(inv2,pw2[i-1])+mod-1)%mod;
        // for(int j=1;j<i;j++){
        //     int w=(mod-ksm(2,mod-1-pw2[j-1])*(1+mod-ksm(inv2,pw2[j-1]))%mod*ksm((ksm(inv2,pw2[j])+mod-1)%mod,mod-2)%mod)%mod;
        //     f[i]=(f[i]+(A+B*w%mod)*f[j]%mod)%mod;
        // }
        
        f[i]=(f[i]+s[i-1]*A%mod+g[i-1]*B%mod)%mod;
        s[i]=(s[i-1]+f[i])%mod;
        g[i]=(g[i-1]+(mod-ksm(inv2,pw2[i-1])*(1+mod-ksm(inv2,pw2[i-1]))%mod*ksm((ksm(inv2,pw2[i])+mod-1)%mod,mod-2)%mod)%mod*f[i]%mod)%mod;
        
        // cout<<i<<": "<<f[i]<<endl;
    }
    cout<<s[n];
    
}

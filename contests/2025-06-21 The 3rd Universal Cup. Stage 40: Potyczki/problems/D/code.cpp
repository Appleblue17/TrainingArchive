#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=7700;
int K,mod;

int ksm(int a,int x){
    int tot=1;
    while(x){
        if(x & 1ll) tot=tot*a%mod;
        a=a*a%mod;
        x>>=1ll;
    }
    return tot;
}

int mul[N],inv[N];
void init(int lim){
    mul[0]=inv[0]=1;
    for(int i=1;i<=lim;i++) mul[i]=mul[i-1]*i%mod;
    inv[lim]=ksm(mul[lim],mod-2);
    for(int i=lim-1;i>=1;i--) inv[i]=inv[i+1]*(i+1)%mod;
}
int C(int m,int n){
    if(m<0 || n<0 || m<n) return 0;
    return mul[m]*inv[n]%mod*inv[m-n]%mod;
}

int s[N];

signed main(){
    cin>>K>>mod;
    init(N-5);
    for(int n=1;n<=K;n++){
        s[0]=1;
        for(int i=1;i<=n;i++) s[i]=(s[i-1]+C(n,i))%mod;
        
        int ans=0;
        for(int t=0;t<=n;t++){
            int m=2*t-n,lim=max(0ll,-m);
            int R=(n-m)/2-lim-1;
            int tot=(lim*C(n,t)%mod+s[min(n,R)])%mod;
            int sum=(n-t)*C(n,t)%mod;
            ans=(ans+(sum+mod-tot)%mod*mul[t]%mod*mul[n-t]%mod)%mod;
        }
        printf("%lld\n",ans);
    }
}

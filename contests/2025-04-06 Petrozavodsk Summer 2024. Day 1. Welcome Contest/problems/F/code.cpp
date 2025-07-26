#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=6e5+5,mod=998244353;

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

int n,k,ans;
signed main(){
    init(N-5);
    cin>>n>>k;
    if(!k) return puts("1"),0;
    int ik=ksm(k,mod-2);
    for(int t=1;t<=k;t++){
        int s=2*t-1;
        int tot=ik*C(k,t)%mod*C(k,t-1)%mod;
        // cout<<t<<": ";
        // cout<<tot<<" "<<C(2*k+n-s,n-s)<<endl;
        ans=(ans+tot*C(2*k+n-s,n-s)%mod)%mod;
    }
    cout<<ans;
}

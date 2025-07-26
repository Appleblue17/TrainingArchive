#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+5,mod=998244353;
int T,n,m,k;

int ksm(int a,int x){
    int tot=1;
    while(x){
        if(x & 1ll) tot=tot*a%mod;
        a=a*a%mod;
        x>>=1ll;
    }
    return tot;
}

void gmod(int &x){
    if(x>=mod) x-=mod;
}

int mul[N],inv[N];
void init(int lim){
    mul[0]=inv[0]=1;
    for(int i=1;i<=lim;i++) mul[i]=mul[i-1]*i%mod;
    inv[lim]=ksm(mul[lim],mod-2);
    for(int i=lim-1;i>=1;i--) inv[i]=inv[i+1]*(i+1)%mod;
}

int solve(int n,int m,int k){
    k*=2;
    if((n & 1) && (m & 1)) k--;
    int ans=0;
    for(int t=max(0ll,k);2*t-k<=min(n,m);t++){
        int x=(n-(2*t-k))/2,y=(m-(2*t-k))/2;
        gmod(ans+=mul[(n+m)/2]*inv[t]%mod*inv[t-k]%mod*inv[x]%mod*inv[y]%mod);
    }
    return ans;
}
signed main(){
    init(N-5);
    cin>>T;
    while(T--){
        scanf("%lld%lld%lld",&n,&m,&k);
        int ans;
        if((n-m)%2==0) ans=solve(n,m,k);
        else ans=(solve(n-1,m,-k)+solve(n,m-1,-(k-n%2)))%mod;
        printf("%lld\n",ans);
    }
}


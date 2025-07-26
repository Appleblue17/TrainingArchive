#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e5+5,mod=998244353;

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

int mul[N],inv[N];
void init(int lim){
    mul[0]=inv[0]=1;
    for(int i=1;i<=lim;i++) mul[i]=mul[i-1]*i%mod;
    inv[lim]=ksm(mul[lim],mod-2);
    for(int i=lim-1;i>=1;i--) inv[i]=inv[i+1]*(i+1)%mod;
}
int C(int m,int n){
    if(m<n || m<0 || n<0) return 0;
    return mul[m]*inv[n]%mod*inv[m-n]%mod;
}

signed main(){
    init(N);
    cin>>T;
    while(T--){
        scanf("%lld%lld",&n,&k);
        int ans=0;
        
        int b=-n+1,c=k-n;
        int delta=b*b-4*c;
        if(delta>=0){
            int t=sqrt(delta);
            while(t*t<delta) t++;
            while(t*t>delta) t--;
            if(t*t==delta && (b+t)%2==0){
                int x=(-b-t)/2;
                ans=(ans+C(n,x))%mod;
                if(t){
                    x=(-b+t)/2;
                    ans=(ans+C(n,x))%mod; 
                }
            }
        }
        
        printf("%lld\n",ans);
    }
}

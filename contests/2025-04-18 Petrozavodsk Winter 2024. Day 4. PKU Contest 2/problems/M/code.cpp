#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=3e5+5,mod=998244353;
int T,n,m;

int ksm(int a,int x){
    int tot=1;
    while(x){
        if(x & 1) tot=tot*a%mod;
        a=a*a%mod;
        x>>=1;
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
    if(n<0 || m<0 || m<n) return 0;
    return mul[m]*inv[n]%mod*inv[m-n]%mod;
}

// int cal(int n,int m){
//     int tot=0;
//     for(int i=0;i<=n/2;i++){
//         for(int j=0;j<=m/2;j++){
//             tot=(tot+C(i+j,i)*C(i+j,i)%mod*C(n-2*i+m-2*j,n-2*i)%mod)%mod;
//         }
//     }
//     return tot;
// }

signed main(){
    init(N-5);
    cin>>T;
    while(T--){
        scanf("%lld%lld",&n,&m);
        printf("%lld\n",C(n/2+m/2,n/2)*C((n-1)/2+1+(m-1)/2+1,(n-1)/2+1)%mod*(n/2+m/2+1)%mod);
    }
    // for(n=1;n<=12;n+=1){
    //     for(m=1;m<=12;m+=1){
    //         int tot=cal(n,m);
    //         int tmp=0;
    //         tmp=C(n/2+m/2,n/2)*C((n-1)/2+1+(m-1)/2+1,(n-1)/2+1)%mod;
    //         cout<<tot/(n/2+m/2+1)<<" "<<tmp<<endl;
    //     }
    //     cout<<endl;
    // }
}

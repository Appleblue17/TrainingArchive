#include<bits/stdc++.h>
using namespace std;
const int N=2e6+5,mod=1e9+7;
int n;
int a[N];

int mul(int n){
    int tot=1;
    for(int i=1;i<=n;i++) tot=1ll*tot*i%mod;
    return tot;
}

long long A,B;
signed main(){
    cin>>n;
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    sort(a+1,a+n+1);
    
    if(n%2==1){
        for(int i=1;i<=n/2;i++) A-=a[i];
        for(int i=n/2+2;i<=n;i++) A+=a[i];
        B=1ll*n*mul(n/2)%mod*mul(n/2)%mod*2%mod;
    }
    else{
        for(int i=1;i<=n/2;i++) A-=a[i];
        for(int i=n/2+1;i<=n;i++) A+=a[i];
        B=1ll*2*mul(n/2)%mod*mul(n/2)%mod;
    }
    cout<<A*2<<" "<<B;
}

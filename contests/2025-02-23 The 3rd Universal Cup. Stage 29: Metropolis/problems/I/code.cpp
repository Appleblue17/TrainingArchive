#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=200010;
const ll mo=998244353;
ll n,k,a[N*2];
bool cmp(ll x,ll y){
    return x>y;
}
void solve(){
    scanf("%lld%lld",&n,&k);
    for(int i=1;i<=n;i++){
        scanf("%lld",&a[i]);
    }
    sort(a+1,a+n+1,cmp);
    ll m=n;
    for(int i=1;i<=n;i++){
        if(a[i] == 0){
            m=i-1;
            break;
        }
    }
    ll t = (m-1)/(k-1)*(k-1)+1;
    if(m==0)t=0;
    //printf("t=%lld\n",t);
    ll ans=a[1]%mo;
    for(int i=2;i<=t;i++){
        ans = ans*a[i]%mo;
    }
    /*for(int i=2;i+(k-2)<=n;i+=(k-1)){
        ll tmp=1;
        for(int j=0;j<=k-2;j++){
            //printf("i=%d,j=%d\n",i,j);
            tmp = a[i+j]*tmp%mo;
        }
        if(tmp != 0)ans = ans * tmp % mo;
    }*/
    printf("%lld\n",ans%mo);
    for(int i=1;i<=n;i++){
        a[i]=0;
    }
}
int main(){
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}

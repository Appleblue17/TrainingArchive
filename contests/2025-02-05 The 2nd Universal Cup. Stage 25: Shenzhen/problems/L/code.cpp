#include <bits/stdc++.h>
using namespace std;
const int N=1100;
int n,a[N],b[N];
const int mo = 1e9+9;
typedef long long ll;
ll ksm(ll a,ll b){
    ll base = a,ret=1;
    while(b){
        if(b%2)ret = ret*base%mo;
        base = base*base%mo;
        b/=2;
    }
    return ret;
}



ll E,C,ans;

int main(){
	long long m,k;
    scanf("%lld%lld",&m,&k );
    E=0;ans=0;C=1;
    for(int i=1;i<=k;i++){
        ans += (E+1)*m%mo;
        ans %= mo;
        E = E*(C-1)+E*m+m;
        E %= mo;
        E *= ksm(C+m-1,mo-2);
        E%=mo;
        C = C+m-1;
    }
    printf("%lld\n",ans);
}

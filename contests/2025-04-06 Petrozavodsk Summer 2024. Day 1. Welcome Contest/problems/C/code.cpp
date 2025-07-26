#include <bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 998244353;

int T,n;

signed main(){
    cin>>T;
    while(T--){
        scanf("%lld",&n);
        if(n%2) puts("0");
        else printf("%lld\n",n*(n/2-1));
    }
}

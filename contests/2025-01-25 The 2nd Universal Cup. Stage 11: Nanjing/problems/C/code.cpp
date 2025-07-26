#pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int lim=(1ll<<62);
int T,P,m;

signed main(){
    cin>>T;
    while(T--){
        scanf("%lld%lld",&P,&m);
        int x=m/P-1,ans=x+1;
        for(int k=x+1;k<=x+50;k++){
            if(k<=lim/P && ((k*P+1)^(P-1))<=m) ans++;
        }
        printf("%lld\n",ans);
    }
}

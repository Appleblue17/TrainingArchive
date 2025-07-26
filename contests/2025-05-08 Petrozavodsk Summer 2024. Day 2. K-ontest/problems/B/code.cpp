#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+5;
int n,a[N];
int ans;

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
    for(int i=1;i<=n;i++){
        ans+=abs(a[i]);
        for(int j=i*2;j<=n;j+=i) a[j]-=a[i];
    }
    cout<<ans;
    
}

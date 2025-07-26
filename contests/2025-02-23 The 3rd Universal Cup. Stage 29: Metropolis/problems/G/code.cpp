#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e5+5;
int T, n;
ll a[N], b[N], c[N];
const ll inf=3e18;
bool check(ll lim){
    vector<ll> v1, v2;
    int ans=0;
    for(int i=1; i<=n; ++i) if(a[i]==0) ans+=(b[i]>=lim);
    for(int i=1; i<=n; ++i){
        if(a[i]>0){
            ll bd=(lim-b[i])/a[i];
            while((bd-1)*a[i]+b[i]>=lim) --bd;
            while(bd*a[i]+b[i]<lim) ++bd;
            v1.push_back(bd);
        }
        if(a[i]<0){
            ll bd=(lim-b[i])/a[i];
            while((bd-1)*a[i]+b[i]>=lim) ++bd;
            while(bd*a[i]+b[i]<lim) --bd;
            v2.push_back(bd);
        }
    }
    sort(v1.begin(), v1.end(), greater<ll>());
    vector<ll> bin;
    for(int i=1; i<=n; ++i) bin.push_back(c[i]);
    sort(bin.begin(), bin.end());
    for(auto t:v1){
        if(t<=bin.back()){
            ++ans;
            bin.pop_back();
        }
    }
    sort(bin.begin(), bin.end(), greater<ll>());
    sort(v2.begin(), v2.end());
    for(auto t:v2){
        if(t>=bin.back()){
            ++ans;
            bin.pop_back();
        }
    }
    return ans>=(n+1)/2;
}
void solve(){
    scanf("%d", &n);
    for(int i=1; i<=n; ++i) scanf("%lld", &a[i]);
    for(int i=1; i<=n; ++i) scanf("%lld", &b[i]);
    for(int i=1; i<=n; ++i) scanf("%lld", &c[i]);
    ll L=-inf, R=inf, mid, ans=-inf;
    while(L<=R){
        mid=(L+R)/2ll;
        if(check(mid)){
            ans=mid; L=mid+1;
        }
        else{
            R=mid-1;
        }
    }
    printf("%lld\n", ans);
}
int main(){
    scanf("%d", &T);
    while(T--){
        solve();
    }
}

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+5;
ll n,a[N],vis[N];
ll ans;

void solve(){
    scanf("%lld",&n);
    for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
    ll x = 0;
    ans=0;ll id=0;
    for(int i=0;i<=29;i++){
        x += (1<<i);
        //cout << x << endl;
        for(int j=1;j<=n;j++){
            if((a[j]&x) <= n)vis[a[j]&x]=1;
        }
        ll tmp=0;
        for(int j=0;j<=n;j++){
            if(!vis[j]){
                tmp=j;
                break;
            }
        }
        if(tmp > ans){
            ans = tmp;
            id = x;
        }
        for(int j=0;j<=n;j++){
            vis[j]=0;
        }
        
    }
    printf("%lld\n",id);
}

int main(){
    int T;
    cin >> T;
    while(T--){
        solve();
    }
}

#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e7+5,mod=1e9+7;
int n;
int pw2[N],F[N];
char S[N];
int f[N];

void solve(){
    int k,x,y,ans=0;
    scanf("%lld%lld%lld",&k,&x,&y);
    int x1,y1;
    if(k==1){
        printf("%lld\n",x+y);
        return;
    }
    if(k&1){
        y1 = k/2;
        x1=1;
        if(y/y1 <= x){
            ans += y/y1;
            y = y%y1;
            x -= ans;
            x += y*2;
            ans += x/k;
        }
        else{
            ans += x;
            y -= ans*y1;
            y1 = k/2+1;
            ans += y/y1;
        }
        printf("%lld\n",ans);
    }
    else{
        ans = y*2+x;
        ans = ans/k;
        printf("%lld\n",ans);
    }
}

signed main() {
    int T;
    cin >> T;
    while(T--){
        solve();
    }
    
}

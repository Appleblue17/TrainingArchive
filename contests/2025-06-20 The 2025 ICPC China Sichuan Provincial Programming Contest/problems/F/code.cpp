#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e6+6;
int T, n, m;
char s[N];
int w1[N], w0[N];
void solve(){
    scanf("%d", &n);
    scanf("%s", s+1);
    ll sum=0; int pre1=0;
    for(int i=1; i<=n; ++i){
        if(s[i]!='1') sum+=pre1;
        else pre1++;
    }
    pre1=0;
    for(int i=1; i<=n; ++i){
        w1[i]=pre1;
        if(s[i]!='0') ++pre1;
    }
    int suf0=0;
    for(int i=n; i>=1; --i){
        w0[i]=suf0;
        if(s[i]!='1') ++suf0;
    }
    ll ans=sum;
    for(int i=1; i<=n; ++i) if(s[i]=='?'){
        sum-=w1[i]; sum+=w0[i];
        ans=max(ans, sum);
    }
    printf("%lld\n", ans);
}
int main(){
    scanf("%d", &T);
    while(T--){
        solve();
    }
}

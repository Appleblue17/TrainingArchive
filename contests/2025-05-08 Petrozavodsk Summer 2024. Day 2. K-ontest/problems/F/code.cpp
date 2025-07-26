#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+5;
int n, a[N];
void solve(){
    scanf("%d", &n);
    for(int i=1; i<=n; ++i) scanf("%d", &a[i]);
    int mx=0;
    vector<int> ans;
    for(int i=1; i<=n;){
        mx=max(mx, a[i]);
        if(mx==i){
            if(i==n) break;
            int j=i;
            while(a[j]<=i) ans.push_back(j), ++j;
            mx=a[j]; i=j;
        }
        else{
            ++i;
        }
    }
    printf("%d\n", ans.size());
    for(auto t:ans) printf("%d ", t);
    putchar('\n');
}
signed main(){
    int T;
    scanf("%d", &T);
    while(T--) solve();
}

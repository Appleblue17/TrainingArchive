#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1100;
int n,m;
int ans;

signed main(){
    cin>>n>>m;
    for(int i=0;i<=n;i++){
        for(int j=0;j<=m;j++){
            int x=min(i,n-i),y=min(j,m-j);
            ans+=x*y*2+x+y;
        }
    }
    cout<<ans;
}


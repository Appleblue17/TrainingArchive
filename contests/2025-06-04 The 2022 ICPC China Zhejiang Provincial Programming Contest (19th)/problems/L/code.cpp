#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+5;
int n,a[N],s[N],ans;

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    sort(a+1,a+n+1);
    
    for(int i=1;i<=n;i++) s[i]=s[i-1]+a[i];
    
    int cur=0;
    for(int t=1;t<=n;t++){
        while(cur+1<=n && s[cur+1]-a[t]*(cur+1)<0) cur++;
        ans=max(ans,cur-t+1);
    }
    cout<<ans;
}

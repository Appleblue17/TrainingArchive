#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+5;
int T,n;
int a[N],b[N],c[N];

signed main(){
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
        if(n<=2){
            puts("1");
            continue;
        }
        for(int i=1;i<=n-1;i++) b[i]=a[i+1]-a[i];
        for(int i=1;i<=n-2;i++) c[i]=b[i+1]-b[i];
        // for(int i=1;i<=n-2;i++) cout<<c[i]<<" ";
        // cout<<endl;
        int ans=0;
        
        int l=1,r;
        for(l=1,r;l<=n-2;l=r+3){
            r=l;
            while(r+1<=n && c[r+1]==c[l]) r++;
            ans++;
            // cout<<l<<" "<<r<<endl;
        }
        if(r<n-2) ans++;
        
        printf("%lld\n",ans);
    }
}

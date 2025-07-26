#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=5e5+5,INF=1e18;
int T,n,m;
int c[N];

signed main(){
    cin>>T;
    while(T--){
        scanf("%lld%lld",&n,&m);
        int ans=-INF,alc=0;
        for(int i=1;i<=n;i++){
            int a,b; scanf("%lld%lld",&a,&b);
            alc+=a;
            c[i]=b-a;
        }
        sort(c+1,c+n+1);
        c[n+1]=0;
        for(int i=n;i>=1;i--) c[i]+=c[i+1];
        
        // cout<<alc<<endl;
        // for(int i=1;i<=n;i++) cout<<c[i]<<" ";
        // cout<<endl;
        
        for(int i=0;i<=min(n-1,m-n);i++){
            if(i==n-1) ans=max(ans,c[1]);
            else ans=max(ans,c[n-i+1]);
        }
        
        printf("%lld\n",ans+alc);
    }
    
}

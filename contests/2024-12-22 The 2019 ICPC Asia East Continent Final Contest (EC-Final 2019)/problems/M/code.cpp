#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+5,INF=1e18;
int n,ans;
int a[N],b[N];
bool vis[N];

int pat[N],id;

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
    for(int i=1;i<=n;i++) scanf("%lld",&b[i]);
    
    ans=a[1];
    for(int t=2;t<=n;t++){
        if(vis[t]) continue;
        id=0;
        int x=t;
        while(x<=n) pat[id++]=x,vis[x]=1,x*=t;
        // for(int i=0;i<id;i++) cout<<pat[i]<<" ";
        
        int mx=0;
        for(int mac=0;mac<(1<<id);mac++){
            int tot=0;
            for(int i=0;i<id;i++){
                if(!(mac>>i & 1)) continue;
                tot+=a[pat[i]];
                for(int j=0;j<i;j++){
                    if(!(mac>>j & 1)) continue;
                    if((i+1)%(j+1)==0) tot-=b[pat[i]];
                }
            }
            mx=max(mx,tot);
        }
        // cout<<": "<<mx<<endl;
        ans+=mx;
    }
    cout<<ans;
    
}

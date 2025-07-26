#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=5e5+5,INF=1e9;
int T,n,m;
int a[N],b[N];

priority_queue <int> q;

signed main(){
    scanf("%lld",&T);
    while(T--){
        scanf("%lld%lld",&n,&m);
        for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
        for(int i=1;i<=n;i++) scanf("%lld",&b[i]);
        sort(b+1,b+n+1);
        
        for(int i=1;i<=n;i++) b[i]+=b[i-1];
        
        a[n+1]=m;
        while(q.size()) q.pop();
        int nw=n,tot=0;
        while(b[nw]>=m) nw--;
        for(int i=n;i>=0 && nw;i--){
            int L=a[i],R=a[i+1];
            if(b[nw]<L) q.push(R-L);
            else{
                while(nw-1>=1 && b[nw-1]>=a[i]){
                    if(q.size()){
                        int x=q.top(); q.pop();
                        tot+=x;
                    }
                    nw--;
                }
                // cout<<nw<<" "<<L<<" "<<b[nw]<<" "<<R<<endl;
                int x=R-b[nw],y;
                if(!q.size()){
                    tot+=x;
                    q.push(b[nw]-L);
                }
                else{
                    y=q.top();
                    q.pop();
                    if(x>=y){
                        tot+=x;
                        q.push(b[nw]-L+y);
                    }
                    else{
                        tot+=y;
                        q.push(R-L);
                    }
                }
                
                nw--;
            }
            
        }
        printf("%lld\n",tot);
        
    }
    
}

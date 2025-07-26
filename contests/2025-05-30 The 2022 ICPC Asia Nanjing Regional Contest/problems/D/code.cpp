#include "bits/stdc++.h"
using namespace std;
#define int long long
const int N=4e5+5,INF=1e18;

int a[N],b[N];
int n,k,m,c,d;

priority_queue <int> q,p;

bool check(int x){
    while(q.size()) q.pop();
    while(p.size()) p.pop();
    
    int lim=x-d+c;
    int tot=0,cur=0,sum=0;
    
    for(int i=1;i<=n;i++) tot+=(a[i]>=x);
    
    for(int i=1;i<=m;i++){
        if(a[i]<x && b[i]>=lim){
            cur++;
            q.push(-b[i]);
        }
    }
    if(tot+cur>=k) return 1;
    
    for(int i=m+1;i<=n;i++){
        lim+=c;
        while(q.size() && -q.top()<lim){
            q.pop();
            cur--;
        }
        if(a[i]<x && b[i]>=lim){
            cur++;
            q.push(-b[i]);
        }
        
        while(p.size() && -p.top()<lim){
            p.pop();
            sum--;
        }
        if(a[i-m]<x && b[i-m]>=lim){
            sum++;
            p.push(-b[i-m]);
        }
        
        if(tot+cur-sum>=k) return 1;
    }
    return 0;
}

signed main(){
    cin>>n>>k>>m>>d>>c;
    int mx=0;
    for(int i=1;i<=n;i++){
        scanf("%lld",&a[i]);
        b[i]=a[i]+i*c;
        mx=max(mx,b[i]);
    }
    int l=0,r=1e16,tot=l;
    while(l<=r){
        int mid=(l+r)>>1ll;
        if(check(mid)) tot=mid,l=mid+1;
        else r=mid-1;
    }
    cout<<tot;
}


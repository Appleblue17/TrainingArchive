#include <bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,k;
double x[N],y[N];


int c[N];
int lowbit(int x){
    return x & (-x);
}
void modify(int x,int k){
    while(x<=n) c[x]=max(c[x],k),x+=lowbit(x);
}
int query(int x){
    int tot=0;
    while(x) tot=max(tot,c[x]),x-=lowbit(x);
    return tot;
}

pair<double,int> p[N];
int mp[N];

bool check(double K){
    for(int i=1;i<=n;i++) c[i]=0;
    for(int i=1;i<=n;i++) p[i]=make_pair(y[i]-x[i]*K,i);
    
    // for(int i=1;i<=n;i++) cout<<p[i].first<<" ";
    // cout<<endl;
    
    sort(p+1,p+n+1);
    for(int i=1;i<=n;i++) mp[p[i].second]=i;
    
    
    for(int i=1;i<=n;i++){
        // cout<<mp[i]<<" ";
        int ret=query(mp[i])+1;
        if(ret>=k) return 1;
        modify(mp[i],ret);
    }
    return 0;
}


int main() {
    cin>>n>>k;
    for(int i=1;i<=n;i++) scanf("%lf%lf",&x[i],&y[i]);
    
    double l=-1e9,r=1e9;
    for(int i=1;i<=50;i++){
        
        double mid=(l+r)/2;
        if(check(mid)) l=mid;
        else r=mid;
    }
    cout<<setprecision(10)<<fixed<<(l+r)/2;
}

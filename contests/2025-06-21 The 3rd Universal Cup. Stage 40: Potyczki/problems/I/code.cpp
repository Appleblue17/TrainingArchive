#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+5;
int n, m, k;
int a[N], b[N];
vector<ll> vec;
bool cmp(int x, int y){
    return abs(x)<abs(y);
}
int main(){
    scanf("%d%d%d", &k, &n, &m);
    for(int i=1; i<=n; ++i) scanf("%d", &a[i]);
    for(int i=1; i<=m; ++i) scanf("%d", &b[i]);
    vector<int> v1, v2, v3, v4;
    for(int i=1; i<=n; ++i){
        if(a[i]>0) v1.push_back(a[i]);
        if(a[i]<0) v2.push_back(a[i]);
    }
    for(int i=1; i<=m; ++i){
        if(b[i]>0) v3.push_back(b[i]);
        if(b[i]<0) v4.push_back(b[i]);
    }
    sort(v1.begin(), v1.end());
    sort(v3.begin(), v3.end());
    while(v1.size()&&v3.size()){
        vec.push_back(1ll*v1.back()*v3.back());
        v1.pop_back(); v3.pop_back();
    }
    sort(v2.begin(), v2.end(), greater<int>());
    sort(v4.begin(), v4.end(), greater<int>());
    while(v2.size()&&v4.size()){
        vec.push_back(1ll*v2.back()*v4.back());
        v2.pop_back(); v4.pop_back();
    }
    sort(vec.begin(), vec.end());
    ll ans=0;
    while(k&&!vec.empty()){
        ans+=vec.back();
        vec.pop_back();
        --k;
    }
    if(k==0){
        printf("%lld\n", ans);
        return 0;
    }
    vector<int> v5, v6;
    while(v1.size()) v5.push_back(v1.back()), v1.pop_back();
    while(v2.size()) v5.push_back(v2.back()), v2.pop_back();
    while(v3.size()) v6.push_back(v3.back()), v3.pop_back();
    while(v4.size()) v6.push_back(v4.back()), v4.pop_back();
    for(int i=1; i<=n; ++i) if(a[i]==0) v5.push_back(0);
    for(int i=1; i<=m; ++i) if(b[i]==0) v6.push_back(0);
    sort(v5.begin(), v5.end(), cmp);
    sort(v6.begin(), v6.end(), cmp);
    while(v5.size()&&v6.size()){
        vec.push_back(1ll*v5.back()*v6.back());
        v5.pop_back(); v6.pop_back();
    }
    for(int i=0; i<k; ++i){
        ans+=1ll*v5[i]*v6[k-i-1];
    }
    printf("%lld\n", ans);
    return 0;
}

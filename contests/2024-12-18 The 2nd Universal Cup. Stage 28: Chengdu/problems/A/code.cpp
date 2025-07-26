#pragma GCC optimize(3)
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pll;
#define mapa make_pair
#define se second
#define fi first
const int N=1000010;
int n;
ll a[N],lmx[N],rmx[N],fa[N],k,ans;
void solve(){
    scanf("%d",&n);
    n += 2;
    ans=0;
    for(int i=1;i<=n;i++){
        lmx[i]=rmx[i]=fa[i]=0;
    }

    for(int i=1;i<=n-2;i++){
        scanf("%lld",&a[i+1]);
        ans += a[i+1];
    }
    a[1]=2e9+10;a[n]=2e9+10;
    k=0;
    for(int i=2;i<=n;i++){
        if(a[i] < a[i-1])k += a[i-1]-a[i];
    }
    k -= a[1];
    stack<int> s;
    s.push(1);
    for(int i=2;i<n;i++){
        while(a[s.top()]<=a[i]){
            s.pop();
        }
        lmx[i]=s.top();
        s.push(i);
    }
    while(!s.empty())s.pop();
    s.push(n);
    for(int i=n-1;i>=2;i--){
        while(a[s.top()]<a[i]){
            s.pop();
        }
        rmx[i]=s.top();
        s.push(i);
    }
    for(int i=2;i<n;i++){
        if(a[lmx[i]]<=a[rmx[i]])fa[i]=lmx[i];
        else fa[i]=rmx[i];
    }
    
    multiset<pll> S;
    for(int i=2;i<n;i++){
        //printf("i=%d,lmx=%lld,rmx=%lld,fa=%lld\n",i,lmx[i],rmx[i],fa[i]);
        //printf("add block width %lld length %lld\n",rmx[i]-lmx[i]-1,a[fa[i]]-a[i]);
        S.insert(mapa(rmx[i]-lmx[i]-1,a[fa[i]]-a[i]));
    }
    //printf("k=%lld,ans=%lld\n",k,ans);
    if(k<0){
        printf("%lld\n",ans);
        return;
    }
    for(auto u:S){
        //printf("block width %lld length %lld\n",u.fi,u.se);
        if(u.se >= k){
            ans += k*u.fi;
            k=0;
            
            break;
        }
        else{
            k -= u.se;
            ans += u.se * u.fi;
        }
    }
    printf("%lld\n",ans);
}
int main(){
    int T;
    cin >> T;
    while(T--){
        solve();
    }
}

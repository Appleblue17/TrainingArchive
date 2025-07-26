#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,p,a[210000],iq;
ll f[210000],ans;
vector<ll> c;
map<ll,ll> ma;
ll ksm(ll a,ll n,ll p){
    ll ret=1,base=a;
    while(n>0){
        if(n%2==1)ret = ret*base%p;
        base = base*base%p;
        n/=2;
    }
    return ret;
}
int main(){
    ll T;
    cin >> T;
    while(T--){
        ma.clear();
        c.clear();
        scanf("%lld%lld",&n,&p);
        for(int i=1;i<=n;i++){
            scanf("%lld",&a[i]);
        }
        for(int k=1;k<=3;k++){
            for(int i=1;i+k<=n;i++){
                ll q = a[i+k]*ksm(a[i],p-2,p)%p;
                //printf("%lld,%lld,get q=%lld\n",a[i],a[i+k],q);
                ma[q]++;
            }
        }
        for(auto it=ma.begin();it!=ma.end();it++){
            if(it->second >= n/4-1){
                c.push_back(it->first);
            }
        }
        ans=0;
        for(ll u:c){
            iq = ksm(u,p-2,p);
            //printf("check %lld\n",u);
            unordered_map<ll,ll> uma;
            for(int i=1;i<=n;i++){
                f[i]=uma[a[i]*iq%p]+1;
                //printf("f[%d]=%lld\n",i,f[i]);
                uma[a[i]]=max(uma[a[i]],f[i]);
                ans = max(ans,f[i]);
            }
            //printf("ans=%lld\n",ans);
        }
        if(ans < (n+1)/2){
            printf("-1\n");
        }
        else printf("%lld\n",ans);
    }
}

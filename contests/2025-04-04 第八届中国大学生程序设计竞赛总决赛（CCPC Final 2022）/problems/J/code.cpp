#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
typedef long long ll;
ll T,x,y,k,n2[70];
ll solve(ll x,ll y,ll k){
    if(x==y)return 0;
    ll t = k;
    ll n=0;
    while(t){
        t/=2;
        n++;
    }
    if(x/n2[n] == y/n2[n]){
        if(abs(x-y)<=1){
            return 1;
        }
        if((x^y) <= k){
            return 1;
        }
        else{
            return 2;
        }
    }
    //printf("n2[n]=%lld\n",n2[n]);
    ll ans=0;
    ll rx = (n2[n]-1)-x%n2[n];
    if(rx == 0){
        ans+=0;
    }
    else if(rx <= k){
        ans+=1;
    }
    else{
        ans+=2;
    }
    ll rd = y/n2[n] - x/n2[n];
    if(k == n2[n]-1){
        ans += (rd-1)*2+1;
    }
    else ans += (rd-1)*3+1;
    ll ry = y%n2[n];
    if(ry == 0){
        ans+=0;
    }
    else if(ry <= k){
        ans+=1;
    }
    else{
        ans+=2;
    }
    return ans;
}
ll f[300];
ll solve2(ll x,ll y,ll K){
    memset(f,48,sizeof(f));
    f[x]=0;
    for(int j=1;j<=128;j++){
        for(int i=0;i<=128;i++){
            if(f[i] <= 300){
                for(int k=0;k<=K ;k++){
                    f[i^k] = min(f[i^k],f[i]+1);
                }
            }
            if(i!=0)f[i-1] = min(f[i-1],f[i]+1);
            f[i+1] = min(f[i+1],f[i]+1);
        }
    }
    return f[y];
}
int main(){
    //freopen("J.in","r",stdin);
    scanf("%lld", &T);
    n2[0]=1;
    for(int i=1;i<=62;i++){
        n2[i]=n2[i-1]*2;
    }
    while(T--){
        scanf("%lld%lld%lld",&x,&y,&k);
        if(x>y)swap(x,y);
        if(k<=1){
            printf("%lld\n",abs(x-y));
            continue;
        }
        //if(solve(x,y,k) != solve2(x,y,k)){
        //    printf("wrong answer at %lld %lld %lld\n",x,y,k);
        //    printf("x^y=%lld\n",x^y);
        //    printf("solve=%lld,solve2=%lld\n",solve(x,y,k),solve2(x,y,k));
        //}
        printf("%lld\n",solve(x,y,k));
    }
}

#include <bits/stdc++.h>
using namespace std;
#define int long long
const int mod=1e9+7;
int n,k,ans;

int S1(int n){
    n%=mod;
    return (n+1)%mod;
}
int S2(int n){
    n%=mod;
    return n*(n+1)/2%mod;
}

int g(int A,int B,int n,int k){
    // sum_{x=0}^n f(Ax+B)
    if(n<0) return 0;
    if(!k) return (A%mod*S2(n)%mod+B%mod*S1(n)%mod)%mod;
    int tot=0;
    if(A%2==0 && B%2==0) tot+=g(A/2,B/2,n,k-1);
    if(A%2==0 && B%2==1) tot+=g(A*3,B*3+1,n,k-1);
    if(A%2==1){
        tot=(tot+g(A*2,B,n/2,k))%mod;
        tot=(tot+g(A*2,B+A,(n+1)/2-1,k))%mod;
    }
    return tot;
}

signed main(){
    cin>>n>>k;
    
    cout<<g(1,0,n,k);
}

#include <bits/stdc++.h>
using namespace std;
#define int __int128
const int mod=998244353;

int solve(int L,int k){
    if(L<=0) return 0;
    int y=(L+1)/2,x=L/2;
    int tot=0,nw=0;
    
    for(int i=k-1,c=1;i>=1;i--,c*=2){
        if(nw+c<=x){
            tot+=c*i;
            nw+=c;
        }
        else{
            int rem=x-nw;
            tot+=rem*i;
            nw+=rem;
            break;
        }
    }
    return tot+min(y,nw+1);
}

long long L,k;
__int128 ans;
signed main(){
    cin>>k>>L;
    L++;
    
    for(int x=L/2-2;x<=L/2;x++){
        int tot=k-1+solve(x,k-1)+solve(L-1-x,k-1);
        ans=max(ans,tot);
    }
    long long anss=ans%mod;
    cout<<anss;
}

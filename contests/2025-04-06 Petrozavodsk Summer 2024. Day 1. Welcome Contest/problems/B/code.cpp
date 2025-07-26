#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=3e5+5,mod=998244353;

int ksm(int a,int x){
    int tot=1;
    while(x){
        if(x & 1ll) tot=tot*a%mod;
        a=a*a%mod;
        x>>=1;
    }
    return tot;
}

int e,p,w,t,n;
int ans;

int mul[N],inv[N];
void init(int lim){
    mul[0]=inv[0]=1;
    for(int i=1;i<=lim;i++) mul[i]=mul[i-1]*i%mod;
    inv[lim]=ksm(mul[lim],mod-2);
    for(int i=lim-1;i>=1;i--) inv[i]=inv[i+1]*(i+1)%mod;
}
int C(int m,int n){
    if(m<n || m<0 || n<0) return 0;
    return mul[m]*inv[n]%mod*inv[m-n]%mod;
}
int A(int m,int n){
    if(n<0) return 0;
    return C(m,n)*mul[n]%mod;
}

signed main(){
    init(N-1);
    cin>>e>>p>>w>>t;
    n=e+p+w;
    for(int k=1;k<=n;k++){
        int sum=1;
        // for(int i=0;i<p;i++){
        //     sum=sum*(n-max(1ll,k-t-i)-i+1-e)%mod;
        // }
        if(k-t<0){
            sum=A(n-e,p);
        }
        else if(k-t>=p){
            sum=ksm(n-(k-t)+1-e,p);
        }
        else{
            // for(int i=0;i<k-t;i++) sum=sum*(n-(k-t)+1-e)%mod;
            // for(int i=k-t;i<p;i++) sum=sum*(n-i-e)%mod;
            // for(int i=0;i<p-(k-t);i++) sum=sum*(n-i-(k-t)-e)%mod;
            sum=ksm(n-(k-t)+1-e,k-t)*A(n-e-(k-t),p-(k-t))%mod;
        }
        
        // cout<<k<<":"<<endl;
        // cout<<n-k<<" "<<e-1<<" "<<C(n-k,e-1)<<endl;
        // cout<<pos<<" "<<sum<<endl;
        // cout<<C(n-k,e-1)*mul[e-1]%mod*ksm(n-pos+1-e,p)%mod<<endl;
        ans=(ans+C(n-k,e-1)*sum%mod)%mod;
    }
    int tot=mul[n]*inv[e]%mod*inv[w]%mod;
    // cout<<ans<<" "<<tot<<endl;
    cout<<ans*ksm(tot,mod-2)%mod;
}

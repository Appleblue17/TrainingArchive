#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=3e5+5;
int n,mod,ans;

int ksm(int a,int x){
    int tot=1;
    while(x){
        if(x & 1) tot=1ll*tot*a%mod;
        a=1ll*a*a%mod;
        x>>=1;
    }
    return tot;
}

int d[N],id[N];
void init(int lim){
    for(int i=1;i<=lim;i++){
        for(int j=i;j<=lim;j+=i){
            d[j]++;
        }
    }
    for(int i=1;i<=lim;i++){
        id[i]=ksm(d[i]-1,mod-2);
    }
}

int f[N],g[N],s[N];
signed main(){
    cin>>n>>mod;
    init(N-5);
    
    for(int t=n;t>=2;t--){
        int m=n/t;
        
        for(int i=1;i<=m;i++) f[i]=0;
        f[1]=1;
        for(int i=1;i<=m;i++){
            if(i>1) f[i]=f[i]*id[i*t]%mod;
            for(int j=i*2;j<=m;j+=i){
                f[j]=(f[j]+f[i])%mod;
            }
            s[t]=(s[t]+f[i])%mod;
        }
        
        g[t]=s[t]*s[t]%mod;
        for(int k=2;k<=n/t;k++){
            g[t]=(g[t]+mod-f[k]*f[k]%mod*g[t*k]%mod)%mod;
        }
        
        int s1=s[t],s2=0;
        for(int r=1;r<=n/t;r++){
            s2=(s2+f[r]*(g[t*r]+mod-1)%mod)%mod;
        }
        int tot=(s1*(n-1)%mod+mod-s2)%mod;
        ans=(ans+tot)%mod;
    }
    cout<<ans*2%mod;
}

#include "bits/stdc++.h"
using namespace std;
#define int long long
const int N=1e6+5,M=40,mod=1e9+7;
int T,n;

int ksm(int a,int x){
    int tot=1;
    while(x){
        if(x & 1) tot=tot*a%mod;
        a=a*a%mod;
        x>>=1;
    }
    return tot;
}

int pw[M];

int sz[M],pos[M];

signed main(){
    pw[0]=1;
    for(int i=1;i<M;i++) pw[i]=pw[i-1]*2%mod;
    
    cin>>T;
    while(T--){
        cin>>n;
        int k=0;
        
        while((1<<(k+1))<=n) k++;
        
        sz[k]=1; pos[k]=n;
        for(int t=k-1;t>=0;t--){
            pos[t]=pos[t+1]/2;
            int d=k-t-1+(pos[t+1]%2);
            sz[t]=(sz[t+1]+pw[d])%mod;
        }
        
        // for(int i=0;i<=k;i++) cout<<pos[i]<<" "; cout<<endl;
        // for(int i=0;i<=k;i++) cout<<sz[i]<<" "; cout<<endl;
        
        int ans=0,prod=1;
        
        for(int t=k;t>=0;t--){
            int tot=sz[t];
            for(int j=0;j<=t-1;j++){
                tot=tot*sz[j]%mod*ksm((sz[j]+mod-sz[t])%mod,mod-2)%mod;
            }
            prod=prod*sz[t]%mod;
            // cout<<t<<": "<<sz[t]<<" "<<pos[t]<<"   "<<tot<<endl;
            ans=(ans+tot)%mod;
            
            if(t<k){
                int d=k-t-1+(pos[t+1]%2);
                for(int i=0;i<d;i++){
                    int num=pw[i],siz=(pw[d-i]+mod-1)%mod;
                    int tot=siz;
                    for(int j=0;j<=t;j++){
                        tot=tot*sz[j]%mod*ksm((sz[j]+mod-siz)%mod,mod-2)%mod;
                    }
                    for(int j=0;j<i;j++){
                        tot=tot*(pw[d-j]+mod-1)%mod*ksm((pw[d-j]+mod-pw[d-i])%mod,mod-2)%mod;
                    }
                    prod=prod*ksm(siz,num)%mod;
                    ans=(ans+tot*num%mod)%mod;
                    // cout<<" *"<<num<<" "<<siz<<" "<<tot<<endl;
                }
            }
        }
        
        // cout<<prod<<" "<<ans<<endl;
        // int mul=1;
        // for(int i=1;i<n;i++) mul=mul*i%mod;
        // cout<<ans*mul%mod*ksm(prod,mod-2)%mod<<endl;
        
        cout<<ans*ksm(n,mod-2)%mod*ksm(prod,mod-2)%mod<<endl;
        // cout<<55555556ll*n%mod*mul%mod*prod%mod<<endl;
    }
}


#pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=2200,mod=1e9+7;

char S[N];
int n,a[N];
int p[N],id;

int f[N],g[N],h[N],dp[N];
void gmod(int &x){
    x%=mod;
}

signed main(){
    scanf("%s",S+1);
    n=strlen(S+1);
    for(int i=1;i<=n;i++){
        a[i]=S[i]-'A';
        a[i]=(a[i]+4-(i-1)%4)%4;
        // cout<<a[i]<<" ";
    }
    // cout<<endl;
    
    for(int i=1;i<=n;i++){
        int x=a[i];
        if(id>=3 && p[id]==x && p[id-1]==x && p[id-2]==x){
            id-=3;
        }
        else p[++id]=x;
    }
    
    // cout<<id<<endl;
    // for(int i=1;i<=id;i++) cout<<p[i]<<" ";
    // cout<<endl;
    
    int lim=(n-id)/4;
    h[0]=f[0]=1;
    for(int k=1;k<=lim;k++){
        for(int i=0;i<=k-1;i++){
            for(int j=0;i+j<=k-1;j++){
                gmod(g[k]+=h[i]*h[j]%mod*h[k-1-i-j]%mod);
            }
        }
        for(int t=1;t<=k;t++){
            gmod(h[k]+=3*g[t]%mod*h[k-t]%mod);
            gmod(f[k]+=4*g[t]%mod*f[k-t]%mod);
        }
    }
    // for(int k=0;k<=lim;k++) cout<<g[k]<<" ";
    // cout<<endl;
    // for(int k=0;k<=lim;k++) cout<<h[k]<<" ";
    // cout<<endl;
    
    // for(int k=0;k<=lim;k++) cout<<f[k]<<" ";
    // cout<<endl;
    
    for(int i=0;i<=lim;i++) dp[i]=f[i];
    for(int t=1;t<=id;t++){
        for(int i=lim;i>=0;i--){
            for(int j=1;i+j<=lim;j++){
                gmod(dp[i+j]+=dp[i]*h[j]%mod);
            }
        }
    }
    // for(int i=0;i<=lim;i++) cout<<dp[i]<<" ";
    // cout<<endl;
    cout<<dp[lim];
    
}

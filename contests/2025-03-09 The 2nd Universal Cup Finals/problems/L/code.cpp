#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=550,mod=1e9+7;

int n,p[N],ip[N],q[N];
int r[N],ir[N],id;

int w[N][N];
int f[N][N],g[N][N],h[N][N];

void gmod(int &x){
    x%=mod;
}

signed main(){
    scanf("%lld",&n);
    for(int i=1;i<=n;i++) scanf("%lld",&p[i]),ip[p[i]]=i;
    for(int i=1;i<=n;i++) scanf("%lld",&q[p[i]]);

    int x=1;
    do{
        r[++id]=x;
        x=q[x];
    }while(x!=1);
    if(id<n) return puts("0"),0;
    // for(int i=1;i<=n;i++) cout<<r[i]<<" ";
    // cout<<endl;
    for(int i=1;i<=n;i++) ir[r[i]]=i;

    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            scanf("%lld",&w[ir[p[i]]][ir[p[j]]]);
    
    for(int i=1;i<=n;i++) f[i][i]=g[i][i]=h[i][i]=1;
    for(int k=2;k<=n;k++){
        for(int l=1;l+k-1<=n;l++){
            int r=l+k-1;
            // h[l][r]=g[l+1][r];
            h[l][r]=f[l][r-1];
            for(int t=l+1;t<r;t++) gmod(h[l][r]+=w[t][r]*h[l][t]%mod*h[t][r]%mod);
            
            for(int t=l+1;t<=r;t++) gmod(f[l][r]+=w[l][t]*h[l][t]%mod*f[t][r]%mod);
            for(int t=l;t<r;t++) gmod(g[l][r]+=w[t][r]*g[l][t]%mod*h[t][r]%mod);
            
            // cout<<l<<" "<<r<<": "<<f[l][r]<<" "<<g[l][r]<<" "<<h[l][r]<<endl;
            assert(f[l][r]==g[l][r] && f[l][r]>=0);
        }
    }
    
    cout<<g[1][n];
}

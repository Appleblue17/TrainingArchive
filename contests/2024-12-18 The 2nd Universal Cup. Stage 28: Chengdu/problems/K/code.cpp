#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=3300,mod=998244353,INF=1e9;
int n,m,ans;
char S[N][N];

int f[N][N],g[N][N];
void gmod(int &x){
    x%=mod;
}

int mx[N],mn[N];
int S2(int x){
    return x*(x+1)/2;
}

signed main(){
    scanf("%lld",&n); m=n;
    for(int i=1;i<=n;i++) scanf("\n%s",S[i]+1);
    for(int i=1;i<=n;i++) mx[i]=0,mn[i]=INF;
    
    f[0][0]=1;
    for(int t=0;t<m;t++){
        for(int i=1;i<=n;i++){
            if(S[i][t]=='1') mx[i]=max(mx[i],t);
            if(S[i][t]=='0') mn[i]=min(mn[i],t);
        }
        
        int MX=0,MN=n+1;
        for(int i=0;i<=n;i++){
            if(S[i][t+1]=='1') MX=max(MX,i);
            if(S[i][t+1]=='0') MN=min(MN,i);
            int L=MX,R=min(i,MN-1);
            if(L<=R){
                gmod(f[t+1][i]+=1ll*f[t][i]*(R-L+1)%mod);
                gmod(g[t+1][i]+=1ll*g[t][i]*(R-L+1)%mod);
                gmod(g[t+1][i]+=1ll*f[t][i]*(S2(R)-S2(L-1))%mod);
            }
        }
        
        for(int i=1;i<=n;i++){
            int L=mx[i],R=min(t,mn[i]-1);
            if(L<=R){
                gmod(f[t][i]+=f[t][i-1]*(R-L+1)%mod);
                gmod(g[t][i]+=g[t][i-1]*(R-L+1)%mod);
                gmod(g[t][i]+=f[t][i-1]*(S2(R)-S2(L-1))%mod);
            }
        }
        
        for(int i=1;i<MN;i++){
            if(t){
                int L=mx[i],R=min(t-1,mn[i]-1);
                
                if(L<=R){
                    gmod(f[t+1][i]+=f[t][i-1]*(R-L+1)%mod);
                    gmod(g[t+1][i]+=g[t][i-1]*(R-L+1)%mod);
                    gmod(g[t+1][i]+=f[t][i-1]*(S2(R)-S2(L-1))%mod);
                    gmod(g[t+1][i]+=f[t][i-1]*(R-L+1)%mod*i%mod);
                }
            }
        }
    }
    
    for(int i=1;i<=n;i++){
        if(S[i][m]=='1') mx[i]=max(mx[i],m);
        if(S[i][m]=='0') mn[i]=min(mn[i],m);
    }
    for(int i=1;i<=n;i++){
        int L=mx[i],R=min(m,mn[i]-1);
        if(L<=R){
            gmod(f[m][i]+=f[m][i-1]*(R-L+1)%mod);
            gmod(g[m][i]+=g[m][i-1]*(R-L+1)%mod);
            gmod(g[m][i]+=f[m][i-1]*(S2(R)-S2(L-1))%mod);   
        }
    }
    
    cout<<f[m][n];
    
}

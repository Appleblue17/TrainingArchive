// #pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=22,mod=998244353;

int ksm(int a,int x){
    int tot=1;
    while(x){
        if(x & 1ll) tot=tot*a%mod;
        a=a*a%mod;
        x>>=1ll;
    }
    return tot;
}

int mul[N];

int n,ans;
int p[N],q[N],ip[N],iq[N],c[N][N];
int f[N],g[N],F[N],G[N];

void gmod(int &x){
    x%=mod;
}

int solve(){
    for(int i=1;i<n;i++){
        if((F[i] & F[i+1])!=F[i]) return 0;
    }
    for(int i=1;i<n;i++){
        if((G[i] & G[i+1])!=G[i]) return 0;
    }
    int tot=1;
    for(int l=1,r;l<=n;l=r+1){
        r=l;
        while(r+1<=n && F[r+1]==F[l]) r++;
        tot=tot*mul[r-l+1]%mod;
    }
    
    for(int l=1,r;l<=n;l=r+1){
        r=l;
        while(r+1<=n && G[r+1]==G[l]) r++;
        tot=tot*mul[r-l+1]%mod;
    }
    return tot;
}

signed main() {
    cin>>n;
    mul[0]=1;
    for(int i=1;i<=n;i++) mul[i]=mul[i-1]*i%mod;
    
    for(int i=0;i<n;i++){
        cin>>p[i];
        p[i]--;
        ip[p[i]]=i;
    }
    for(int i=0;i<n;i++){
        cin>>q[i];
        q[i]--;
        iq[q[i]]=i;
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>c[i][j]; c[i][j]--;
            if(c[i][j]!=p[i] && c[i][j]!=q[j]){
                puts("0");
                return 0;
            }
            if(p[i]!=q[j]){
                if(c[i][j]==p[i]) f[i] |= 1<<j;
                else g[j] |= 1<<i;
            }
        }
    }
    // for(int i=0;i<n;i++) cout<<f[i]<<" "; cout<<" ";
    // for(int i=0;i<n;i++) cout<<g[i]<<" "; cout<<" ";
    // cout<<endl;
    
    for(int mac=0;mac<(1<<n);mac++){
        for(int i=0;i<n;i++) F[i]=f[i],G[i]=g[i];
        for(int i=0;i<n;i++){
            int x=ip[i],y=iq[i];
            F[x]=f[x];
            G[y]=g[y];
            if(mac>>i & 1) F[x] |= 1<<y;
            else G[y] |= 1<<x;
        }
        sort(F,F+n);
        sort(G,G+n);
        
        for(int i=n;i>=1;i--) F[i]=F[i-1],G[i]=G[i-1];
        F[0]=G[0]=0;
        
        // cout<<mac<<": ";
        // for(int i=1;i<=n;i++) cout<<F[i]<<" "; cout<<" ";
        // for(int i=1;i<=n;i++) cout<<G[i]<<" "; cout<<" ";
        // cout<<endl;
        
        int ret=solve();
        // cout<<ret<<endl;
        gmod(ans+=ret);
    }
    cout<<ans;
}

// #pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+5,M=2200,mod=1e9+7,inv2=(mod+1)/2;

int ksm(int a,int x){
    int tot=1;
    while(x){
        if(x & 1ll) tot=tot*a%mod;
        a=a*a%mod;
        x>>=1ll;
    }
    return tot;
}
int mul[N],inv[N];
void init(int lim){
    mul[0]=inv[0]=1;
    for(int i=1;i<=lim;i++) mul[i]=mul[i-1]*i%mod;
    inv[lim]=ksm(mul[lim],mod-2);
    for(int i=lim-1;i>=1;i--) inv[i]=inv[i+1]*(i+1)%mod;
}
int C(int m,int n){
    if(n<0 || m<0 || m<n) return 0;
    return mul[m]*inv[n]%mod*inv[m-n]%mod;
}
int CC(int m,int n){
    if(n<0 || m<0 || m<n) return 0;
    int tmp=inv[n];
    for(int j=m;j>=m-n+1;j--) tmp=tmp*j%mod;
    return tmp;
}

void gmod(int &x){
    x%=mod;
}


int n,m,K,ans;
int pre[M][M];
int f[N],g[N];

int S(int n,int m){
    int tot=0;
    for(int i=0;i<=n/2;i++){
        // gmod(tot+=CC(m,i)*CC(m-i,n-2*i)%mod*mul[n]%mod*ksm(inv2,i)%mod);
        gmod(tot+=pre[K-m][i]*pre[K-m+i][n-2*i]%mod*mul[n]%mod*ksm(inv2,i)%mod);
    }
    return tot;
}

signed main(){
    // freopen("1.txt","w",stdout);
    init(N-5);
    cin>>n>>m>>K;
    
    for(int i=0;i<=m;i++){
        pre[i][0]=1;
        for(int j=1;j<=m;j++){
            pre[i][j]=pre[i][j-1]*(K-i-j+1)%mod;
        }
        for(int j=1;j<=m;j++){
            pre[i][j]=pre[i][j]*inv[j]%mod;
        }
    }
    
    g[1]=S(m,K)*(n-m+1)%mod*ksm(K,n-m)%mod;
    for(int t=1;t<=m/2;t++){
        int val=S(m-2*t,K-t)*pre[0][t]%mod*mul[t]%mod;
        
        for(int k=2;k<=n;k++){
            int len=k*m-(k-1)*t;
            if(len>n) break;
            gmod(g[k]+=(n-len+1)*ksm(K,n-len)%mod*val%mod);
        }
    }
    
    int S=0,SS=0;
    for(int k=n;k>=1;k--){
        int tot=0;
        // for(int i=k+1;i<=n;i++) gmod(tot+=f[i]*(i-k+1)%mod);
        tot=(SS+mod-k*S%mod)%mod;
        f[k]=(g[k]+mod-tot)%mod;
        gmod(S+=f[k]);
        gmod(SS+=f[k]*(k+1)%mod);
    }
    
    for(int i=1;i<=n;i++) gmod(ans+=f[i]*((i+1)/2)%mod);
    cout<<ans;
}

#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=6600,mod=998244353;

int ksm(int a,int x){
    int tot=1;
    while(x){
        if(x & 1ll) tot=tot*a%mod;
        a=a*a%mod;
        x>>=1ll;
    }
    return tot;
}

int mul[N],inv[N],pw2[N];
void init(int lim){
    mul[0]=inv[0]=1;
    for(int i=1;i<=lim;i++) mul[i]=mul[i-1]*i%mod;
    inv[lim]=ksm(mul[lim],mod-2);
    for(int i=lim-1;i>=1;i--) inv[i]=inv[i+1]*(i+1)%mod;
    
    pw2[0]=1;
    for(int i=1;i<=lim;i++) pw2[i]=pw2[i-1]*2%mod;
}
int C(int m,int n){
    if(m<0 || n<0 || m<n) return 0;
    return mul[m]*inv[n]%mod*inv[m-n]%mod;
}
void gmod(int &x){
    x%=mod;
}

int n,ans;
char S[N];
int s[N];

int A[N],B[N];

int f[N][N],g[N][N];

signed main(){
    init(N-5);
    
    scanf("%lld",&n);
    scanf("\n%s",S+1);
    bool flag=1;
    for(int i=1;i<=n*2;i++){
        A[i]=A[i-1];
        B[i]=B[i-1];
        if(S[i]=='('){
            s[i]=s[i-1]+1;
            A[i]++;
        }
        else{
            s[i]=s[i-1]-1;
            B[i]++;
        }
        if(s[i]<0) flag=0;
    }
    if(flag){
        cout<<(pw2[n*2]+mod-1)%mod;
        return 0;
    }
    
    f[0][0]=1;
    for(int i=1;i<=n*2;i++){
        for(int j=0;j<=n;j++){
            if(!f[i-1][j]) continue;
            gmod(f[i][j]+=f[i-1][j]);
            if(S[i]==')') gmod(f[i][j+1]+=f[i-1][j]);
        }
        for(int j=0;2*j<(-s[i]);j++) f[i][j]=0;
    }
    
    g[n*2+1][0]=1;
    for(int i=n*2;i>=1;i--){
        for(int j=0;j<=n;j++){
            if(!g[i+1][j]) continue;
            gmod(g[i][j]+=g[i+1][j]);
            if(S[i]=='(') gmod(g[i][j+1]+=g[i+1][j]);
        }
        for(int j=0;2*j<(-s[i-1]);j++) g[i][j]=0;
    }
    
    for(int pos=1;pos<=2*n;pos++){
        for(int k=0;k<=n;k++){
            if(S[pos]=='('){
                gmod(ans+=pw2[n-B[pos]]*pw2[A[pos]-1]%mod*f[pos][k]%mod*g[pos+1][k]%mod);
            }
            else if(k>0){
                gmod(ans+=pw2[n-B[pos]]*pw2[A[pos]]%mod*f[pos-1][k-1]%mod*g[pos+1][k]%mod);
            }
            
        }
    }
    cout<<ans;
}

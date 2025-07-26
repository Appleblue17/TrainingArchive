#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1100,mod=1e9+7;

int ksm(int a,int x){
    int tot=1;
    while(x){
        if(x & 1ll) tot=tot*a%mod;
        a=a*a%mod;
        x>>=1ll;
    }
    return tot;
}

int mul[N],inv[N],S1[N][N];
void init(int lim){
    mul[0]=inv[0]=1;
    for(int i=1;i<=lim;i++) mul[i]=mul[i-1]*i%mod;
    inv[lim]=ksm(mul[lim],mod-2);
    for(int i=lim-1;i>=1;i--) inv[i]=inv[i+1]*(i+1)%mod;
    
    S1[0][0]=1;
    for(int i=1;i<=lim;i++){
        for(int j=1;j<=i;j++) S1[i][j]=((i-1)*S1[i-1][j]%mod+S1[i-1][j-1])%mod;
    }
}
int binom(int m,int n){
    if(m<0 || n<0 || m<n) return 0;
    return mul[m]*inv[n]%mod*inv[m-n]%mod;
}
int cal(int n,int k){
    if(!n && !k) return 1;
    return (binom(2*n+k-1,n)+mod-binom(2*n+k-1,n-1))%mod;
}
int ID(int x){
    return (x & 1ll)?mod-1:1;
}

int A,B,C,K;
int n;

int f[N][N];
int y[N],F[N],G[N];

signed main(){
    init(N-5);
    cin>>A>>B>>C>>K;
    if((A+B+C) & 1ll){
        puts("0");
        return 0;
    }
    n=(A+B+C)/2;
    
    for(int a=0;a<=n;a++){
        for(int t=0;t<=n;t++){
            int tot=0;
            for(int k=0,s=1;k<=a;k++,s=s*t%mod){
                tot=(tot+cal(a-k,k)*inv[k]%mod*s%mod)%mod;
            }
            f[a][t]=tot;
            // cout<<f[a][t]<<" ";
        }
        // cout<<endl;
    }
    
    for(int a=0;a<=n;a++){
        for(int b=0;a+b<=n;b++){
            int c=n-a-b;
            int coef=0;
            for(int i=0;i<=a;i++){
                int j=C-c-a+i;
                int k=i-B+b+c;
                coef=(coef+binom(a,i)*binom(b,j)%mod*binom(c,k)%mod)%mod;
            }
            
            // cout<<a<<" "<<b<<" "<<c<<" "<<coef<<endl;
            for(int t=0;t<=n;t++){
                y[t]=(y[t]+f[a][t]*f[b][t]%mod*f[c][t]%mod*coef%mod)%mod;
            }
        }
    }
    
    // for(int t=0;t<=n;t++) cout<<y[t]<<" ";
    // cout<<endl;
    
    for(int i=0;i<=n;i++){
        for(int j=0;i+j<=n;j++){
            F[i+j]=(F[i+j]+y[i]*inv[i]%mod*inv[j]%mod*ID(j)%mod)%mod;
        }
    }
    for(int i=0;i<=n;i++){
        for(int j=0;j<=i;j++){
            G[j]=(G[j]+F[i]*S1[i][j]%mod*ID(i-j)%mod)%mod;
        }
    }
    for(int i=0;i<=n;i++) G[i]=G[i]*mul[i]%mod;
    // for(int i=0;i<=n;i++) cout<<G[i]*mul[i]%mod<<" ";
    
    int tot=0;
    for(int i=0;i<=n;i++) tot=(tot+G[i]*ksm(i,K)%mod)%mod;
    cout<<tot;
}

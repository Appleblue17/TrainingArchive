#pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;
#define int long long
// #define short int
const int N=1e6+5,M=62,mod=998244353,inv2=(mod+1)/2;

int n,a[N],ans;
char S[N];

int trans(char c){
    if(c>='a' && c<='z') return c-'a';
    if(c>='A' && c<='Z') return c-'A'+26;
    if(c>='0' && c<='9') return c-'0'+52;
}

void gmod(int& x){
    if(x>=mod) x-=mod;
}
int f[N][M],g[M];

int A[M][M],B[M][M];

signed main(){
    scanf("%s",S+1);
    n=strlen(S+1);
    for(int i=1;i<=n;i++) a[i]=trans(S[i]);
    
    for(int i=1;i<=n;i++){
        for(int c=0;c<62;c++) f[i][c]=f[i-1][c];
        f[i][a[i]]++;
    }
    
    for(int i=n;i>=1;i--){
        int s=a[i];
        g[s]++;
        
        int tot=0;
        for(int c=0;c<62;c++) gmod(tot+=f[i-1][c]*f[i-1][c]%mod);
        for(int c=0;c<62;c++){
            if(c==s) continue;
            int h=(g[c]*A[s][c]%mod+mod-B[s][c])%mod;
            
            int x=i-1-f[i-1][s]-f[i-1][c];
            
            int y=(tot+mod-f[i-1][s]*f[i-1][s]%mod+mod-f[i-1][c]*f[i-1][c]%mod)%mod;
            gmod(ans+=(x*x%mod+mod-y)%mod*inv2%mod*h%mod);
        }
        
        for(int c=0;c<62;c++){
            gmod(A[s][c]+=g[c]);
            gmod(B[s][c]+=g[c]*g[c]%mod);
        }
    }
    
    cout<<ans;
}

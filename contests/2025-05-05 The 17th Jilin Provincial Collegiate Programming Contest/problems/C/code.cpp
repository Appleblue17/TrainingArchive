#pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e7+5,mod=1e9+7,inv2=(mod+1)/2;
int n;
int pw2[N];
char S[N];

struct abc{
    int A,B;
}F[N],G[N],ANS;
abc P={inv2,inv2},Q={inv2+1,inv2};
abc operator +(abc X,abc Y){
    return (abc){(X.A+Y.A)%mod,(X.B+Y.B)%mod};
}
abc operator *(abc X,abc Y){
    return (abc){(X.A*Y.A%mod+X.B*Y.B%mod*5%mod)%mod,(X.A*Y.B%mod+X.B*Y.A%mod)%mod};
}

mt19937 rng(time(NULL));
signed main() {
    scanf("%s",S+1);
    n=strlen(S+1);
    // n=10000000;
    // for(int i=1;i<=n;i++) S[i]=rng()%2+'0';
    for(int i=1;i<=n/2;i++) swap(S[i],S[n+1-i]);
    
    pw2[0]=1;
    for(int i=1;i<=n;i++) pw2[i]=pw2[i-1]*2%mod;
    F[0]=G[0]={1,0};
    for(int i=1;i<=n;i++){
        F[i]=F[i-1]*P;
        G[i]=G[i-1]*Q;
    }
    
    int c=0;
    for(int i=n;i>=1;i--){
        if(S[i]=='1'){
            ANS = ANS + F[c]*G[i-1];
            // cout<<c<<" "<<i-1<<": "<<(F[c]*G[i-1]).A<<" "<<(F[c]*G[i-1]).B<<endl;
            c++;
        }
    }
    ANS = ANS + F[c];
    
    cout<<ANS.B*2%mod;
}

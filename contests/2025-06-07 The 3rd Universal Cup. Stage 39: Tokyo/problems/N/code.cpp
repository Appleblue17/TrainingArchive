#include "bits/stdc++.h"
using namespace std;
const int N=1e5+5;
int n,k;
char S[N];
vector <int> V[N],P[N],Q;

int inv(int x){
    return x;
}

void ins(vector<int> X){
    for(int l=0;l<=k;l++){
        if(!X[l]) continue;
        if(!V[l].size()){
            V[l]=X;
            return ;
        }
        int w=X[l]*inv(V[l][l])%3;
        for(int i=l;i<=k;i++){
            X[i]=(X[i]+3-V[l][i]*w%3)%3;
        }
    }
}
bool check(vector<int> X){
    for(int l=0;l<=k;l++){
        if(!X[l]) continue;
        if(!V[l].size()){
            return 0;
        }
        int w=X[l]*inv(V[l][l])%3;
        for(int i=l;i<=k;i++){
            X[i]=(X[i]+3-V[l][i]*w%3)%3;
        }
    }
    return 1;
}

signed main(){
    scanf("%d%d",&n,&k);
    
    for(int t=1;t<=n;t++){
        P[t].resize(k+1);
    }
    for(int t=1;t<=n;t++){
        scanf("\n%s",S+1);
        
        P[t][0]=1;
        for(int i=1;i<=k;i++){
            if(S[i]=='R') P[t][i]=0;
            else if(S[i]=='G') P[t][i]=1;
            else P[t][i]=2;
        }
    }
    
    Q.resize(k+1);
    for(int i=0;i<=k;i++) Q[i]=0;
    for(int t=1;t<=n;t++){
        for(int i=0;i<=k;i++) Q[i]=(Q[i]+3-P[t][i])%3;
    }
    
    for(int t=0;t<=n;t++){
        if(check(Q)){
            cout<<t;
            return 0;
        }
        ins(P[t+1]);
        for(int i=0;i<=k;i++) Q[i]=(Q[i]+P[t+1][i])%3;
    }
    
    
}

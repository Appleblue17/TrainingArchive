#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e7+5,mod=998244353;
char S[11];
int p[11],id,q,ans;

int ksm(int a,int x){
    int tot=1;
    while(x){
        if(x & 1) tot=1ll*tot*a%mod;
        a=1ll*a*a%mod;
        x>>=1;
    }
    return tot;
}


bool ispr[N];
void init(int lim){
    for(int i=2;i<=lim;i++) ispr[i]=1;
    for(int i=2;i<=lim;i++){
        if(!ispr[i]) continue;
        for(int j=i*2;j<=lim;j+=i) ispr[j]=0;
    }
    ispr[0]=ispr[1]=1;
}

void dfs(int dep,int prob,int x){
    bool fl;
    if(x>N-5){
        fl=1;
        for(int i=2;1ll*i*i<=x;i++){
            if(x%i==0){
                fl=0;
                break;
            }
        }
    }
    else fl=ispr[x];
    
    if(!fl){
        ans=(ans+1ll*prob*dep%mod)%mod;
        return ;
    }
    for(int i=1;i<=id;i++){
        dfs(dep+1,1ll*prob*q%mod,x*10+p[i]);
    }
}

signed main(){
    init(N-5);
    scanf("%s",&S);
    for(int i=0;i<9;i++){
        if(S[i]=='1') p[++id]=i+1;
    }
    q=ksm(id,mod-2);
    
    dfs(0,1,0);
    cout<<ans;
}

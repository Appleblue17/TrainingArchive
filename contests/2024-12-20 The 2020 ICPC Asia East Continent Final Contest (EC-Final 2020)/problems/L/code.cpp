#include <bits/stdc++.h>
using namespace std;
const int N=1e6+5,mod=1e9+7;

int n,ans=1;
bool vis[N];
vector <int> D[N];
int a[N];

vector <int> V[N];

int ksm(int a,int x){
    int tot=1;
    while(x){
        if(x & 1ll) tot=1ll*tot*a%mod;
        a=1ll*a*a%mod;
        x>>=1ll;
    }
    return tot;
}

int main(){
    scanf("%d",&n);
    
    int lim=N-5;
    for(int i=2;i<=lim;i++){
        if(D[i].size()) continue;
        for(int j=i;j<=lim;j+=i) D[j].push_back(i);
    }
    
    for(int i=1;i<=n;i++){
        int x; scanf("%d",&x);
        
        int y=x;
        for(int t: D[x]){
            int c=0;
            while(y%t==0) y/=t,c++;
            if(c%2==1) V[t].push_back(i);
        }
    }
    
    for(int t=1;t<=lim;t++){
        if(!V[t].size()) continue;
        ans=1ll*ans*ksm(t,min(V[t].size(),n-V[t].size()))%mod;
    }
    cout<<ans;
    
}

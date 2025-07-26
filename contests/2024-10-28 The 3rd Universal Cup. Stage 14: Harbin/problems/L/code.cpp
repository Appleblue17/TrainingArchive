#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+5,mod=998244353,inv2=(mod+1)/2;
int T,n;
vector <int> G[N];

void gmod(int &x){
    x%=mod;
}
int ksm(int a,int x){
    int tot=1;
    while(x){
        if(x & 1ll) tot=tot*a%mod;
        a=a*a%mod;
        x>>=1ll;
    }
    return tot;
}

int siz[N],siz2[N];
void dfs(int u,int fa){
    siz[u]=1;
    siz2[u]=0;
    for(int v: G[u]){
        if(v==fa) continue;
        dfs(v,u);
        siz[u]+=siz[v];
        gmod(siz2[u]+=siz2[v]);
    }
    gmod(siz2[u]+=siz[u]*siz[u]%mod);
}

int alc,ans;
void dfss(int u,int fa){
    int sum=0,sum2=0;
    for(int v: G[u]){
        if(v==fa) continue;
        dfss(v,u);
        gmod(sum+=siz2[v]);
        gmod(sum2+=siz2[v]*siz2[v]%mod);
        
        int tmp=(n-siz[v])*siz[v]%mod;
    	gmod(alc+=tmp*tmp%mod);
    }
    gmod(ans+=(n-siz[u])*(n-siz[u])%mod*(siz2[u]+mod-siz[u]*siz[u]%mod)%mod);
    gmod(ans+=(sum*sum%mod+mod-sum2)%mod*inv2%mod);
}


signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++) G[i].clear();
        alc=ans=0;
        
        for(int i=1;i<n;i++){
            int u,v; cin>>u>>v;
            G[u].push_back(v);
            G[v].push_back(u);
        }
        dfs(1,0);
        dfss(1,0);
        
        int tot=n*(n-1)/2%mod;
//        cout<<" "<<alc<<" "<<ans<<endl;
        int anss=(alc+ans*2%mod)%mod;
//        cout<<" "<<anss<<" "<<anss*ksm(tot*tot%mod,mod-2)%mod<<endl;
		cout<<anss*ksm(tot*tot%mod,mod-2)%mod<<endl;
    }
    
    
    
}

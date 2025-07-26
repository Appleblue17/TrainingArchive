#pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=22,M=1.1e6+5,mod=1e9+7;
int T,n1,n2,m,k;

int G[N];
int must;

bool vis[N];
int dfs_mac;
void dfs(int u){
    vis[u]=1;
    dfs_mac |= 1<<u;
    for(int v=0;v<m;v++){
        if((G[u]>>v & 1) && !vis[v]){
            dfs(v);
        }
    }
}

int f[M],g[N][M];
int dp[N][N],h[N][N],tmp[N][N];


int ksm(int a,int x){
    int tot=1;
    while(x){
        if(x & 1) tot=tot*a%mod;
        a=a*a%mod;
        x>>=1;
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
int ID(int x){
    return (x & 1)?mod-1:1;
}
int cal(int n,int m){
    // C(n-1,m-1)
    if(n<m) return 0;
    int tot=1;
    for(int i=n-1;i>n-m;i--) tot=tot*i%mod;
    return tot*inv[m-1]%mod;
}

signed main(){
    // freopen("1.txt","r",stdin);
    init(N-1);
    
    cin>>T;
    while(T--){
        cin>>n1>>n2>>m>>k;
        must=0;
        memset(G,0,sizeof(G));
        memset(vis,0,sizeof(vis));
        for(int mac=0;mac<(1<<m);mac++) f[mac]=0;
        for(int i=0;i<=m;i++){
            for(int mac=0;mac<(1<<m);mac++) g[i][mac]=0;
        }
        
        int nw=0;
        dp[0][0]=1;
        
        for(int i=1;i<=k;i++){
            int u,v; scanf("%lld%lld",&u,&v);
            u--,v--;
            if(u==v) must |= 1<<u;
            else{
                G[u] |= 1<<v;
                G[v] |= 1<<u;
            }
        }
        
        for(int mac=0;mac<(1<<m);mac++){
            if(mac & must) continue;
            bool fl=1;
            for(int i=0;i<m && fl;i++){
                if((mac>>i & 1) && (G[i] & mac)) fl=0;
            }
            f[mac]=g[__builtin_popcount(mac)][mac]=fl;
        }
        
        for(int t=0;t<=m;t++){
            for(int i=0;i<m;i++){
                for(int mac=0;mac<(1<<m);mac++){
                    if(!(mac>>i & 1)) g[t][mac | (1<<i)]+=g[t][mac];
                }
            }
        }
        
        for(int u=0;u<m;u++){
            if(vis[u]) continue;
            dfs_mac=0;
            dfs(u);
            
            // cout<<u<<": "<<dfs_mac<<endl;
            
            int num=__builtin_popcount(dfs_mac);
            
            for(int i=0;i<=num+nw;i++)
                for(int j=0;j<=num+nw;j++)
                    tmp[i][j]=h[i][j]=0;
            if(!(dfs_mac & must) && num==1) tmp[0][0]=1;
            
            for(int mac=dfs_mac;;mac=(mac-1) & dfs_mac){
                if(f[mac]){
                    int imac=dfs_mac^mac;
                    int mac_count=__builtin_popcount(mac);
                    for(int j=0;j<=num;j++){
                        tmp[num-j][num-mac_count]+=g[j][imac];
                    }
                }
                
                
                if(!mac) break;
            }
            
            // for(int i=0;i<=num;i++){
            //     for(int j=0;j<=num;j++)
            //         cout<<tmp[i][j]<<" ";
            //     cout<<endl;
            // }
            
            for(int x=0;x<=nw;x++){
                for(int y=0;y<=nw;y++){
                    if(!dp[x][y]) continue;
                    for(int i=0;i<=num;i++){
                        for(int j=0;j<=num;j++){
                            if(!tmp[i][j]) continue;
                            h[x+i][y+j]=(h[x+i][y+j]+dp[x][y]*tmp[i][j]%mod)%mod;
                        }
                    }
                }
            }
            nw+=num;
            swap(h,dp);
        }
        
        // cout<<"final: "<<endl;
        // for(int i=0;i<=m;i++){
        //     for(int j=0;j<=m;j++)
        //         cout<<dp[i][j]<<" ";
        //     cout<<endl;
        // }
        // cout<<endl;
        
        int ans=0;
        for(int i=1;i<=m;i++){
            for(int j=1;j<=m;j++){
                ans=(ans+dp[i][j]*cal(n1,i)%mod*cal(n2,j)%mod)%mod;
                // if(dp[i][j]) cout<<i<<" "<<j<<"  "<<dp[i][j]<<" "<<cal(n1,i)<<" "<<cal(n2,j)<<endl;
            }
        }
        printf("%lld\n",ans);
    }
}

#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+5,mod=1e9+7;

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

int T,n,a[N],b[N],w[N],c[N],ans[N];

vector <int> iG[N];

int dfn[N],low[N],id;
bool vis[N];
stack <int> st;
vector <int> tmp;
int pat[N],pid;
void dfs(int u){
    low[u]=dfn[u]=++id;
    vis[u]=1;
    st.push(u);
    
    int v=b[u];
    if(!dfn[v]){
        dfs(v);
        low[u]=min(low[u],low[v]);
    }
    else if(vis[v]) low[u]=min(low[u],dfn[v]);
    
    if(dfn[u]==low[u]){
        tmp.clear();
        while(st.size()){
            int x=st.top();
            vis[x]=0;
            tmp.push_back(x);
            st.pop();
            if(x==u) break;
        }
        if(tmp.size()>1 || b[u]==u){
            for(int x: tmp) pat[++pid]=x;
        }
    }
}


void dfss(int u,int ban,int d){
    // cout<<"  "<<u<<": "<<d;
    if(c[u]==1) ans[u]=1,d=2;
    else if(c[u]==2) d=-1;
    else if(d!=-1) ans[u]=inv[d],d++;
    // cout<<" "<<ans[u]<<endl;
    
    for(int v: iG[u]){
        if(v==ban) continue;
        dfss(v,ban,d);
    }
}

signed main(){
    // freopen("1.txt","r",stdin);
    // freopen("2.txt","w",stdout);
    init(N-5);
    
    cin>>T;
    while(T--){
        scanf("%lld",&n);
        for(int i=1;i<=n;i++) iG[i].clear();
        for(int i=1;i<=n;i++) vis[i]=dfn[i]=ans[i]=0;
        while(st.size()) st.pop();
        
        for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
        for(int i=1;i<=n;i++){
            scanf("%lld",&b[i]);
            iG[b[i]].push_back(i);
        }
        for(int i=1;i<=n;i++) scanf("%lld",&w[i]);
        
        for(int u=1;u<=n;u++){
            int v=b[u];
            if(a[u]<a[v]) c[u]=1,ans[u]=1;
            else if(a[u]>=a[v]+w[v]) c[u]=2;
            else c[u]=3;
            // cout<<c[u]<<" ";
        }
        // cout<<endl;
        
        id=0;
        for(int u=1;u<=n;u++){
            if(dfn[u]) continue;
            pid=0;
            dfs(u);
            if(!pid) continue;
            // cout<<u<<": ";
            // for(int i=1;i<=pid;i++) cout<<pat[i]<<" ";
            // cout<<endl;
            
            int st=0;
            for(int i=1;i<=pid;i++){
                int x=pat[i];
                if(c[x]!=3) st=i;
            }
            if(st){
                int d=0;
                int nw=st;
                do{
                    int x=pat[nw],nxt=nw%pid+1;
                    
                    if(c[x]==1) d=1;
                    else if(c[x]==2) d=-1;
                    else if(d!=-1) d++;
                    // cout<<"dfs "<<x<<" "<<d<<endl;
                    dfss(x,pat[nxt],d);
                    
                    nw=nxt;
                }while(nw!=st);
            }
            else{
                for(int i=1;i<=pid;i++){
                    int x=pat[i],nxt=i%pid+1;
                    // cout<<"dfs "<<x<<" "<<-1<<endl;
                    dfss(x,pat[nxt],-1);
                }
            }
        }
        
        // for(int i=1;i<=n;i++) cout<<ans[i]<<" ";
        // cout<<endl;
        for(int i=1;i<=n;i++)
            printf("%lld ",(a[i]+ans[i]*w[i]%mod)%mod);
        putchar('\n');
    }
    
    
}

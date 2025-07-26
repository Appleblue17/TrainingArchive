#include <bits/stdc++.h>
using namespace std;
const int N=1e5+5,M=2e5+5;

struct nod{
    int to,nxt,w;
}e[M*2];
int head[N],cnt;
void add(int u,int v,int w){
    e[++cnt]=(nod){v,head[u],w};
    head[u]=cnt;
}

int dfn[N],low[N],id;
bool vis[N];
stack <int> st;

bool cut[M];

void dfs(int u,int fa){
	low[u]=dfn[u]=++id;
	vis[u]=1;
	st.push(u);
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to,w=e[i].w;
		if(w==fa) continue;
		if(!dfn[v]){
			dfs(v,w);
			low[u]=min(low[u],low[v]);
			if(low[v]>dfn[u]) cut[w]=1;
		}
		else if(vis[v]) low[u]=min(low[u],dfn[v]);
	}
	if(dfn[u]==low[u]){
		while(st.size()){
			int tmp=st.top();
			vis[tmp]=0;
			st.pop();
			if(tmp==u) break;
		}
	}
}

vector <int> G[N];
bool viss[N];
int col[N],siz[N],cid;
void dfss(int u){
    viss[u]=1;
    col[u]=cid;
    siz[cid]++;
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to,w=e[i].w;
        if(viss[v] || cut[w]) continue;
        dfss(v);
    }
}

int T,n,m;

int buc[N],p[N],pid,sum[N];
int mp1[N],mp2[N];
int f[N],g[N],recf[N],recg[N];

int top,pos,stl,str;
int tmp[N];
void dfs1(int u,int fa){
    int tot1=0,tot2=pid+1;
    
    for(int v: G[u]){
        if(v==fa) continue;
        dfs1(v,u);
        if(f[v]>tot1) tot1=f[v],recf[u]=v;
        if(g[v]<tot2) tot2=g[v],recg[u]=v;
        siz[u]+=siz[v];
    }
    
    for(int F=0;F<=1;F++){
        for(int v: G[u]){
            if(v==fa) continue;
            int w=tmp[f[v]+2];
            if(w){
                top=u, pos=f[v]+1;
                stl=v, str=w;
            }
            tmp[g[v]]=v;
        }
        for(int v: G[u]){
            if(v==fa) continue;
            tmp[g[v]]=0;
        }
        reverse(G[u].begin(),G[u].end());
    }
    
    int x=mp1[siz[u]],y=mp2[siz[u]];
    if(x && tot1==x-1) tot1=x;
    if(y && tot2==y+1) tot2=y;
    f[u]=tot1;
    g[u]=tot2;
    
    if(tot1==pid){
        top=u, pos=pid;
        stl=recf[u], str=0;
    }
    else if(tot2==1){
        top=u, pos=1;
        stl=0, str=recg[u];
    }
}

int ans[N];
void dye(int u,int fa,int ban,int col){
    ans[u]=col;
    for(int v: G[u]){
        if(v==fa || v==ban) continue;
        dye(v,u,ban,col);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>m;
        
        for(int i=1;i<=n;i++){
            head[i]=0;
            vis[i]=dfn[i]=low[i]=0;
            viss[i]=col[i]=siz[i]=0;
            mp1[i]=mp2[i]=0;
            buc[i]=0;
            f[i]=g[i]=recf[i]=recg[i]=0;
            ans[i]=0;
            G[i].clear();
        }
        cnt=id=cid=pid=0;
        stl=str=0;
        for(int i=1;i<=m;i++) cut[i]=0;
        
        for(int i=1;i<=m;i++){
            int u,v; cin>>u>>v;
            add(u,v,i);
            add(v,u,i);
        }
        
        dfs(1,0);
        
        for(int i=1;i<=n;i++){
            if(viss[i]) continue;
            cid++;
            dfss(i);
        }
        for(int u=1;u<=n;u++){
            for(int i=head[u];i;i=e[i].nxt){
                int v=e[i].to,w=e[i].w;
                if(cut[w]){
                    int x=col[u],y=col[v];
                    G[x].push_back(y);
                }
            }
        }
        
        for(int i=1;i<=n;i++){
            int x; cin>>x; buc[x]++;
        }
        
        for(int i=1;i<=n;i++){
            if(buc[i]){
                p[++pid]=i;
                sum[pid]=sum[pid-1]+buc[i];
            }
        }
        
        for(int i=1;i<=pid;i++) mp1[sum[i]]=i,mp2[n-sum[i-1]]=i;
        top=pos=stl=str=0;
        dfs1(1,0);
        
        if(!top){
            cout<<"No"<<endl;
            continue;
        }
        
        dye(top,stl,str,p[pos]);
        
        int x=stl,lst=top,nw=pos;
        while(x){
            if(nw>1 && mp1[siz[x]]==nw-1) nw--;
            int y=recf[x];
            dye(x,lst,y,p[nw]);
            lst=x; x=y;
        }
        x=str,lst=top,nw=pos;
        while(x){
            if(nw<pid && mp2[siz[x]]==nw+1) nw++;
            int y=recg[x];
            dye(x,lst,y,p[nw]);
            lst=x; x=y;
        }
        
        cout<<"Yes"<<endl;
        for(int i=1;i<=n;i++) cout<<ans[col[i]]<<" ";
        cout<<endl;
    }
    
}

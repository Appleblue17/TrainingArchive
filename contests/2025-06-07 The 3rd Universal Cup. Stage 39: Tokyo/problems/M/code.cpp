#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=5e5+5,M=5e5+5;
int n,m;
struct abc{
    int u,v,w;
}edg[M];
bool operator <(abc X,abc Y){
    return X.w<Y.w;
}


struct nod{
	int to,nxt,w;
}e[M*2];

int head[N],cnt;
void add(int u,int v,int w){
    e[++cnt]={v,head[u],w};
	head[u]=cnt;
}

int fa[N];
int getf(int x){
    if(fa[x]==x) return x;
    return x=getf(fa[x]);
}

int dep[N],dis[N],f[N][20];

void dfs(int u,int fa){
	f[u][0]=fa;
    dep[u]=dep[fa]+1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==fa) continue;
        dis[v]=dis[u]+e[i].w;
		dfs(v,u);
	}
}

int lca(int x,int y){
	if(dep[x]>dep[y]) swap(x,y);
	for(int i=19;i>=0;i--){
		if(dep[f[y][i]]>=dep[x]) y=f[y][i];
	}
	if(x==y) return x;
	for(int i=19;i>=0;i--){
		if(f[x][i]!=f[y][i]) x=f[x][i],y=f[y][i];
	}
	return f[x][0];
}


bool tag[M];

signed main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        scanf("%lld%lld%lld",&edg[i].u,&edg[i].v,&edg[i].w);
    }
    sort(edg+1,edg+m+1);
    
    for(int i=1;i<=n;i++) fa[i]=i;
    for(int t=1;t<=m;t++){
        int u=edg[t].u,v=edg[t].v,w=edg[t].w;
        int fu=getf(u),fv=getf(v);
        if(fu==fv){
            // assert dis(u,v)<=w
            tag[t]=1;
        }
        else{
            fa[fu]=fv;
            add(u,v,w);
            add(v,u,w);
            // cout<<u<<" "<<v<<" "<<w<<endl;
        }
    }
    
	dfs(1,0);
	for(int j=1;j<=19;j++)
		for(int i=1;i<=n;i++)
			f[i][j]=f[f[i][j-1]][j-1];
    
    for(int t=1;t<=m;t++){
        if(!tag[t]) continue;
        int u=edg[t].u,v=edg[t].v,w=edg[t].w;
        int lc=lca(u,v);
        int ds=dis[u]+dis[v]-2*dis[lc];
        // cout<<"  "<<u<<" "<<v<<": "<<lc<<" "<<ds<<endl;
        if(ds>w){
            puts("No");
            return 0;
        }
    }
    puts("Yes");
}

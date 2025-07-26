#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
typedef long long ll;
ll T;
ll n, m, q,pre[N],nxt[N],lst[N];
vector<ll> p[N];
unordered_map<ll, bool> h;
vector<ll> g[N];
inline ll hs(ll  x, ll  y){
    return 1ll*x*N+y;
}

ll dfn[N],low[N],cnt;
//vector<ll> scc[N];
stack<ll> s;
ll ins[N],sccol[N],scnt,sind[N],soud[N],col[N];
void tarjan(ll u){
	dfn[u] = low[u] = ++cnt;
	ins[u]=1;
	s.push(u);
	for(ll i=0;i<g[u].size();i++){
		ll v = g[u][i];
		if(!dfn[v]){
			tarjan(v);
			low[u] = min(low[v],low[u]);
		}
		else if(ins[v])low[u] = min(dfn[v],low[u]);
	}
	if(dfn[u] == low[u]){
		scnt++;
		ll v=0;
		while(v != u){
			v = s.top();
			s.pop();
			ins[v] = 0;
			sccol[v] = scnt;
			//scc[scnt].push_back(v);
		}
	}
}

ll nn(ll x){
    return x*(x-1)/2;
}

void solve(){
    scanf("%lld%lld%lld", &n, &m, &q);
    for(int i=1; i<=n; ++i){
        g[i].clear(), p[i].clear();
        dfn[i]=0;
        low[i]=0;
        sccol[i]=0;
    }
    cnt=0;scnt=0;
    pre[0]=0;
    h.clear();
    for(int i=1; i<=m; ++i){
        p[i].resize(n+1);
        for(int j=1; j<=n; ++j) scanf("%lld", &p[i][j]);
        for(int j=1; j<n; ++j) {
            if(h.find(hs(p[i][j], p[i][j+1]))==h.end()){
                h[hs(p[i][j], p[i][j+1])]=true;
                g[p[i][j]].push_back(p[i][j+1]);
                //printf("add edge %lld %lld\n",p[i][j],p[i][j+1]);
            }
        }
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i])tarjan(i);
    }
    
    for(int i=1;i<=n;i++){
        col[i] = sccol[p[1][i]];
        //printf("sccol[%d]=%lld,col[%d]=%lld\n",i,sccol[i],i,col[i]);
        
    }
    ll L=1,R=n,val=0;
    pre[1]=0;nxt[n]=n;
    lst[1]=1;
    for(int i=1;i<n;i++){
        if(col[i] != col[i+1]){
            L = i+1;
            val=-1;
        }
        lst[i+1]=L;
        val++;
        pre[i+1]=pre[i]+val;
    }
    for(int i=n;i>1;i--){
        if(col[i] != col[i-1]){
            R = i-1;
        }
        nxt[i-1]=R;
    }
    //for(int i=1;i<=n;i++){
    //    printf("i=%d,col=%lld,pre=%lld,nxt=%lld,lst=%lld\n",i,col[i],pre[i],nxt[i],lst[i]);
    //}
    ll ans=0;
    for(int i=1;i<=q;i++){
        ll id,l,r;
        scanf("%lld%lld%lld",&id,&l,&r);
        l = (l+ans)%n+1;
        r = (r+ans)%n+1;
        //ans = nn(nxt[l]-l+1)+nn(r-lst[r]+1)+pre[lst[r]]-pre[nxt[l]];
        if(col[l] != col[r])ans = nn(nxt[l]-l+1)+pre[r]-pre[nxt[l]];
        else ans = nn(r-l+1);
        printf("%lld\n",ans);
    }
}
int main(){
    scanf("%lld", &T);
    while(T--){
        solve();
    }
}

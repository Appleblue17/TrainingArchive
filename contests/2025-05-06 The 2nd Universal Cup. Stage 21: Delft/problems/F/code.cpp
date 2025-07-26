#include <bits/stdc++.h>
using namespace std;
const int N=5e5+5;
int n;
int a[N];
int sz[N], cir[N];
bool vis[N];
bool ins[N];
int stk[N], top;
vector<int> e[N];
vector<int> chain[N];
int cnt;
int bid[N];
int mncir, mxcir;
int rk[N];
inline bool cmp(int x, int y){
    if(sz[x]!=sz[y]) return sz[x]<sz[y];
    return x<y;
}
bool oncir[N];
void solve(){
    for(int i=1; i<=cnt; ++i) rk[i]=i;
    sort(rk+1, rk+cnt+1, cmp);
    multiset<int> st;
    for(int i=1; i<=cnt; ++i) st.insert(cir[i]);
    int it=1;
    for(int i=1; i<mxcir; ++i){
        while(it<=cnt&&sz[rk[it]]<i){
            st.erase(st.find(cir[rk[it]]));
            ++it;
        }
        if(i<mncir){
            printf("1 ");
            continue;
        }
        if(!st.empty()&&(*st.begin())<=i) printf("0 ");
        else printf("1 ");
    }
    it=cnt; int sum=sz[rk[cnt]];
    for(int i=mxcir; i<=n; ++i){
        while(sum<i) --it, sum+=sz[rk[it]];
        printf("%d ", cnt-it);  
    }
}
int dep[N], son[N], tp[N];
void dfs(int x){
    dep[x]=1;
    for(auto y:e[x]) {
        if(oncir[y]) continue;
        dfs(y);
        dep[x]=max(dep[x], dep[y]+1);
        if(dep[y]>dep[son[x]]) son[x]=y;
    }
}
void dfs2(int x, int tpp){
    tp[x]=tpp;
    if(son[x]) dep[son[x]]=dep[x]+1, dfs2(son[x], tpp);
    for(auto y:e[x]){
        if(oncir[y]||y==son[x]) continue;
        dep[y]=dep[x]+1;
        dfs2(y, y);
    } 
}
priority_queue<int> que[N];
int main(){
	// freopen("D:\\nya\\acm\\A\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\A\\test.out","w",stdout);
    scanf("%d", &n);
    for(int i=1; i<=n; ++i) scanf("%d", &a[i]), e[a[i]].push_back(i);
    for(int i=1; i<=n; ++i) if(!vis[i]){
        int p=i;
        do{
            vis[p]=1;
            ins[p]=1;
            stk[++top]=p;
            p=a[p];
        }while(!vis[p]);
        if(ins[p]){
            while(top) ins[stk[top]]=0, --top;
            ++cnt;
            do{
                chain[cnt].push_back(p);
                ins[p]=1; bid[p]=cnt; oncir[p]=1;
                p=a[p];
            }while(!ins[p]);
            for(auto t:chain[cnt]) ins[t]=0;
        }
        else{
            while(top) ins[stk[top]]=0, --top;
        }
    }
    for(int i=1; i<=cnt; ++i) {
        cir[i]=chain[i].size();
        for(auto t:chain[i]) dfs(t), dfs2(t, t);
    }
    mncir=n; mxcir=1;
    for(int i=1; i<=cnt; ++i) mncir=min(mncir, cir[i]), mxcir=max(mxcir, cir[i]);
    int rcnt=cnt;
    for(int i=1; i<=n; ++i) if(e[i].empty()){
        if(oncir[tp[i]]){
            que[bid[tp[i]]].push(dep[i]-dep[tp[i]]);
        }
        else{
            ++cnt;
            sz[cnt]=dep[i]-dep[tp[i]]+1;
            cir[cnt]=n+1;
        }
    }
    for(int i=1; i<=rcnt; ++i) {
        sz[i]=cir[i];
        if(!que[i].empty()){
            sz[i]+=que[i].top(); que[i].pop();
        }
        while(!que[i].empty()){
            ++cnt;
            sz[cnt]=que[i].top();
            cir[cnt]=n+1;
            que[i].pop();
        }
    }
    // for(int i=1; i<=cnt; ++i) cout<<sz[i]<<' '<<cir[i]<<endl;
    solve();
}

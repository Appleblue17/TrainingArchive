#include <bits/stdc++.h>
using namespace std;
// #define int long long
int T, n, m;
const int N=2e5+5;
struct myheap{
    priority_queue<int> p1, p2;
    inline void push(int x){
        p1.push(x);
    }
    inline void pop(int x){
        p2.push(x);
    }
    inline int top(){
        while(!p2.empty()&&p1.top()==p2.top()) p1.pop(), p2.pop();
        return p1.top();
    }
    inline void clear(){
        while(!p1.empty()) p1.pop();
        while(!p2.empty()) p2.pop();
    }
}pq[N];
int fx[N], fy[N], fz[N], fa[N], fb[N];
int va[N], vb[N];
vector<int> vec[N];
bool vis[N];
void solve(){
    scanf("%d%d", &n, &m);
    for(int i=0; i<=n; ++i) pq[i].clear(), vec[i].clear();
    for(int i=1; i<=m; ++i){
        scanf("%d%d%d%d%d", &fa[i], &fb[i], &fx[i], &fy[i], &fz[i]);
        vec[fa[i]].push_back(i);
        vec[fb[i]].push_back(i);
        if(fx[i]+fz[i]<=fy[i]){
            pq[fa[i]].push(va[i]=(fx[i]+fz[i]));
            pq[fb[i]].push(vb[i]=fy[i]);
        }
        else if(fy[i]+fz[i]<=fx[i]){
            pq[fa[i]].push(va[i]=fx[i]);
            pq[fb[i]].push(vb[i]=(fy[i]+fz[i]));
        }
        else if(fx[i]<=fy[i]){
            int dt=fz[i]-(fy[i]-fx[i]);
            pq[fa[i]].push(va[i]=(fy[i]+dt/2));
            pq[fb[i]].push(vb[i]=(fy[i]+dt-dt/2));
        }
        else{
            int dt=fz[i]-(fx[i]-fy[i]);
            pq[fa[i]].push(va[i]=(fx[i]+dt/2));
            pq[fb[i]].push(vb[i]=(fx[i]+dt-dt/2));
        }
    }
    for(int i=1; i<=n; ++i) pq[0].push(pq[i].top());
    vector<int> ans;
    for(int i=1; i<=n; ++i){
        pq[0].pop(pq[i].top());
        vector<int> bin;
        for(auto t:vec[i]){
            if(fa[t]==i) {
                if(!vis[fb[t]]) vis[fb[t]]=1, bin.push_back(fb[t]);
            }
            else{
                if(!vis[fa[t]]) vis[fa[t]]=1, bin.push_back(fa[t]);
            }
        }
        for(auto t:bin) pq[0].pop(pq[t].top());
        for(auto t:vec[i]){
            pq[fa[t]].pop(va[t]); pq[fb[t]].pop(vb[t]);
            if(fa[t]==i) {
                pq[i].push(fx[t]+fz[t]);
                pq[fb[t]].push(fy[t]);
            }
            else{
                pq[i].push(fy[t]+fz[t]);
                pq[fa[t]].push(fx[t]);
            }
        }
        for(auto t:bin) pq[0].push(pq[t].top());
        if(pq[i].top()>pq[0].top()) ans.push_back(i);
        for(auto t:bin) pq[0].pop(pq[t].top());
        for(auto t:vec[i]){
            pq[fa[t]].push(va[t]); pq[fb[t]].push(vb[t]);
            if(fa[t]==i) {
                pq[i].pop(fx[t]+fz[t]);
                pq[fb[t]].pop(fy[t]);
            }
            else{
                pq[i].pop(fy[t]+fz[t]);
                pq[fa[t]].pop(fx[t]);
            }
        }
        for(auto t:bin) pq[0].push(pq[t].top()), vis[t]=0;
        pq[0].push(pq[i].top());
    }
    printf("%d\n", (int)ans.size());
    for(auto t:ans) printf("%d ", t);
    putchar('\n');
}
signed main() {
    scanf("%d", &T);
    while(T--){
        solve();
    }
}

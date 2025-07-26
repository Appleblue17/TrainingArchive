#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n, m;
vector<int> e[N];
int d[N];
void dfs(int x, int fa){
    d[x]=d[fa]+1;
    for(auto y:e[x]) if(y^fa) dfs(y, x);
}
int val[N], p[N];
int op[N];
bool cmp(int x, int y){
    return val[x]<val[y];
}
int main(){
    scanf("%d%d", &n, &m);
    for(int i=1; i<=m*2; ++i){
        for(int j=1; j<=n; ++j) e[j].clear();
        for(int x, y, j=1; j<n; ++j){
            scanf("%d%d", &x, &y);
            e[x].push_back(y); e[y].push_back(x);
        }
        dfs(1, 0);
        int rt=1;
        for(int j=1; j<=n; ++j) if(d[j]>=d[rt]) rt=j;
        dfs(rt, 0);
        for(int j=1; j<=n; ++j) val[i]=max(val[i], d[j]);
        p[i]=i;
    }
    sort(p+1, p+2*m+1, cmp);
    for(int i=1; i<=m; ++i) op[p[i]]=1;
    for(int i=1; i<=m*2; ++i) {
        if(op[i]) printf("DSU\n");
        else printf("Uniform\n");
    }
    return 0;
}

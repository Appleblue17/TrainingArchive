#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
typedef long long ll;
typedef unsigned long long ull;
int n, m;
int d[35][4];
map<__int128, ll> h[35];
ull hs(int x, int y){
    return (ull)INT_MAX*x+y;
}
__int128 hs2(ull x, ull y){
    if(x>y) swap(x, y);
    return (__int128)LONG_LONG_MAX*x+y;
}
typedef pair<int, int> pii;
#define fi first
#define se second
#define mapa make_pair
vector<pii> e[35][4];
int p1x[35][10], p1y[35][10], p2x[35][10], p2y[35][10];
int stk[N], top;
bool flag;
void dfs(int d, int x, int fa, int goal){
    if(x==goal){
        flag=1; return ;
    }
    for(auto edg:e[d][x]) {
        int y=edg.fi, z=edg.se;
        if(y==fa) continue;
        stk[++top]=z;
        dfs(d, y, x, goal);
        if(flag) return ;
        --top;
    }
}
inline ll calc(int d, int sx, int sy, int ex, int ey){
    if(d==0) return 0;
    __int128 state=hs2(hs(sx, sy), hs(ex, ey));
    if(h[d].find(state)!=h[d].end()) return h[d][state];
    int id1=((sx>(1<<(d-1)))?2:0)+((sy>(1<<(d-1)))?1:0);
    int id2=((ex>(1<<(d-1)))?2:0)+((ey>(1<<(d-1)))?1:0);
    if(sx>(1<<(d-1))) sx-=(1<<(d-1));
    if(sy>(1<<(d-1))) sy-=(1<<(d-1));
    if(ex>(1<<(d-1))) ex-=(1<<(d-1));
    if(ey>(1<<(d-1))) ey-=(1<<(d-1));
    flag=0; top=0;
    dfs(d, id1, -1, id2);
    ll ret=0;
    vector<int> vec;
    for(int i=1; i<=top; ++i) vec.push_back(stk[i]);
    for(int i=0; i<(int)vec.size(); ++i){
        ++ret;
        ret+=calc(d-1, sx, sy, p1x[d][vec[i]], p1y[d][vec[i]]);
        sx=p2x[d][vec[i]]; sy=p2y[d][vec[i]];
    }
    ret+=calc(d-1, sx, sy, ex, ey);
    
    return h[d][state]=ret;
}
int main(){
    scanf("%d", &n);
    for(int i=1; i<=n; ++i){
        int idx=0;
        for(int j=0; j<4; ++j) {
            scanf("%d", &d[i][j]);
            if(d[i][j]==0) continue;
            if(j==0){
                p1y[i][++idx]=d[i][j], p1x[i][idx]=1<<(i-1);
                p2y[i][idx]=d[i][j], p2x[i][idx]=1;
                e[i][1].emplace_back(3, idx);
                p1y[i][++idx]=d[i][j], p1x[i][idx]=1;
                p2y[i][idx]=d[i][j], p2x[i][idx]=1<<(i-1);
                e[i][3].emplace_back(1, idx); 
            }
            if(j==1){
                p1y[i][++idx]=1, p1x[i][idx]=(1<<(i-1))+1-d[i][j];
                p2y[i][idx]=1<<(i-1), p2x[i][idx]=(1<<(i-1))+1-d[i][j];
                e[i][1].emplace_back(0, idx);
                p1y[i][++idx]=1<<(i-1), p1x[i][idx]=(1<<(i-1))+1-d[i][j];
                p2y[i][idx]=1, p2x[i][idx]=(1<<(i-1))+1-d[i][j];
                e[i][0].emplace_back(1, idx); 
            }
            if(j==2){
                p1y[i][++idx]=(1<<(i-1))+1-d[i][j], p1x[i][idx]=1<<(i-1);
                p2y[i][idx]=(1<<(i-1))+1-d[i][j], p2x[i][idx]=1;
                e[i][0].emplace_back(2, idx);
                p1y[i][++idx]=(1<<(i-1))+1-d[i][j], p1x[i][idx]=1;
                p2y[i][idx]=(1<<(i-1))+1-d[i][j], p2x[i][idx]=1<<(i-1);
                e[i][2].emplace_back(0, idx); 
            }
            if(j==3){
                p1y[i][++idx]=1<<(i-1), p1x[i][idx]=d[i][j];
                p2y[i][idx]=1, p2x[i][idx]=d[i][j];
                e[i][2].emplace_back(3, idx);
                p1y[i][++idx]=1, p1x[i][idx]=d[i][j];
                p2y[i][idx]=1<<(i-1), p2x[i][idx]=d[i][j];
                e[i][3].emplace_back(2, idx);  
            }
        }
    }
    scanf("%d", &m);
    while(m--){
        int sx, sy, ex, ey;
        scanf("%d%d%d%d", &sx, &sy, &ex, &ey);
        printf("%lld\n", calc(n, sx, sy, ex, ey));
    }
    return 0;
}

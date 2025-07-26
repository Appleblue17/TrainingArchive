#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
typedef long long ll;
const ll inf=1e18;
int T;
int n, m;
int a[N], lim[N];
int st[20][N], lg[N];
ll tr[N<<2];
inline void mdf(int p, int l, int r, int x, ll v){
    if(l==r){
        tr[p]=v;
        return ;
    }
    int mid=(l+r)>>1;
    if(x<=mid) mdf(p<<1, l, mid, x, v);
    else mdf(p<<1|1, mid+1, r, x, v);
    tr[p]=min(tr[p<<1], tr[p<<1|1]);
}
inline int get(int l, int r){
    int t=lg[r-l+1];
    return max(st[t][l], st[t][r-(1<<t)+1]);
}
void build(){
    for(int i=2; i<=n+1; ++i) lg[i]=lg[i>>1]+1;
    for(int i=0; i<=n; ++i) st[0][i]=lim[i];
    for(int i=1; i<=lg[n+1]; ++i){
        for(int j=0; j+(1<<i)-1<=n; ++j){
            st[i][j]=max(st[i-1][j], st[i-1][j+(1<<(i-1))]);
        }
    }
    for(int i=1; i<=(n+1)*4; ++i) tr[i]=inf;
    mdf(1, 0, n, 0, 0);
    mdf(1, 0, n, 1, a[1]);
}
inline ll get(int p, int l, int r, int L, int R){
    if(L<=l&&r<=R) return tr[p];
    int mid=(l+r)>>1; ll ret=inf;
    if(L<=mid) ret=get(p<<1, l, mid, L, R);
    if(R>mid) ret=min(ret, get(p<<1|1, mid+1, r, L, R));
    return ret;
}
void solve(){
    scanf("%d", &n);
    for(int i=1; i<=n; ++i) lim[i]=0;
    for(int i=1; i<=n; ++i) scanf("%d", &a[i]);
    scanf("%d", &m);
    while(m--){
        int l, r; scanf("%d%d", &l, &r);
        lim[r]=max(lim[r], l);
    }
    build();
    ll ans=0;
    for(int i=1; i<=n; ++i){
        int L=0, R=i-1, mid, ret=i;
        while(L<=R){
            mid=(L+R)>>1;
            if(mid>=get(mid, i)) ret=mid, R=mid-1;
            else L=mid+1;
        }
        ans=get(1, 0, n, ret, i);
        if(i!=n) mdf(1, 0, n, i+1, ans+a[i+1]);
    }
    printf("%lld\n", ans);
}
int main(){
    scanf("%d", &T);
    while(T--){
        solve();
    }
    
}

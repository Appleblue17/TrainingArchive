#pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=5e5+5;
int n, fx[N], fy[N];
int cnt[N][4];
int id[N];
inline bool cmp(int x, int y){
    if(fx[x]!=fx[y]) return fx[x]<fx[y];
    return x<y;
}
int tr[N*70], ls[N*70], rs[N*70], rt, idx;
inline void ins(int &p, int l, int r, int x){
    if(!p){
        p=++idx; tr[p]=ls[p]=rs[p]=0;
    }
    ++tr[p];
    if(l==r) return ;
    int mid=((ll)l+(ll)r)>>1ll;
    if(x<=mid) ins(ls[p], l, mid, x);
    else ins(rs[p], mid+1, r, x);
}
inline int get(int p, int l, int r, int L, int R){
    if(!p) return 0;
    if(L<=l&&r<=R) return tr[p];
    int mid=((ll)l+(ll)r)>>1ll;
    int ret=0;
    if(L<=mid) ret=get(ls[p], l, mid, L, R);
    if(R>mid) ret+=get(rs[p], mid+1, r, L, R);
    return ret;
}
int main(){
    scanf("%d", &n);
    for(int i=1, x, y; i<=n; ++i) scanf("%d%d", &x, &y), fx[i]=x+y, fy[i]=x-y;
    ll res=1ll*n*(n-1)*(n-2)/6;
    for(int i=1; i<=n; ++i) id[i]=i;
    sort(id+1, id+n+1, cmp);
    for(int l=1, r=1; l<=n; l=r+1){
        while(r<n&&fx[id[r+1]]==fx[id[l]]) ++r;
        for(int i=l; i<=r; ++i){
            cnt[id[i]][0]+=get(rt, -INT_MAX, INT_MAX, -INT_MAX, fy[id[i]]-1);
        }
        for(int i=l; i<=r; ++i) ins(rt, -INT_MAX, INT_MAX, fy[id[i]]);
    }
    rt=0; idx=0;
    for(int i=1; i<=n; ++i) fx[i]=-fx[i];
    sort(id+1, id+n+1, cmp);
    for(int l=1, r=1; l<=n; l=r+1){
        while(r<n&&fx[id[r+1]]==fx[id[l]]) ++r;
        for(int i=l; i<=r; ++i){
            cnt[id[i]][1]+=get(rt, -INT_MAX, INT_MAX, -INT_MAX, fy[id[i]]-1);
        }
        for(int i=l; i<=r; ++i) ins(rt, -INT_MAX, INT_MAX, fy[id[i]]);
    }
    rt=0; idx=0;
    for(int i=1; i<=n; ++i) fy[i]=-fy[i];
    sort(id+1, id+n+1, cmp);
    for(int l=1, r=1; l<=n; l=r+1){
        while(r<n&&fx[id[r+1]]==fx[id[l]]) ++r;
        for(int i=l; i<=r; ++i){
            cnt[id[i]][3]+=get(rt, -INT_MAX, INT_MAX, -INT_MAX, fy[id[i]]-1);
        }
        for(int i=l; i<=r; ++i) ins(rt, -INT_MAX, INT_MAX, fy[id[i]]);
    }
    rt=0; idx=0;
    for(int i=1; i<=n; ++i) fx[i]=-fx[i];
    sort(id+1, id+n+1, cmp);
    for(int l=1, r=1; l<=n; l=r+1){
        while(r<n&&fx[id[r+1]]==fx[id[l]]) ++r;
        for(int i=l; i<=r; ++i){
            cnt[id[i]][2]+=get(rt, -INT_MAX, INT_MAX, -INT_MAX, fy[id[i]]-1);
        }
        for(int i=l; i<=r; ++i) ins(rt, -INT_MAX, INT_MAX, fy[id[i]]);
    }
    for(int i=1; i<=n; ++i){
        res-=1ll*cnt[i][0]*cnt[i][3];
        res-=1ll*cnt[i][1]*cnt[i][2];
    }
    printf("%lld\n", res);
}

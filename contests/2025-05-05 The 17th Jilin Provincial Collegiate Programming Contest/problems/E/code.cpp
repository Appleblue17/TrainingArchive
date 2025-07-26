#include <bits/stdc++.h>
using namespace std;
// #define int long long
const int N=1e6+5;
int n;
int a[N], b[N];
int va[N], vb[N];
int fa[N];
inline int get(int x){
    if(x==fa[x]) return x;
    return fa[x]=get(fa[x]);
}
inline void merge(int x, int y){
    x=get(x); y=get(y);
    fa[x]=y;
}
int id[N], iid[N];
inline bool cmp(int x, int y){
    if(va[x]!=va[y]) return va[x]<va[y];
    return x<y;
}
void work(int x, int l, int r){
    for(int i=l; i<=r; ++i) merge(id[x], id[i]);
}
void link(int l, int r){
    if(l==r) return ;
    int mid=(l+r)>>1;
    link(l, mid); link(mid+1, r);
    int lp=l, rp=mid+1, lstl=l, it=l;
    while(lp<=mid||rp<=r){
        if(lp>mid){
            work(rp, lstl, lp-1);
            lstl=max(lstl, lp-1);
            iid[it]=id[rp];
            ++it; ++rp;
        }
        else if(rp>r){
            iid[it]=id[lp];
            ++it; ++lp;
        }
        else{
            if(vb[id[lp]]>=vb[id[rp]]){
                work(rp, lstl, lp);
                lstl=max(lstl, lp);
                iid[it]=id[lp];
                ++it; ++lp;
            }
            else{
                work(rp, lstl, lp-1);
                lstl=max(lstl, lp-1);
                iid[it]=id[rp];
                ++it; ++rp;
            }
        }
    }
    for(int i=l; i<=r; ++i) id[i]=iid[i];
}
void solve(){
    sort(id+1, id+n+1, cmp);
    link(1, n);
}
signed main() {
    scanf("%d", &n);
    for(int i=1; i<=n; ++i){
        scanf("%d%d", &a[i], &b[i]);
        va[i]=a[i]-i; vb[i]=b[i]-i;
        fa[i]=i; id[i]=i;
    }
    solve();
    for(int i=1; i<=n; ++i){
        va[i]=b[i]-i; vb[i]=a[i]-i;
    }
    solve();
    int cnt=0;
    for(int i=1; i<=n; ++i) cnt+=(get(i)==i);
    printf("%d\n", cnt);
}

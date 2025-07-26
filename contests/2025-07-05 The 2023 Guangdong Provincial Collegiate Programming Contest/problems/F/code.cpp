#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
typedef long long ll;
int T;
int n, m;
int c[N], a[N];
struct T1{
    ll sum[N<<2];
    void build(int p, int l, int r){
        if(l==r){
            sum[p]=a[l];
            return ;
        }
        int mid=(l+r)>>1;
        build(p<<1, l, mid); build(p<<1|1, mid+1, r);
        sum[p]=sum[p<<1]+sum[p<<1|1];
    }
    void mdf(int p, int l, int r, int x){
        if(l==r){
            sum[p]=a[l];
            return ;
        }
        int mid=(l+r)>>1;
        if(x<=mid) mdf(p<<1, l, mid, x);
        else mdf(p<<1|1, mid+1, r, x);
        sum[p]=sum[p<<1]+sum[p<<1|1];
    }
    ll get(int p, int l, int r, int L, int R){
        if(L<=l&&r<=R) return sum[p];
        int mid=(l+r)>>1; ll ret=0;
        if(L<=mid) ret=get(p<<1, l, mid, L, R);
        if(R>mid) ret+=get(p<<1|1, mid+1, r, L, R);
        return ret;
    }
}t1;
int idx, rt[N];
int ls[N*60], rs[N*60], sz[N*60];
inline int gen(){
    ++idx; ls[idx]=0; rs[idx]=0; sz[idx]=0;
    return idx;
}
void add(int &p, int l, int r, int x, int v){
    if(!p) p=gen();
    if(l==r) {
        sz[p]+=v;
        return ;
    }
    int mid=(l+r)>>1;
    if(x<=mid) add(ls[p], l, mid, x, v);
    else add(rs[p], mid+1, r, x, v);
    sz[p]=sz[ls[p]]+sz[rs[p]];
}
int get(int p, int l, int r, int L, int R){
    if(!p) return 0;
    if(L<=l&&r<=R) return sz[p];
    int mid=(l+r)>>1;
    int ret=0;
    if(L<=mid) ret=get(ls[p], l, mid, L, R);
    if(R>mid) ret+=get(rs[p], mid+1, r, L, R);
    return ret;
}
int k, b[N];
void solve(){
    scanf("%d%d", &n, &m);
    for(int i=1; i<=n; ++i) scanf("%d", &c[i]), rt[i]=0;
    for(int i=1; i<=n; ++i) scanf("%d", &a[i]);
    t1.build(1, 1, n);
    idx=0;
    for(int i=1; i<=n; ++i) add(rt[c[i]], 1, n, i, 1);
    while(m--){
        int tp; scanf("%d", &tp);
        if(tp==1){
            int x; scanf("%d", &x);
            add(rt[c[x]], 1, n, x, -1);
            scanf("%d", &c[x]);
            add(rt[c[x]], 1, n, x, 1);
        }
        else if(tp==2){
            int x; scanf("%d", &x);
            scanf("%d", &a[x]);
            t1.mdf(1, 1, n, x);
        }
        else{
            int x; scanf("%d", &x);
            scanf("%d", &k);
            for(int i=1; i<=k; ++i) scanf("%d", &b[i]);
            int lp=x, rp=x;
            int L=1, R=x-1, mid, ret=x;
            while(L<=R){
                mid=(L+R)>>1;
                int sum=0;
                for(int i=1; i<=k; ++i) sum+=get(rt[b[i]], 1, n, mid, x);
                if(sum==x-mid+1) {
                    ret=mid; R=mid-1;
                }
                else{
                    L=mid+1;
                }
            }
            lp=ret;
            L=x+1, R=n, ret=x;
            while(L<=R){
                mid=(L+R)>>1;
                int sum=0;
                for(int i=1; i<=k; ++i) sum+=get(rt[b[i]], 1, n, x, mid);
                if(sum==mid-x+1) {
                    ret=mid; L=mid+1;
                }
                else{
                    R=mid-1;
                }
            }
            rp=ret;
            printf("%lld\n", t1.get(1, 1, n, lp, rp));
        }
        
    }
}
int main(){
    scanf("%d", &T);
    while(T--){
        solve();
    }
}

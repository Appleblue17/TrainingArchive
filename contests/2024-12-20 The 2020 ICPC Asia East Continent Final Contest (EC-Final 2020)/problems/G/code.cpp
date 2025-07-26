#pragma GCC optimize(3)
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
typedef long long ll;
struct mat1{
    ll a0, a1, sum;
};
struct mat2{
    ll a00, a01, a02;
    ll a10, a11, a12;
};
inline bool operator !=(mat2 x, mat2 y){
    if(x.a00!=y.a00) return true;
    if(x.a01!=y.a01) return true;
    if(x.a02!=y.a02) return true;
    if(x.a10!=y.a10) return true;
    if(x.a11!=y.a11) return true;
    if(x.a12!=y.a12) return true;
    return false;
}
int n, m;
mat1 tr[N<<2]; mat2 tag[N<<2];
int a[N];
typedef pair<int, int> pii;
#define fi first
#define se second
#define mapa make_pair
vector<pii> vec[N];
ll ans[N];
int lst[N];
mat2 bs, o0, o1;
inline mat1 operator +(mat1 x, mat1 y){
    return (mat1){x.a0+y.a0, x.a1+y.a1, x.sum+y.sum};
}
inline mat1 operator *(mat1 x, mat2 y){
    mat1 z;
    z.a0=x.a0*y.a00+x.a1*y.a10;
    z.a1=x.a0*y.a01+x.a1*y.a11;
    z.sum=x.sum+x.a0*y.a02+x.a1*y.a12;
    return z;
}
inline mat2 operator *(mat2 x, mat2 y){
    mat2 z;
    z.a00=x.a00*y.a00+x.a01*y.a10;
    z.a01=x.a00*y.a01+x.a01*y.a11;
    z.a02=x.a00*y.a02+x.a01*y.a12+x.a02;
    
    z.a10=x.a10*y.a00+x.a11*y.a10;
    z.a11=x.a10*y.a01+x.a11*y.a11;
    z.a12=x.a10*y.a02+x.a11*y.a12+x.a12;
    return z;
}
inline void build(int p, int l, int r){
    tag[p]=bs;
    if(l==r){
        tr[p].a0=1;
        return ;
    }
    int mid=(l+r)>>1;
    build(p<<1, l, mid); build(p<<1|1, mid+1, r);
    tr[p]=tr[p<<1]+tr[p<<1|1];
}
inline void down(int p){
    if(tag[p]!=bs){
        tr[p<<1]=tr[p<<1]*tag[p];
        tr[p<<1|1]=tr[p<<1|1]*tag[p];
        tag[p<<1]=tag[p<<1]*tag[p];
        tag[p<<1|1]=tag[p<<1|1]*tag[p];
        tag[p]=bs;
    }
}
inline void mdf(int p, int l, int r, int L, int R, mat2 &o){
    if(L>R) return ;
    if(L<=l&&r<=R) {
        tr[p]=tr[p]*o;
        tag[p]=tag[p]*o;
        return ;
    }
    down(p);
    int mid=(l+r)>>1;
    if(L<=mid) mdf(p<<1, l, mid, L, R, o);
    if(R>mid) mdf(p<<1|1, mid+1, r, L, R, o);
    tr[p]=tr[p<<1]+tr[p<<1|1];
}
inline ll qry(int p, int l, int r, int L, int R){
    if(L<=l&&r<=R) return tr[p].sum;
    down(p);
    int mid=(l+r)>>1; ll ret=0;
    if(L<=mid) ret+=qry(p<<1, l, mid, L, R);
    if(R>mid) ret+=qry(p<<1|1, mid+1, r, L, R);
    return ret;
}
int main(){
    bs.a00=bs.a11=1;
    o0.a00=o0.a11=o0.a12=1;
    o1.a01=o1.a10=o1.a02=1;
    scanf("%d", &n);
    for(int i=1; i<=n; ++i) scanf("%d", &a[i]);
    scanf("%d", &m);
    for(int i=1, l, r; i<=m; ++i){
        scanf("%d%d", &l, &r);
        vec[r].emplace_back(l, i);
    }
    build(1, 1, n);
    for(int i=1; i<=n; ++i){
        mdf(1, 1, n, lst[a[i]]+1, i, o1);
        mdf(1, 1, n, 1, lst[a[i]], o0);
        lst[a[i]]=i;
        for(auto t:vec[i]) ans[t.se]=qry(1, 1, n, t.fi, i);
    }
    for(int i=1; i<=m; ++i) printf("%lld\n", ans[i]);
}

#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
typedef pair<int, int> pii;
#define fi first
#define se second
#define mapa make_pair
int n, m;
struct node{
    pii a[24];
    int sum;
    node(){
        for(int i=0; i<24; ++i) a[i]=mapa(-1, -1);
        sum=0;
    }
}tr[N<<2], emp, tem;
inline node operator +(node x, node y){
    node ret=emp;
    for(int i=0; i<24; ++i) if(x.a[i]!=mapa(-1, -1)){
        int res=x.a[i].se;
        if(res+y.sum<=24){
            ret.a[i].fi=x.a[i].fi+((res+y.sum)==24);
            if(res+y.sum==24) ret.a[i].se=0;
            else ret.a[i].se=res+y.sum;
        }
        else{
            for(int j=23; j>=0; --j) if(y.a[j]!=mapa(-1, -1)&&res+j<=24){
                if(ret.a[i]==mapa(-1, -1)){
                    ret.a[i].fi=x.a[i].fi+((res+j)>0)+y.a[j].fi;
                    ret.a[i].se=y.a[j].se;
                }
                else{
                    ret.a[i]=min(ret.a[i], mapa(x.a[i].fi+((res+j)>0)+y.a[j].fi, y.a[j].se));
                }
            }
        }
    }
    if(x.sum<24){
        for(int i=23; i-x.sum>=0; --i) {
            if(y.a[i-x.sum]!=mapa(-1, -1)){
                if(ret.a[i]==mapa(-1, -1)) ret.a[i]=y.a[i-x.sum];
                else ret.a[i]=min(ret.a[i], y.a[i-x.sum]);
            }
        }
        if(x.sum!=0&&y.a[24-x.sum]!=mapa(-1, -1)){
            ret.a[0]=y.a[24-x.sum];
            ret.a[0].fi++;
        }
    }
    ret.sum=x.sum+y.sum;
    return ret;
}
void build(int p, int l, int r){
    if(l==r){
        scanf("%d", &tr[p].sum);
        if(tr[p].sum==24) tr[p].a[0]=mapa(1, 0);
        else tr[p].a[0]=mapa(0, tr[p].sum), tr[p].a[tr[p].sum]=mapa(0, 0);
        return ;
    }
    int mid=(l+r)>>1;
    build(p<<1, l, mid); build(p<<1|1, mid+1, r);
    tr[p]=tr[p<<1]+tr[p<<1|1];
}
void mdf(int p, int l, int r, int x, int v){
    if(l==r){
        tr[p]=emp;
        tr[p].sum=v;
        if(tr[p].sum==24) tr[p].a[0]=mapa(1, 0);
        else tr[p].a[0]=mapa(0, tr[p].sum), tr[p].a[tr[p].sum]=mapa(0, 0);
        return ;
    }
    int mid=(l+r)>>1;
    if(x<=mid) mdf(p<<1, l, mid, x, v);
    else mdf(p<<1|1, mid+1, r, x, v);
    tr[p]=tr[p<<1]+tr[p<<1|1];
}
void get(int p, int l, int r, int L, int R){
    if(L<=l&&r<=R) {tem=tem+tr[p]; return ;}
    int mid=(l+r)>>1;
    if(L<=mid) get(p<<1, l, mid, L, R);
    if(R>mid) get(p<<1|1, mid+1, r, L, R); 
}
int main(){
    scanf("%d%d", &n, &m);
    build(1, 1, n);
    while(m--){
        int o, x, y;
        scanf("%d%d%d", &o, &x, &y);
        if(o==1){
            mdf(1, 1, n, x, y);
        }
        else{
            tem=emp;
            tem.a[0]=mapa(0, 0);
            get(1, 1, n, x, y);
            printf("%d\n", tem.a[0].fi+(tem.a[0].se>0));
        }
    }
}

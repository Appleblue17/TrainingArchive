#pragma GCC optimize(2)
#pragma GCC optimize(3)
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n, k, m;
char s[N];
using u32=uint32_t;
using i32=int32_t;
using u64=uint64_t;
using i64=int64_t;
static u32 _m, m2, inv, r2;
u32 getinv(){
    u32 inv=_m;
    for(int i=0; i<4; ++i) inv*=2-inv*_m;
    return inv;
}
struct Mont{
private :
    u32 x;
public :
    static u32 reduce(u64 x){
        u32 y=(x+u64(u32(x)*inv)*_m)>>32;
        return i32(y)<0?y+_m:y;
    }
    Mont(){;}
    Mont(i32 x):x(reduce(u64(x)*r2)){}
    Mont& operator +=(const Mont &rhs){return x+=rhs.x-m2, i32(x)<0&&(x+=m2), *this;}
    Mont& operator -=(const Mont &rhs){return x-=rhs.x, i32(x)<0&&(x+=m2), *this;}
    Mont& operator *=(const Mont &rhs){return x=reduce(u64(x)*rhs.x), *this;}
    friend Mont operator +(Mont x, const Mont &y){return x+=y;} 
    friend Mont operator -(Mont x, const Mont &y){return x-=y;} 
    friend Mont operator *(Mont x, const Mont &y){return x*=y;} 
    i32 get(){
        u32 res=reduce(x);
        return res>=_m?res-_m:res;
    }
};
void init(int _m){
    ::_m=_m; m2=_m*2;
    inv=-getinv();
    r2=-u64(_m)%_m;
}
struct mat{
    Mont a[20][20];
    mat(){memset(a, 0, sizeof a);}
}mt[N], bs[2];
inline mat operator *(mat x, mat y){
    mat z;
    for(register int i=0; i<k; ++i){
        for(register int j=0; j<k; ++j){
            for(register int kk=0; kk<k; ++kk){
                z.a[i][j]+=x.a[i][kk]*y.a[kk][j];
            }
        }
    }
    return z;
}
int main(){
    init(998244353);
    scanf("%d%d%d", &n, &k, &m);
    for(int i=0; i+1<k; ++i) bs[0].a[i][i+1]=1, bs[1].a[i][i+1]=1;
    for(int i=0; i<k; ++i) bs[1].a[k-1][i]=1; 
    for(int i=1; i<=n; ++i){
        scanf("%s", s+1);
        for(int j=0; j<k; ++j) mt[i].a[j][j]=1;
        for(int j=1; s[j]; ++j){
            if(s[j]=='O') mt[i]=mt[i]*bs[1];
            else mt[i]=mt[i]*bs[0];
        }
        printf("%d\n", mt[i].a[k-1][0].get());
    }
    for(int i=n+1, x, y; i<=n+m; ++i){
        scanf("%d%d", &x, &y);
        mt[i]=mt[x]*mt[y];
        printf("%d\n", mt[i].a[k-1][0].get());
    }
    return 0;
}

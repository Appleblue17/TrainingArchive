#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double dou;
typedef pair<int,int> pii;
#define fi first
#define se second
#define mapa make_pair
typedef long double ld;
typedef unsigned long long ull;
#define ep emplace_back
template <typename T>inline void read(T &x){
	x=0;char c=getchar();bool f=0;
	for(;c<'0'||c>'9';c=getchar()) f|=(c=='-');
	for(;c>='0'&&c<='9';c=getchar())
	x=(x<<1)+(x<<3)+(c^48);
	x=(f?-x:x);
}
const int N=2e7+5, mod1=1e9+7, mod2=998244353;
int n, m;
char s[N];
pii bs=mapa(131, 13331), hs[N], pw[N];
inline pii plu(pii x, pii y){
	return mapa((x.fi+y.fi)%mod1, (x.se+y.se)%mod2);
}
inline pii sub(pii x, pii y){
	return mapa((x.fi-y.fi+mod1)%mod1, (x.se-y.se+mod1)%mod2);
}
inline pii mul(pii x, pii y){
	return mapa(1ll*x.fi*y.fi%mod1, 1ll*x.se*y.se%mod2);
}
inline bool eq(pii x, pii y){return x.fi==y.fi&&x.se==y.se;}
inline pii get(int l, int r){
	return sub(hs[r], mul(hs[l-1], pw[r-l+1]));
}
inline int lcp(int x, int y){
    int l=1, r=n-max(x, y)+1, mid, ret=0;
    while(l<=r){
        mid=(l+r)>>1;
        if(eq(get(x, x+mid-1), get(y, y+mid-1))) ret=mid, l=mid+1;
        else r=mid-1;
    }
    return ret;
}
inline int lcs(int x, int y){
    int l=1, r=min(x, y), mid, ret=0;
    while(l<=r){
        mid=(l+r)>>1;
        if(eq(get(x-mid+1, x), get(y-mid+1, y))) ret=mid, l=mid+1;
        else r=mid-1;
    }
    return ret;
}
int main(){
	// freopen("D:\\nya\\acm\\A\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\A\\test.out","w",stdout);
    scanf("%d%d", &n, &m);
	scanf("%s", s+1);
	pw[0]=mapa(1, 1);
	for(int i=1; i<=n; ++i) pw[i]=mul(pw[i-1], bs), hs[i]=plu(mapa(s[i], s[i]), mul(hs[i-1], bs));
    int ans=0;
	for(int i=1; i*m<=n; ++i){
        int cnt=0, lstl=-1;
        pii lst=mapa(-1, -1);
        int lp=1, rp=i;
        for(; lp<=n&&ans<i; lp+=i){
            rp=lp+i-1; rp=min(rp, n);
            if(eq(lst, get(lp, rp))){
                ++cnt;
            }
            else {
                if(cnt>=m-1){
                    if(cnt>=m){
                        ans=i;
                        break;
                    }
                    if(lcp(lp, lp-i)+lcs(lp-1, lstl-1)>=i){
                        ans=i;
                        break;
                    }
                }
                cnt=1;
                lst=get(lp, rp);
                lstl=lp;
            }
        }
        if(cnt>=m) ans=i;
    }
    printf("%d\n", ans*m);
	return 0;
}


#pragma GCC optimize(3)
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
const int N=505;
int T, n, m;
pii stk[1000006]; int top;
char str[N];
int a[N][N];
int s[N][N];
inline int get(int l1, int r1, int l2, int r2){
    l1=max(1, l1); l2=max(1, l2);
    r1=min(n, r1); r2=min(n, r2);
    return s[r1][r2]-s[l1-1][r2]-s[r1][l2-1]+s[l1-1][l2-1];
}
bool flag;
inline void perf(int tp, int r){
    for(int i=1; i<=n; ++i) for(int j=1; j<=n; ++j){
        s[i][j]=(tp^1^a[i][j])+s[i][j-1]+s[i-1][j]-s[i-1][j-1];
    }
    if(s[n][n]==n*n||s[n][n]==0) {
        flag=0; return;
    }
    for(int i=1; i<=n; ++i) for(int j=1; j<=n; ++j){
        a[i][j]=(get(i-r, i+r, j-r, j+r)>0)^1^tp;
    }
}
void solve(){
    read(n); read(m);
    for(int i=1; i<=n; ++i){
        scanf("%s", str+1);
        for(int j=1; j<=n; ++j) a[i][j]=str[j]-'0';
    }
    top=0;
    while(m--){
        pii cur; read(cur.fi); read(cur.se);
        
        stk[++top]=cur;
        if(top>=2){
            pii v1=stk[top-1], v2=stk[top];
            if(v1.fi==v2.fi) stk[top-1].se+=stk[top].se, --top;
        }
        while(top>=3){
            pii v1=stk[top-2], v2=stk[top-1], v3=stk[top];
            if(v1.se>=v2.se&&v3.se>=v2.se){
                stk[top-2].se+=v3.se-v2.se;
                 top-=2;
            }
            else break;
        }
    }
    flag=1;
    for(int i=1; i<=top&&flag; ++i) perf(stk[i].fi, stk[i].se);
    for(int i=1; i<=n; ++i){
        for(int j=1; j<=n; ++j) printf("%d", a[i][j]);
        putchar('\n');
    }
}
int main(){
	// freopen("D:\\nya\\acm\\A\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\A\\test.out","w",stdout);
	read(T);
    while(T--) solve();
    return 0;
}

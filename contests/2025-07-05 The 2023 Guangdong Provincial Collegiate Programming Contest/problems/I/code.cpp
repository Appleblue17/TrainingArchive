#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int T, n, m;
int px[N], py[N];
int p[N];
bool cmp(int x, int y){
    if(px[x]!=px[y]) return px[x]<px[y];
    return py[x]<py[y];
}
bool check(int x){
    for(int i=1; i<=x; ++i) p[i]=i-1;
    sort(p+1, p+x+1, cmp);
    for(int i=2; i<=x; ++i){
        if(px[p[i]]<px[p[i-1]]||py[p[i]]<py[p[i-1]]) return false;
    }
    return true;
}
void solve(){
    scanf("%d%d", &n, &m);
    for(int i=1; i<=n; ++i){
        for(int j=1, x; j<=m; ++j){
            scanf("%d", &x);
            px[x]=i; py[x]=j;
        }
    }
    int L=1, R=n+m-1, mid, ret=0;
    while(L<=R){
        mid=(L+R)>>1;
        if(check(mid)){
            ret=mid; L=mid+1;
        }
        else{
            R=mid-1;
        }
    }
    printf("%d\n", ret);
}
int main(){
    scanf("%d", &T);
    while(T--){
        solve();
    }
    
}

#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=66,INF=1e9;
int n,ans=-INF;
int p;
int cnt;

void query(int l,int r){
    printf("? %lld %lld\n",l,r);
    fflush(stdout);
    scanf("%lld",&p);
}

void sol(int l,int r,int pos){
    //printf("sol %lld %lld %lld\n",l,r,pos);
    if(l == r){
        ans = l;
        return;
    }
    if(pos == -1){
        query(l,r);
        pos = p;
    }
    if(r-l == 1){
        if(pos == l){
            ans = r;
            return;
        }
        else{
            ans = l;
            return;
        }
    }
    int x = round((r-l+1)*0.618);
    if(pos <= (l+r)/2){
        query(l,l+x-1);
    }
    else{
        query(r-x+1,r);
    }
    if(p == pos){
        if(pos <= (l+r)/2){
            sol(l,l+x-1,pos);
        }
        else{
            sol(r-x+1,r,pos);
        }
    }
    else{
        if(pos <= (l+r)/2){
            sol(l+x,r,-1);
        }
        else{
            sol(l,r-x,-1);
        }
    }
}

void solve(){
    scanf("%lld",&n);
    sol(1,n,-1);
    printf("! %lld\n",ans);
    fflush(stdout);
}


signed main(){
    int T;
    scanf("%lld",&T);
    while(T--){
        solve();
    }
}

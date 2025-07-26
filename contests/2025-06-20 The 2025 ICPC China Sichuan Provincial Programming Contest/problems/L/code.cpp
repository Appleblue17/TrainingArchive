#pragma GCC optimize(2)
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=4e5+5;
int n;
char str[N];
int s[3][N];
int p[N], x[N], y[N], z[N];
ll ans=0;
struct BIT{
    const int eps=N/2;
    ll tr[N];
    void add(int x, ll v){
        for(x+=eps; x<N; x+=(x&-x)) tr[x]+=v;
    }
    ll get(int x){
        ll ret=0;
        for(x+=eps; x; x-=(x&-x)) ret+=tr[x];
        return ret;
    }
}t1, t2;
void solve(int o1, int o2, int o3){
    for(int i=0; i<=n; ++i){
        x[i]=s[o1][i]-s[o2][i];
        y[i]=s[o2][i]-s[o3][i];
        z[i]=s[o1][i]-s[o3][i];
        p[i]=i;
    }
    sort(p, p+n+1, [&](int A,int B){return x[A]<x[B];});
    int it=0;
    for(int i=1; i<=n; ++i){
        while(x[p[it]]<x[p[i]]) t1.add(y[p[it]], 1), t2.add(y[p[it]], z[p[it]]), ++it;
        ans+=t1.get(y[p[i]]-1)*z[p[i]]-t2.get(y[p[i]]-1);
    }
    for(int i=0; i<it; ++i) t1.add(y[p[i]], -1), t2.add(y[p[i]], -z[p[i]]);
}
void solve2(int o1, int o2, int o3){
    for(int i=0; i<=n; ++i){
        x[i]=s[o1][i]-s[o2][i];
        y[i]=s[o2][i]-s[o3][i];
        z[i]=s[o1][i]-s[o3][i];
        p[i]=i;
    }
    sort(p, p+n+1, [&](int A,int B){return y[A]<y[B];});
    int it=0;
    unordered_map<int, ll> bin1, bin2;
    for(int i=1; i<=n; ++i){
        while(y[p[it]]<y[p[i]]) bin1[x[p[it]]]+=1, bin2[x[p[it]]]+=z[p[it]], ++it;
        ans+=bin1[x[p[i]]]*z[p[i]]-bin2[x[p[i]]];
    }
}
void solve3(int o1, int o2, int o3){
    for(int i=0; i<=n; ++i){
        x[i]=s[o1][i]-s[o2][i];
        y[i]=s[o2][i]-s[o3][i];
        z[i]=s[o1][i]-s[o3][i];
        p[i]=i;
    }
    sort(p, p+n+1, [&](int A,int B){return x[A]<x[B];});
    int it=0;
    unordered_map<int, ll> bin1, bin2;
    for(int i=1; i<=n; ++i){
        while(x[p[it]]<x[p[i]]) bin1[y[p[it]]]+=1, bin2[y[p[it]]]+=z[p[it]], ++it;
        ans+=bin1[y[p[i]]]*z[p[i]]-bin2[y[p[i]]];
    }
}
void solve4(int o1, int o2, int o3, int l, int r){
    for(int i=l-1; i<=r; ++i){
        x[i]=s[o1][i]-s[o2][i];
        z[i]=s[o2][i];
        ans-=t1.get(x[i]-1)*z[i]-t2.get(x[i]-1);
        t1.add(x[i], 1); t2.add(x[i], z[i]);
    }
    for(int i=l-1; i<=r; ++i){
        t1.add(x[i], -1); t2.add(x[i], -z[i]);
    }
    for(int i=l-1; i<=r; ++i){
        x[i]=s[o2][i]-s[o1][i];
        z[i]=s[o1][i];
        ans-=t1.get(x[i])*z[i]-t2.get(x[i]);
        t1.add(x[i], 1); t2.add(x[i], z[i]);
    }
    for(int i=l-1; i<=r; ++i){
        t1.add(x[i], -1); t2.add(x[i], -z[i]);
    }
}
ll calc2(int r){
    return 1ll*r*(r+1)/2;
}
ll calc3(int r){
    return 1ll*r*(r+1)*(2ll*r+1)/6ll;
}
int main(){
    scanf("%d", &n);
    scanf("%s", str+1);
    for(int i=1; i<=n; ++i){
        for(int j=0; j<3; ++j) s[j][i]=s[j][i-1];
        if(str[i]=='a') s[0][i]++;
        if(str[i]=='b') s[1][i]++;
        if(str[i]=='c') s[2][i]++;
    }
    solve(0, 1, 2);
    solve(1, 0, 2);
    solve(0, 2, 1);
    solve(2, 0, 1);
    solve(1, 2, 0);
    solve(2, 1, 0);
    solve2(0, 1, 2);
    solve2(0, 2, 1);
    solve2(1, 2, 0);
    solve3(2, 0, 1);
    solve3(1, 0, 2);
    solve3(0, 1, 2);
    assert(ans%2==0);
    ans/=2;
    for(int l=0, r=0; l<=n; ){
        r=l+1;
        while(r<=n&&str[r]!='c') ++r;
        if(l+1<=r-1) solve4(0, 1, 2, l+1, r-1);
        l=r;
    }
    for(int l=0, r=0; l<=n; ){
        r=l+1;
        while(r<=n&&str[r]!='b') ++r;
        if(l+1<=r-1) solve4(0, 2, 1, l+1, r-1);
        l=r;
    }
    for(int l=0, r=0; l<=n; ){
        r=l+1;
        while(r<=n&&str[r]!='a') ++r;
        if(l+1<=r-1) solve4(1, 2, 0, l+1, r-1);
        l=r;
    }
    for(int l=1, r=1; l<=n; l=r){
        while(r<=n&&str[r]==str[l]) ++r;
        int len=r-l;
        ans-=calc2(len)*(len+1);
        ans+=calc3(len);
    }
    printf("%lld\n", ans);
    return 0;
}

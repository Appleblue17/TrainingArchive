#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int n, m;
int c[N];
typedef pair<int, int> pii;
#define fi first
#define se second
typedef long long ll;
vector<pii> e[N];
int sz[N], tag[N];
ll sum[N];
pair<ll, ll> d[N];
ll gcd(ll x, ll y){
    if(x==0&&y==0) return 0;
    return __gcd(x, y);
}
void dfs(int x, int fa){
    for(auto edg:e[x]){
        int y=edg.fi, z=edg.se;
        if(y==fa) continue;
        dfs(y, x);
        sum[x]+=sum[y]+1ll*sz[y]*z;
        if(!sz[y]) continue;
        if(sz[x]){
            d[x].se=gcd(gcd(abs(d[y].fi+z-d[x].fi), d[y].se), d[x].se); 
        }
        else{
            d[x].se=gcd(d[y].se, d[x].se); 
        }
        sz[x]+=sz[y];
        d[x].fi=d[y].fi+z;
    }
    sz[x]+=tag[x];
    if(tag[x]) d[x].se=gcd(d[x].fi, d[x].se), d[x].fi=0;
}
int sz2[N];
ll sum2[N];
pair<ll, ll> pre[N], suf[N], d2[N];
void dfs2(int x, int fa){
    sz2[x]+=tag[x];
    ll sum_sum=0, sum_mul=0;
    vector<pii> vec;
    for(auto edg:e[x]){
        int y=edg.fi, z=edg.se;
        if(y==fa) continue;
        sum_sum+=sum[y];
        sum_mul+=1ll*sz[y]*z;
        vec.emplace_back(y, z);
    }
    pre[0]=suf[vec.size()+1]=d2[x];
    for(int i=1; i<=(int)vec.size(); ++i){
        int y=vec[i-1].fi, z=vec[i-1].se;
        if(!sz[y]) {
            pre[i]=pre[i-1];
            continue;
        }
        pre[i].fi=d[y].fi+z;
        pre[i].se=gcd(gcd(abs(d[y].fi+z-pre[i-1].fi), d[y].se), pre[i-1].se); 
        if(tag[x]) pre[i].se=gcd(pre[i].se, pre[i].fi), pre[i].fi=0;
    }
    for(int i=(int)vec.size(); i>=1; --i){
        int y=vec[i-1].fi, z=vec[i-1].se;
        if(!sz[y]) {
            suf[i]=suf[i+1];
            continue;
        }
        suf[i].fi=d[y].fi+z;
        suf[i].se=gcd(gcd(abs(d[y].fi+z-suf[i+1].fi), d[y].se), suf[i+1].se); 
        if(tag[x]) suf[i].se=gcd(suf[i].se, suf[i].fi), suf[i].fi=0;
    }
    for(int i=1; i<=(int)vec.size(); ++i){
        int y=vec[i-1].fi, z=vec[i-1].se;
        d2[y].fi=pre[i-1].fi+z;
        d2[y].se=gcd(gcd(pre[i-1].se, suf[i+1].se), abs(pre[i-1].fi-suf[i+1].fi));
        if(tag[y]) d2[y].se=gcd(d2[y].se, d2[y].fi), d2[y].fi=0;
    }
    for(auto edg:vec){
        int y=edg.fi, z=edg.se;
        sum2[y]=sum2[x]+sum_sum-sum[y]+sum_mul-1ll*sz[y]*z+1ll*(m-sz[y])*z;
    }
    for(auto edg:vec) dfs2(edg.fi, x);
}
int main(){
	// freopen("D:\\nya\\acm\\A\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\A\\test2.out","w",stdout);
    scanf("%d%d", &n, &m);
    for(int i=1; i<=m; ++i) scanf("%d", &c[i]), tag[c[i]]=1;
    for(int i=1, x, y, z; i<n; ++i){
        scanf("%d%d%d", &x, &y, &z);
        e[x].emplace_back(y, z); e[y].emplace_back(x, z);
    }
    if(m==1){
        printf("0\n");
        return 0;
    }
    dfs(c[1], 0);
    dfs2(c[1], 0);
    ll ans=1e18;
    for(int i=1; i<=n; ++i){
        ll tot=sum[i]+sum2[i];
        ll temd=gcd(gcd(d[i].se, d2[i].se), gcd(d[i].fi, d2[i].fi));
        // cout<<tot<<' '<<temd<<' '<<d[i].se<<' '<<d2[i].se<<' '<<d[i].fi<<' '<<d2[i].fi<<endl;
        ans=min(ans, tot/temd);
    }
    printf("%lld\n", ans*2);
}

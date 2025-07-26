#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef long long ll;
const int N=3e5+5;
int n;
char s[N];
int m;
vector<int> e[N];
ll ans=0;
ll f[N][3][3];//x, self, parent
inline bool ckmax(ll &x, ll y){
    if(y>x) {x=y; return true;}
    return false;
}
inline ll cal(ll x){
    return (x/2)*((x+1)/2);
}
inline ll cal2(ll x){
    return x*(x-1);
}
inline void dfs(int x, int fa){
    bool isleaf=1;
    for(auto y:e[x]) if(y^fa){
        dfs(y, x);
        isleaf=0;
    }
    if(isleaf) return ;
    if(x==1){
        for(int o=0; o<3; ++o){//self
            vector<ll> vec;
            for(auto y:e[x]) if(y^fa) {
                vec.push_back(f[y][1][o]-f[y][0][o]);
            }
            sort(vec.begin(), vec.end(), greater<ll>());
            ll sum=0; int cnt=0;
            for(auto y:e[x]) if(y^fa) ++cnt, sum+=f[y][0][o];
            if(o!=1) ckmax(ans, sum);
            else{
                ll cur=sum+cal(cnt);
                ckmax(ans, cur);
            }
            for(auto v:vec){
                sum+=v; --cnt;
                if(o!=1) ckmax(ans, sum);
                else{
                    ll cur=sum+cal(cnt);
                    ckmax(ans, cur);
                }
            }
        }
        return ;
    }
    for(int o=0; o<3; ++o){//self
        vector<ll> vec;
        for(auto y:e[x]) if(y^fa) {
            vec.push_back(f[y][1][o]-f[y][0][o]);
        }
        sort(vec.begin(), vec.end(), greater<ll>());
        for(int p=0; p<3; ++p){//parent
            ll sum=0; int cnt=0;
            for(auto y:e[x]) if(y^fa) ++cnt, sum+=f[y][0][o];
            if(o!=1) {
                ckmax(f[x][o][p], sum);
            }
            else{
                ll cur=sum+cal(cnt+(p!=1));
                ckmax(f[x][o][p], cur);
            }
            for(auto v:vec){
                sum+=v; --cnt;
                if(o!=1) {
                    ckmax(f[x][o][p], sum);
                }
                else{
                    ll cur=sum+cal(cnt+(p!=1));
                    ckmax(f[x][o][p], cur);
                }
            }
        }
    }
    // for(int o=0; o<3; ++o) for(int p=0; p<3; ++p){
    //     printf("%d %d %d %d\n", x, o, p, f[x][o][p]);
    // }
}

inline void dfs2(int x, int fa){
    bool isleaf=1;
    for(auto y:e[x]) if(y^fa){
        dfs2(y, x);
        isleaf=0;
    }
    if(isleaf) return ;
    if(x==1){
        for(int o=0; o<2; ++o){//self
            vector<ll> vec;
            for(auto y:e[x]) if(y^fa) {
                vec.push_back(f[y][1][o]-f[y][0][o]);
            }
            sort(vec.begin(), vec.end(), greater<ll>());
            ll sum=0; int cnt=0;
            for(auto y:e[x]) if(y^fa) ++cnt, sum+=f[y][0][o];
            if(o!=1) ckmax(ans, sum);
            else{
                ll cur=sum+cal2(cnt);
                ckmax(ans, cur);
            }
            for(auto v:vec){
                sum+=v; --cnt;
                if(o!=1) ckmax(ans, sum);
                else{
                    ll cur=sum+cal2(cnt);
                    ckmax(ans, cur);
                }
            }
        }
        return ;
    }
    for(int o=0; o<2; ++o){//self
        vector<ll> vec;
        for(auto y:e[x]) if(y^fa) {
            vec.push_back(f[y][1][o]-f[y][0][o]);
        }
        sort(vec.begin(), vec.end(), greater<ll>());
        for(int p=0; p<2; ++p){//parent
            ll sum=0; int cnt=0;
            for(auto y:e[x]) if(y^fa) ++cnt, sum+=f[y][0][o];
            if(o!=1) {
                ckmax(f[x][o][p], sum);
            }
            else{
                ll cur=sum+cal2(cnt+(p!=1));
                ckmax(f[x][o][p], cur);
            }
            for(auto v:vec){
                sum+=v; --cnt;
                if(o!=1) {
                    ckmax(f[x][o][p], sum);
                }
                else{
                    ll cur=sum+cal2(cnt+(p!=1));
                    ckmax(f[x][o][p], cur);
                }
            }
        }
    }
    // for(int o=0; o<3; ++o) for(int p=0; p<3; ++p){
    //     printf("%d %d %d %d\n", x, o, p, f[x][o][p]);
    // }
}


inline void dfs3(int x, int fa){
    bool isleaf=1;
    for(auto y:e[x]) if(y^fa){
        dfs3(y, x);
        isleaf=0;
    }
    if(isleaf) return ;
    if(x==1){
        for(int o=0; o<2; ++o){//self
            vector<ll> vec;
            for(auto y:e[x]) if(y^fa) {
                vec.push_back(f[y][1][o]-f[y][0][o]);
            }
            sort(vec.begin(), vec.end(), greater<ll>());
            ll sum=0; int cnt=0;
            for(auto y:e[x]) if(y^fa) ++cnt, sum+=f[y][0][o];
            if(o!=1) ckmax(ans, sum);
            else{
                ll cur=sum+1ll*(cnt)*(vec.size()-cnt);
                ckmax(ans, cur);
            }
            for(auto v:vec){
                sum+=v; --cnt;
                if(o!=1) ckmax(ans, sum);
                else{
                    ll cur=sum+1ll*(cnt)*(vec.size()-cnt);
                    ckmax(ans, cur);
                }
            }
        }
        return ;
    }
    for(int o=0; o<2; ++o){//self
        vector<ll> vec;
        for(auto y:e[x]) if(y^fa) {
            vec.push_back(f[y][1][o]-f[y][0][o]);
        }
        sort(vec.begin(), vec.end(), greater<ll>());
        for(int p=0; p<2; ++p){//parent
            ll sum=0; int cnt=0;
            for(auto y:e[x]) if(y^fa) ++cnt, sum+=f[y][0][o];
            if(o!=1) {
                ckmax(f[x][o][p], sum);
            }
            else{
                ll cur=sum+1ll*(cnt+(p==0))*(vec.size()-cnt+(p==1));
                ckmax(f[x][o][p], cur);
            }
            for(auto v:vec){
                sum+=v; --cnt;
                if(o!=1) {
                    ckmax(f[x][o][p], sum);
                }
                else{
                    ll cur=sum+1ll*(cnt+(p==0))*(vec.size()-cnt+(p==1));
                    ckmax(f[x][o][p], cur);
                }
            }
        }
    }
    // for(int o=0; o<3; ++o) for(int p=0; p<3; ++p){
    //     printf("%d %d %d %d\n", x, o, p, f[x][o][p]);
    // }
}
signed main(){
	// freopen("D:\\nya\\acm\\A\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\A\\test.out","w",stdout);
    scanf("%lld", &n);
    scanf("%s", s+1);
    m=strlen(s+1);
    if(m==1){
        printf("%lld\n", n);
        return 0;
    }
    if(m==2){
        if(s[1]==s[2]) printf("%lld\n", 2ll*(n-1));
        else printf("%lld\n", n-1);
        return 0;
    }
    for(int i=1, x, y; i<n; ++i){
        scanf("%lld%lld", &x, &y);
        e[x].push_back(y); e[y].push_back(x);
    }
    if(s[1]!=s[2]&&s[2]!=s[3]&&s[1]!=s[3]) dfs(1, 0);
    else if(s[1]==s[3]&&s[1]==s[2]){
        for(int i=1; i<=n; ++i) ans+=1ll*e[i].size()*(e[i].size()-1);
    }
    else if(s[1]==s[3]&&s[1]!=s[2]) dfs2(1, 0);
    else dfs3(1, 0);
    printf("%lld\n", ans);
}

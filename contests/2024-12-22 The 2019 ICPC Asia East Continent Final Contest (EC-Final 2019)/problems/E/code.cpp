#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5, M=1e7;
typedef long long ll;
int n, m;
typedef pair<int, int> pii;
#define fi first
#define se second
#define mapa make_pair
vector<pii> e[N];
vector<int> b[N];
int tot=0;
#define ep emplace_back
int main(){
    scanf("%d%d", &n, &m);
    ll sum=0;
    for(int i=1, x, y, z; i<=m; ++i){
        scanf("%d%d%d", &x, &y, &z);
        e[x].emplace_back(y, z);
        sum+=z;
    }
    for(auto t:e[1]){
        ++tot;
        b[tot].ep(t.se);
        int x=t.fi;
        while(x!=n) {
            b[tot].ep(e[x][0].se);
            x=e[x][0].fi;
        }
    }
    sum/=m/tot;
    // cout<<sum<<endl;
    priority_queue<pii> pq;
    for(int i=1; i<=tot; ++i){
        sort(b[i].begin(), b[i].end());
        sum-=b[i][0];
        for(int j=1; j<(int)b[i].size(); ++j){
            if(b[i][j]!=b[i][j-1]){
                pq.push(mapa(-j, b[i][j]-b[i][j-1]));
            }
        }
    }
    ll ans=0;
    while(sum){
        pii cur=pq.top(); pq.pop();
        ans+=(-1ll*cur.fi)*min((ll)cur.se, sum);
        sum-=min((ll)cur.se, sum);
    }
    printf("%lld\n", ans);
}

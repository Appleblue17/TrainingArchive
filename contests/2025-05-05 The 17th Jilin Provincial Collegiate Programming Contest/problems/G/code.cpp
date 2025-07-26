#include <bits/stdc++.h>
using namespace std;
// #define int long long
const int N=4e5+5;
int T, n;
int lp[N], rp[N], yp[N];
int id[N];
inline bool cmp(int x, int y){
    if(lp[x]!=lp[y]) return lp[x]<lp[y];
    else return x<y;
}
typedef pair<int, int> pii;
#define fi first
#define se second
#define mapa make_pair
void solve(){
    scanf("%d", &n);
    for(int i=1; i<=n; ++i){
        scanf("%d%d%d", &lp[i], &rp[i], &yp[i]); id[i]=i;
        ++lp[i]; --rp[i];
    }
    sort(id+1, id+n+1, cmp);
    int sx, sy;
    scanf("%d%d", &sx, &sy);
    int it=1;
    priority_queue<pii, vector<pii>, greater<pii> > pq;
    set<pii> st;
    st.insert(mapa(0, 0));
    while(sy!=0){
        while(it<=n&&lp[id[it]]<=sx){
            pq.push(mapa(rp[id[it]], it));
            st.insert(mapa(yp[id[it]], it));
            ++it;
        }
        while(!pq.empty()&&pq.top().fi<sx){
            int iit=pq.top().se; pq.pop();
            st.erase(st.find(mapa(yp[id[iit]], iit)));
        }
        set<pii>::iterator p=st.upper_bound(mapa(sy, -1));
        --p;
        sy=(*p).fi;
        if(sy!=0) sx=rp[id[(*p).se]]+1;
    }
    printf("%d\n", sx);
}
signed main() {
    scanf("%d", &T);
    while(T--){
        solve();
    }
}

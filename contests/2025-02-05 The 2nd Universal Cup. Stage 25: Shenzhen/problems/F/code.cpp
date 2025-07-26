#include <bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n;
vector<int> e[N];
int deg[N], w[N];
bool vis[N];
int cnt[N];
unordered_map<long long, bool> h;
multiset<int> st;
int main(){
    cin>>n;
    for(int i=1, x, y; i<=n; ++i){
        cin>>x>>y;
        ++deg[x]; ++deg[y];
        e[x].emplace_back(y); e[y].emplace_back(x);
    }
    for(int i=1; i<=n; ++i) w[i]=deg[i], cnt[w[i]]++, st.insert(w[i]);
    queue<int> que;
    for(int i=1; i<=n; ++i) if(deg[i]==1) que.push(i), vis[i]=1;
    while(!que.empty()){
        int x=que.front(); que.pop();
        for(int y:e[x]) if(!vis[y]){
            --deg[y];
            if(deg[y]==1){
                vis[y]=1;
                que.push(y);
            }
        }
    }
    vector<pair<int, int> > edge;
    for(int i=1; i<=n; ++i) if(!vis[i]){
        for(int j:e[i]) if(!vis[j]){
            int x=min(i, j), y=max(i, j);
            if(h.find(1ll*x*(n+10)+y)==h.end()){
                edge.emplace_back(x, y);
                h[1ll*x*(n+10)+y]=1;
            }
        }
    }
    long long ans=0;
    for(auto edg:edge){
        int x=edg.first, y=edg.second;
        st.erase(st.find(w[x]));
        st.insert(w[x]-1);
        --cnt[w[x]]; ++cnt[w[x]-1];
        st.erase(st.find(w[y]));
        st.insert(w[y]-1);
        --cnt[w[y]]; ++cnt[w[y]-1];
        if(*(st.rbegin())<=4){
            ans+=n-cnt[4];
        }
        st.erase(st.find(w[x]-1));
        st.insert(w[x]);
        ++cnt[w[x]]; --cnt[w[x]-1];
        st.erase(st.find(w[y]-1));
        st.insert(w[y]);
        ++cnt[w[y]]; --cnt[w[y]-1]; 
    }
    cout<<ans<<endl;
}

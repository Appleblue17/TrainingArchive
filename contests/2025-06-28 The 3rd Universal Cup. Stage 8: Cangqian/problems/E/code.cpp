#include <bits/stdc++.h>
using namespace std;
const int N=66,INF=1e9;
int n,ans=-INF;
int w[N];
vector <int> R[N];

int pat[N];

priority_queue <int> q;
bool check(){
    while(q.size()) q.pop();
    
    for(int i=1;i<=n;i++){
        for(int r: R[i]) q.push(-r);
        for(int j=1;j<=pat[i]*i;j++){
            if(!q.size()) return 0;
            int x=-q.top(); q.pop();
            if(x<i) return 0;
        }
    }
    return 1;
}

int cnt;
void dfs(int cur,int sum,int val){
    if(sum==n){
        cnt++;
        // for(int i=1;i<=n;i++) cout<<pat[i]<<" ";
        // cout<<endl;
        // cout<<"  "<<check()<<endl;
        if(check()) ans=max(ans,val);
        return ;
    }
    for(int i=cur;i<=n-sum;i++){
        for(int j=1;j<=(n-sum)/cur;j++){
            pat[i]=j;
            dfs(i+1,sum+i*j,val+w[i]*j);
        }
        pat[i]=0;
    }
}


signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        int l,r; cin>>l>>r;
        R[l].push_back(r);
    }
    for(int i=1;i<=n;i++) cin>>w[i];
    dfs(1,0,0);
    
    if(ans==-INF) puts("impossible");
    else cout<<ans;
}

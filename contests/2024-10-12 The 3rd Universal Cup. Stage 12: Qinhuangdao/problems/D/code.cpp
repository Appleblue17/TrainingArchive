#pragma GCC optimize(2)
#include<bits/stdc++.h>
using namespace std;
// #define int long long
const int N=2e5+5,INF=1e9;
int T,n,m;
unordered_map <int, bool> G[N];
int in[N],col[N];
vector <int> ANS[N];
int p[N],id;

priority_queue < pair<int,int> > q;


signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>T;
	
	while(T--){
		cin>>n>>m;
		id=0;
		for(int i=1;i<=n;i++) G[i].clear(),ANS[i].clear();
		for(int i=1;i<=n;i++) in[i]=col[i]=0;
		while(q.size()) q.pop();
		
		for(int i=1;i<=m;i++){
			int u,v; cin>>u>>v;
			G[u][v]=G[v][u]=true;
			in[u]++,in[v]++;
		}
		
		for(int i=1;i<=n;i++) q.push(make_pair(in[i],i));
		bool fl=1;
		while(q.size() && fl){
			int u=q.top().second; q.pop();
			p[++id]=u;
			ANS[col[u]].push_back(u);
			
			for(auto tmp: G[u]){
				int v=tmp.first;
				if(col[u]!=col[v]){
					fl=0;
					break;
				}
				G[v].erase(G[v].find(u));
				col[v]=u;
			}
			
		}
		
		
		if(fl){
			cout<<"Yes"<<endl;
			for(int i=id;i>=1;i--){
				int u=p[i];
				cout<<u<<" ";
				cout<<ANS[u].size()<<" ";
				for(int t: ANS[u]) cout<<t<<" ";
				cout<<endl;
			}
		}
		else{
			cout<<"No"<<endl;
		}
	}
	
}

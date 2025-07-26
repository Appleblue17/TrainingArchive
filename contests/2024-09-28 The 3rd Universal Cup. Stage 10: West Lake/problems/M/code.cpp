#pragma GCC optimize(2)
#include<bits/stdc++.h>
using namespace std;
#define MP make_pair
//#define int long long
const int N=1e6+5,INF=2e9+100;
int T_,n,m,k;
int A[N],B[N];
bool vis[N];

vector <int> COL[N];
vector < pair<int,int> > G[N];
int cur[N],id;
unordered_map < long long, int > mp;
void add(int u,int v,int w,int c){
	if(!mp[1ll*u*(m+1)+c]){
		mp[1ll*u*(m+1)+c]=++id;
		G[id].clear();
	}
	int num=mp[1ll*u*(m+1)+c];
	G[num].push_back(MP(w,v));
}

int getnum(int u,int c){
	if(!mp.count(1ll*u*(m+1)+c)) return 0;
	return mp[1ll*u*(m+1)+c];
}


priority_queue < pair<int,int> > que[N];
void upd(int u){
	sort(COL[u].begin(),COL[u].end());
	int siz=unique(COL[u].begin(),COL[u].end())-COL[u].begin();
	for(int t=0;t<siz;t++){
		int c=COL[u][t],num=getnum(u,c);
		if(cur[num]==(int)G[num].size()) continue;
		que[c].push(MP(-G[num][cur[num]].first,u));
	}
}

int dis[N];
priority_queue < pair<int,int> > q;

signed main(){
//	freopen("1.txt","r",stdin);
//	freopen("2.txt","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>T_;
	while(T_--){
		cin>>n>>m>>k;
		id=0;
		for(int i=1;i<=n;i++) vis[i]=0,dis[i]=INF,COL[i].clear();
		for(int i=1;i<=m;i++){
			while(que[i].size()) que[i].pop();
		}
		mp.clear();
		
		
		for(int i=1;i<=m;i++){
			int u,v,c,w;
			cin>>u>>v>>c>>w;
			add(u,v,w,c);
			add(v,u,w,c);
			COL[u].push_back(c);
			COL[v].push_back(c);
		}
//		return 0;
		for(int i=1;i<=id;i++) sort(G[i].begin(),G[i].end());
		for(int i=1;i<=id;i++) cur[i]=0;
		
		for(int i=1;i<=k;i++) cin>>A[i]>>B[i];
		vis[1]=1;
		upd(1);
		
		for(int i=1;i<=k;i++){
//			cout<<"round "<<i<<": "<<endl;
			int c=A[i],d=B[i];
			while(que[c].size()){
				pair<int,int> tmp=que[c].top();
				
				int u=tmp.second,w=-tmp.first;
				if(w>d) break;
				que[c].pop();
				
				int num=getnum(u,c);
				int v=G[num][cur[num]].second;
				if(!vis[v]){
					dis[v]=min(dis[v],w);
					q.push(MP(-w,v));
//					cout<<"  "<<"add "<<u<<" "<<v<<" "<<w<<endl;
				}
				
				cur[num]++;
				if(cur[num]<(int)G[num].size()){
					que[c].push(MP(-G[num][cur[num]].first,u));
				}
			}
			
			while(q.size()){
				int u=q.top().second; q.pop();
				if(vis[u]) continue;
				vis[u]=1;
				
				int num=getnum(u,c);
				if(!num) continue;
				for(int t=cur[num];t<(int)G[num].size();t++){
					int w=G[num][t].first,v=G[num][t].second;
					if(dis[u]+w>d) break;
					cur[num]++;
					
					if(!vis[v] && dis[u]+w<dis[v]){
						dis[v]=dis[u]+w;
						q.push(MP(-dis[v],v));
					}
				}
				upd(u);
			}
			
//			for(int i=1;i<=n;i++) cout<<vis[i];
//			cout<<endl;
		}
		
//		cout<<endl;
		for(int i=1;i<=n;i++) cout<<vis[i];
		cout<<endl;
	}
} 

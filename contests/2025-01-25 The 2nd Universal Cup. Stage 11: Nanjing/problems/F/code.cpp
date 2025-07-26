#include<bits/stdc++.h>
using namespace std;
const int N = 1000010;
int t,n,m;
int a[N],b[N],in[N];
vector<int> col[N];
vector<int> g[N];
bool f=0;
vector<int> L;
deque<int> S;
void toposort(){
    f=0;
	L.clear();
    S.clear();
	for (int i = 1; i <= n; i++)
		if (in[i] == 0){
            S.push_back(i);
            //printf("s push %d\n",i);
        }
	while(!S.empty()){
        //printf("size = %d\n",S.size());
        if(S.size()>=2){
            f=1;
        }
        int u;
        if(S.front() > S.back()){
            u = S.front();
	    	S.pop_front();
        }
        else{
            u = S.back();
            S.pop_back();
        }
		L.push_back(u);
		for (auto v : g[u]) {
			if (--in[v] == 0) {
				S.push_back(v);
			}
		}
	}
    //printf("L.size = %d\n",L.size());
	if(f){
        printf("Yes\n");
        for(int i=0;i<n-1;i++){
            printf("%d ",L[i]);
        }
        printf("%d\n",L[n-1]);
    }
    else{
        printf("No\n");
    }
}
void solve(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=max(n,m);i++){
        col[i].clear();g[i].clear();
    }
    for(int i=1;i<=max(n,m);i++){
        in[i]=0;
    }
    for(int i=1;i<=n;i++){
        int x,y;
        scanf("%d",&x);
        for(int j=1;j<=x;j++){
            scanf("%d",&y);
            col[y].push_back(i);
        }
    }
    for(int i=1;i<=m;i++){
        if(!col[i].size())continue;
        for(int j=0;j<col[i].size()-1;j++){
            g[col[i][j]].push_back(col[i][col[i].size()-1]);
            in[col[i][col[i].size()-1]]++;
            //printf("g[%d].push_back(%d)\n",col[i][j],col[i][col[i].size()-1]);
        }
    }
    toposort();
}
int main(){
    cin >> t;
    while(t--){
        solve();
    }
}

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double dou;
typedef pair<int,int> pii;
#define fi first
#define se second
#define mapa make_pair
typedef long double ld;
typedef unsigned long long ull;
#define ep emplace_back
template <typename T>inline void read(T &x){
	x=0;char c=getchar();bool f=0;
	for(;c<'0'||c>'9';c=getchar()) f|=(c=='-');
	for(;c>='0'&&c<='9';c=getchar())
	x=(x<<1)+(x<<3)+(c^48);
	x=(f?-x:x);
}
const int N=1e6+5;
int T, n, m;
char s[N];
int tr[N][2], tr2[N][2], idx;
int id[N], cnt[N], id2[N], cnt2[N], id3[N], cnt3[N]; 
bool flag[N]; int fail[N];
void insert(int o){
	int len=strlen(s+1), p=0;
	for(int i=1, c; i<=len; ++i){
		c=s[i]-'0';
		if(!tr[p][c]) tr[p][c]=++idx;
		p=tr[p][c];
	}
	if(o==-1){
		flag[p]=1;
	}
	else{
		id3[p]=o; cnt3[p]++;
	}
}
int lin[N], nxt[N], to[N], tot;
void in(int x, int y){
	nxt[++tot]=lin[x]; lin[x]=tot; to[tot]=y;
}
int stk[N], top;
bool ins[N];
int dfn[N], tim, low[N], scc[N], scccnt;
vector<int> e[N], e2[N];
int deg[N], deg2[N];
void build(){
	queue<int> q;
	for(int i=0; i<2; ++i) if(tr[0][i]) q.push(tr[0][i]);
	while(!q.empty()){
		int x=q.front(); q.pop();
		e2[fail[x]].ep(x); ++deg2[x];
		for(int i=0; i<2; ++i){
			int &c=tr[x][i];
			if(!c){
				c=tr[fail[x]][i];
			}
			else{
				e2[x].ep(c); ++deg2[c];
				fail[c]=tr[fail[x]][i];
				q.push(c);
			}
		}
	}
	q.push(0);
	while(!q.empty()){
		int x=q.front(); q.pop();
		if(cnt3[x]>=2||cnt2[x]>=2){
			cnt3[x]=2;
		}
		else if(cnt3[x]==1&&cnt2[x]==1&&id3[x]!=id2[x]){
			cnt3[x]=2;
		}
		else{
			cnt3[x]+=cnt2[x];
			id3[x]|=id2[x];
		}
		cnt2[x]=id2[x]=0;
		for(auto y:e2[x]){
			if(cnt3[x]>=2){
				cnt2[y]=2;
			}
			else if(cnt2[y]==0){
				cnt2[y]=cnt3[x];
				id2[y]=id3[x];
			}
			else if(cnt2[y]==1&&cnt3[x]==1){
				if(id3[x]!=id2[y]){
					cnt2[y]=2;
				}
			}
			flag[y]|=flag[x];
			if(!--deg2[y]){
				q.push(y);
			}
		}
	}
}
void ddfs(int x){
	for(int i=0; i<2; ++i) if(tr[x][i]){
		cout<<x<<' '<<tr[x][i]<<' '<<i<<endl;
		ddfs(tr[x][i]);
	}
}
inline void tarjan(int x){
	low[x]=dfn[x]=++tim;
	stk[++top]=x; ins[x]=true;
	for(int i=lin[x]; i; i=nxt[i]){
		int y=to[i];
		if(!dfn[y]) tarjan(y), low[x]=min(low[x], low[y]);
		else if(ins[y]) low[x]=min(low[x], dfn[y]);
	}
	if(low[x]==dfn[x]){
		scccnt++;
		do{
			scc[x]=scccnt;
			x=stk[top--]; ins[x]=false;
		}while(low[x]!=dfn[x]);
	}
}
void build2(){
	for(int i=0; i<=idx; ++i) if(!flag[i]){
		for(int j=0; j<2; ++j){
			if(i!=tr[i][j]&&!flag[tr[i][j]]){
				in(i, tr[i][j]);
			}
		}
	}
	for(int i=0; i<=idx; ++i) if(!dfn[i]&&!flag[i]) tarjan(i);
	for(int i=0; i<=idx; ++i) if(!flag[i]){
		if(cnt3[i]>=2){
			cnt[scc[i]]=2;
		}
		else if(cnt[scc[i]]==0){
			cnt[scc[i]]=cnt3[i];
			id[scc[i]]=id3[i];
		}
		else if(cnt[scc[i]]==1&&cnt3[i]==1){
			if(id[scc[i]]!=id3[i]){
				cnt[scc[i]]=2;
			}
		}
		for(int j=0; j<2; ++j){
			if(i!=tr[i][j]&&!flag[tr[i][j]]){
				if(scc[i]!=scc[tr[i][j]]) e[scc[i]].ep(scc[tr[i][j]]), ++deg[scc[tr[i][j]]];
			}
		}
	}
}
void solve(){
	for(int i=0; i<=tot; ++i) nxt[i]=to[i]=0;
	tot=1; tim=0; scccnt=0;
	for(int i=0; i<=idx; ++i){
		for(int j=0; j<2; ++j) tr[i][j]=0;
		e[i].clear(); e2[i].clear();
		fail[i]=0;
		cnt[i]=cnt2[i]=cnt3[i]=0;
		id[i]=id2[i]=id3[i]=0;
		flag[i]=0;
		deg[i]=deg2[i]=0;
		lin[i]=0;
		dfn[i]=0;
	}
	idx=0;
	read(n); read(m);
	for(int i=1; i<=n; ++i){
		scanf("%s", s+1);
		insert(i); 
	}
	for(int i=1; i<=m; ++i){
		scanf("%s", s+1);
		insert(-1); 
	}
	build();
	build2();
	queue<int> q;
	for(int i=1; i<=scccnt; ++i) if(!deg[i]) q.push(i);
	while(!q.empty()){
		int x=q.front(); q.pop();
		if(cnt[x]>=2){
			printf("Yes\n");
			return ;
		}
		if(cnt[x]==1&&cnt2[x]>=2){
			printf("Yes\n");
			return ;
		}
		if(cnt[x]==1&&cnt2[x]==1&&id[x]!=id2[x]){
			printf("Yes\n");
			return ;
		}
		if(cnt[x]==0){
			cnt[x]=cnt2[x];
			id[x]=id2[x];
		}
		else if(cnt[x]==1&&cnt2[x]==1){
			if(id[x]!=id2[x]) cnt[x]=2;
		}
		for(auto y:e[x]){
			if(cnt[x]>=2){
				cnt2[y]=2;
			}
			else if(cnt2[y]==0){
				cnt2[y]=cnt[x];
				id2[y]=id[x];
			}
			else if(cnt2[y]==1&&cnt[x]==1){
				if(id[x]!=id2[y]){
					cnt2[y]=2;
				}
			}
			if(!--deg[y]){
				q.push(y);
			}
		}
	}
	printf("No\n");
}
int main(){
	// freopen("D:\\nya\\acm\\A\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\A\\test.out","w",stdout);
	read(T);
	while(T--){
		solve();
	}
	return 0;
}

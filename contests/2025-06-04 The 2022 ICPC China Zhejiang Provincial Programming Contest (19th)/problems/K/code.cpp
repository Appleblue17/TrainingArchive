#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
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
typedef unsigned __int128 lint;
#define ep emplace_back
template <typename T>inline void read(T &x){
	x=0;char c=getchar();bool f=0;
	for(;c<'0'||c>'9';c=getchar()) f|=(c=='-');
	for(;c>='0'&&c<='9';c=getchar())
	x=(x<<1)+(x<<3)+(c^48);
	x=(f?-x:x);
}
const int N=2e5+5;
const int B=64;
int n, m, q;
int fx[N], fy[N];
vector<pii> e[N]; lint e2[N];
int tp[N], qu[N], qv[N];
bool ban[N], sp[N];
lint val[N]; 
lint f[N];
int deg[N];
int stk[N], top; bool ins[N];
int dfn[N], tim, low[N], scc[N], scccnt;
vector<int> e3[N];
inline void tarjan(int x){
	low[x]=dfn[x]=++tim;
	stk[++top]=x; ins[x]=true;
	for(auto edg:e[x]){
		if(sp[edg.se]||ban[edg.se]) continue;
		int y=edg.fi;
		if(!dfn[y]) tarjan(y), low[x]=min(low[x], low[y]);
		else if(ins[y]) low[x]=min(low[x], dfn[y]);
	}
	if(low[x]==dfn[x]){
		scccnt++;
		f[scccnt]=val[scccnt]=e2[scccnt]=0; deg[scccnt]=0; e3[scccnt].clear();
		do{
			scc[x]=scccnt;
			x=stk[top--]; ins[x]=false;
		}while(low[x]!=dfn[x]);
	}
}
lint pw[N];
int main(){
	// freopen("D:\\nya\\acm\\A\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\A\\test.out","w",stdout);
	read(n); read(m); read(q);
	pw[0]=1;
	for(int i=1; i<=128; ++i) pw[i]=pw[i-1]+pw[i-1];
	for(int i=1; i<=m; ++i){
		read(fx[i]); read(fy[i]);
		e[fx[i]].ep(fy[i], i);
	}
	for(int i=1; i<=q; ++i){
		read(tp[i]);
		if(tp[i]==2) read(qu[i]), read(qv[i]);
		else read(qu[i]);
	}
	for(int i=1; i<=q; i+=B){
		vector<int> vec;
		for(int j=i; j<i+B&&j<=q; ++j){
			if(tp[j]==2) vec.ep(qu[j]), vec.ep(qv[j]);
			else vec.ep(fx[qu[j]]), vec.ep(fy[qu[j]]), sp[qu[j]]=1;
		}
		top=tim=scccnt=0;
		for(int x=1; x<=n; ++x) dfn[x]=low[x]=stk[x]=0, ins[x]=0;
		for(int x=1; x<=n; ++x) if(!dfn[x]) tarjan(x);
		vector<int> vid;
		for(auto t:vec) vid.ep(scc[t]);
		sort(vid.begin(), vid.end());
		vid.erase(unique(vid.begin(), vid.end()), vid.end());
		for(int j=0; j<(int)vid.size(); ++j){
			val[vid[j]]=pw[j]; f[vid[j]]=pw[j];
		}
		for(int x=1; x<=n; ++x){
			for(auto edg:e[x]){
				if(sp[edg.se]||ban[edg.se]) continue;
				if(scc[x]!=scc[edg.fi]){
					++deg[scc[edg.fi]];
					e3[scc[x]].ep(scc[edg.fi]);
				}
			}
		}
		queue<int> que;
		for(int x=1; x<=scccnt; ++x) if(deg[x]==0) que.push(x);
		while(!que.empty()){
			int x=que.front(); que.pop();
			for(auto y:e3[x]){
				f[y]|=f[x];
				if(!--deg[y]){
					que.push(y);
				}
			}
		}
		for(int j=i; j<i+B&&j<=q; ++j){
			if(tp[j]==1) sp[qu[j]]=0;
		}
		for(int j=i; j<i+B&&j<=q; ++j){
			if(tp[j]==1) continue;
			if(f[scc[qv[j]]]&val[scc[qu[j]]]){
				printf("YES\n");
				continue;
			}
			for(auto t:vid) e2[t]=0;
			for(int p=0; p<(int)vid.size(); ++p){
				for(int q=0; q<(int)vid.size(); ++q){
					if((f[vid[p]]>>q)&1){
						e2[vid[q]]|=pw[p];
					}
				} 
			}
			vector<int> eid;
			for(int k=i; k<i+B&&k<=q; ++k){
				if(tp[k]==1) {
					eid.ep(qu[k]);
					if(k<j) sp[qu[k]]^=1;
				}
			}
			sort(eid.begin(), eid.end());
			eid.erase(unique(eid.begin(), eid.end()), eid.end());
			for(auto t:eid) if(sp[t]^ban[t]^1){
				if(scc[fx[t]]!=scc[fy[t]]) e2[scc[fx[t]]]|=val[scc[fy[t]]]; 
			}
			lint vis=0;
			for(int p=0; p<(int)vid.size(); ++p) {
				if(vid[p]!=scc[qu[j]]) vis|=pw[p];
			}
			que.push(scc[qu[j]]);
			while(!que.empty()){
				int x=que.front(); que.pop();
				lint tem=vis&e2[x];
				while(tem){
					int t=0;
					if(tem&(pw[64]-1)){
						t=__builtin_ctzll((ull)(tem&(pw[64]-1)));
					}
					else{
						t=64+__builtin_ctzll((ull)(tem/pw[64]));
					}
					vis^=pw[t];
					tem^=pw[t];
					que.push(vid[t]);
				}
			}
			if(vis&val[scc[qv[j]]]){
				printf("NO\n");
			}
			else{
				printf("YES\n");
			}
			for(auto t:eid) sp[t]=0;
		}
		for(int j=i; j<i+B&&j<=q; ++j){
			if(tp[j]==1) ban[qu[j]]^=1;
		}
	}
	return 0;
}

//喜欢卡路径压缩并查集的出生们，你们好，我是雷军
//tmd，老子起来早八打UCUP，被你一道交互硬控一小时
//霓虹人也许不过春节，不过盂兰盆节马上就要到了
//你要是还想穿和服和家人参加晚会，就不要卡tmd路径压缩并查集
//否则我就远程遥控小米su7，出口到东京创死你 
#pragma GCC optimize(3)
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
const int N=50005;
int n;
int fa[N], fb[N];
vector<int> ba[N], bb[N];
inline void ma(int x, int y){
	if(ba[x].size()<ba[y].size()) swap(x, y);
	for(auto t:ba[y]) fa[t]=x, ba[x].ep(t);
}
inline void mb(int x, int y){
	if(bb[x].size()<bb[y].size()) swap(x, y);
	for(auto t:bb[y]) fb[t]=x, bb[x].ep(t);
}
char str[2];
vector<pii> va, vb;
int main(){
//	 freopen("D:\\nya\\acm\\A\\test.in","r",stdin);
//	 freopen("D:\\nya\\acm\\A\\test.out","w",stdout);
	scanf("%d", &n);
	for(int i=1; i<=n; ++i) fa[i]=fb[i]=i, ba[i].ep(i), bb[i].ep(i);
	for(int i=2; i<=n; ++i){
		for(int j=1; j<i; ++j){
			if((fa[i]^fa[j])&&(fb[i]^fb[j])){
				printf("? %d %d\n", i, j);
				fflush(stdout);
				scanf("%s", str);
				if(str[0]=='R'){
					ma(fa[i], fa[j]);
					va.ep(i, j);
					if((int)va.size()==n-1){
						printf("!\n");
						for(auto t:va) printf("%d %d\n", t.fi, t.se);
						return 0;
					}
				}
				else{
					mb(fb[i], fb[j]);
					vb.ep(i, j);
					if((int)vb.size()==n-1){
						printf("!\n");
						for(auto t:vb) printf("%d %d\n", t.fi, t.se);
						return 0;
					}
				}
			}
		}
	}
	return 0;
}

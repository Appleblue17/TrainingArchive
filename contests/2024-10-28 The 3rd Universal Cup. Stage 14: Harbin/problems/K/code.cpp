#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double dou;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
#define fi first
#define se second
#define MAXN 1000010
#define mapa make_pair
typedef long double ld;
typedef unsigned long long ull;
typedef pair<ull,ull> puu;
//mt19937_64 rng(GetTickCount());
template <typename T>inline void read(T &x){
	x=0;char c=getchar();bool f=0;
	for(;c<'0'||c>'9';c=getchar()) f|=(c=='-');
	for(;c>='0'&&c<='9';c=getchar())
	x=(x<<1)+(x<<3)+(c^48);
	x=(f?-x:x);
}
const int mo=1e9+7;
using namespace std;
ll w[MAXN],l[MAXN],r[MAXN],id[MAXN],pre[MAXN],suf[MAXN],pans[MAXN],sans[MAXN];
ll t,n,m,x,y,ans,k;
bool cmp(int a,int b){
	return w[a]>w[b];
}
ll su(int x,int del){
	if(x > del)return suf[x];
	else return suf[x]-l[id[del]];
}
ll pr(int x,int del){
	if(x < del)return pre[x];
	else return m+1;
}
ll san(int x,int del){
	if(x > del)return sans[x];
	else return sans[x]-l[id[del]]*w[id[del]];
}
/*ll pan(int x,int del){
	if(x < del)return pans[x];
	else return pans[del-1]+w[id[del]]*
}*/

int main(){
	ans=0;
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%lld%lld%lld",&w[i],&l[i],&r[i]);
		id[i]=i;
	}
	sort(id+1,id+n+1,cmp);
	for(int i=1;i<=n;i++){
		pre[i]=pre[i-1]+r[id[i]];
		pans[i]=pans[i-1]+r[id[i]]*w[id[i]];
	}
	suf[n+1]=0;
	for(int i=n;i>=1;i--){
		suf[i]=suf[i+1]+l[id[i]];
		sans[i]=sans[i+1]+l[id[i]]*w[id[i]];
	}
	for(int i=1;i<=n;i++){
		int le=0,ri=n,mi=(le+ri)/2;
		while(le<ri){//找出第一个mid，使得[1,mi],[mi+1,m]小于等于m,即：如果等于，则算 
			if(pr(mi,i)+su(mi+1,i) <= m)le = mi;
			else ri = mi-1;
			mi = (le+ri+1)/2;
		}
		//printf("%lld")
		//if(mi < i){
		//	ans = max(ans,pans[mi]+san(mi+1,i));
		//}
		//else{//直接拉满 
		//	//mi==i is true
		//printf("after i=%d is deleted, mi=%d,pans=%lld,san=%lld,giving mi %lld*%lld\n",i,mi,pans[mi],san(mi+2,i),(m-pre[mi]-suf[mi+2]),w[id[i]]);
		//if(mi+1 == i)
		//else ans = max(ans,pans[mi]+san(mi+1,i));
		ans = max(ans,pans[mi]+san(mi+2,i)+(m-pre[mi]-su(mi+2,i))*w[id[mi+1]]);
		//}
	}
	printf("%lld\n",ans);
}

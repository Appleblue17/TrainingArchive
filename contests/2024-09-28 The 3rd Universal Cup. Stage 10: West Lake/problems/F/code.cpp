#pragma GCC optimize(2)
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
template <typename T>inline void read(T &x){
	x=0;char c=getchar();bool f=0;
	for(;c<'0'||c>'9';c=getchar()) f|=(c=='-');
	for(;c>='0'&&c<='9';c=getchar())
	x=(x<<1)+(x<<3)+(c^48);
	x=(f?-x:x);
}
const int N=3e5+5;
const ull bs=137;
ull pw[1000006];
int Test, n;
char s[1000006];
int id[N], sz[N];
vector<char> str[N];
vector<ull> hs[N];
inline bool cmp(int x, int y){
	int l=1, r=min(sz[x], sz[y]), res=0, mid;
	while(l<=r){
		mid=(l+r)>>1;
		if(hs[x][mid]==hs[y][mid]) {res=mid; l=mid+1;}
		else r=mid-1;
	}
	if(res==min(sz[x], sz[y])) return sz[x]>sz[y];
	return str[x][res+1]>str[y][res+1];
}
vector<int> bd[N];
int pre[N], sam[N];
inline ull get(int id, int l, int r){
	return hs[id][r]-hs[id][l-1]*pw[r-l+1];
}
inline bool chk(int id, int lp, int rp, int cur){
	int l=1, r=min(rp-lp+1, sz[cur]), res=0, mid;
	while(l<=r){
		mid=(l+r)>>1;
		if(get(id, lp, lp+mid-1)==hs[cur][mid]) {res=mid; l=mid+1;}
		else r=mid-1;
	}
	if(res==min(rp-lp+1, sz[cur])) return rp-lp+1<sz[cur];
	return str[id][lp+res]<str[cur][res+1];
}
inline ll calc(int l, int r){
	if(l>r) return 0;
	return (ll)(l+r)*(r-l+1)/2ll;
}
inline ll calc2(int l, int r){
	if(l>r) return 0;
	return (ll)r*(r+1)*(2*r+1)/6ll-(ll)(l-1)*l*(2*l-1)/6ll;
}
int main(){
//	freopen("test.in","r",stdin);
//	freopen("test.out","w",stdout);
	read(Test);
	pw[0]=1;
	for(int i=1; i<=1000000; ++i) pw[i]=pw[i-1]*bs;
	while(Test--){
		read(n);
		for(int i=1; i<=n; ++i){
			scanf("%s", s+1); sz[i]=strlen(s+1);
			hs[i].resize(sz[i]+1); str[i].resize(sz[i]+1); bd[i].resize(sz[i]+2);
			hs[i][0]=0;
			for(int j=1; j<=sz[i]; ++j) hs[i][j]=hs[i][j-1]*bs+s[j], str[i][j]=s[j];
			id[i]=i;
		}
		sort(id+1, id+n+1, cmp);
		ll ans=0;
		for(int l=1, r; l<=n; l=r+1){
			r=l;
			while(r+1<=n&&sz[id[r+1]]==sz[id[l]]&&hs[id[l]][sz[id[l]]]==hs[id[r+1]][sz[id[r+1]]]) ++r;
			pre[r]=l-1;
			sam[r]=r-l+1;
			for(int i=l-1; i>=1; i=pre[i]){
				if(sz[id[i]]<sz[id[l]]) break;
				if(hs[id[i]][sz[id[l]]]!=hs[id[l]][sz[id[l]]]) break;
				ans+=(ll)sam[i]*calc(max(0, bd[id[i]][sz[id[l]]+1]-r), max(0, bd[id[i]][sz[id[l]]+1]-l));
				for(int j=min(bd[id[i]][sz[id[l]]+1], l-1); j>i; j=pre[j]){
					if(sz[id[i]]<sz[id[j]]) {
						ans+=(ll)sam[i]*sam[j]*sam[r]; 
						continue;
					}
					if(hs[id[i]][sz[id[j]]]!=hs[id[j]][sz[id[j]]]) {
						ans+=(ll)sam[i]*sam[j]*sam[r];
						continue;
					}
					if(bd[id[i]][sz[id[j]]+1]<l){
						ans+=(ll)sam[i]*sam[j]*sam[r];
					}
				}
			}
			ans-=calc2(l, r);
			ans-=(ll)sam[r]*l*n;
			ans+=calc(l, r)*(n+l);
			bd[id[r]][sz[id[r]]+1]=n;
			for(int i=sz[id[r]]; i>=1; --i){
				int lp=r+1, rp=n, res=l-1, mid;
				while(lp<=rp){
					mid=(lp+rp)>>1;
					if(chk(id[r], i, sz[id[r]], id[mid])) {res=mid; lp=mid+1;}
					else rp=mid-1;
				}
				bd[id[r]][i]=res;
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}

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
#define ep emplace_back
template <typename T>inline void read(T &x){
	x=0;char c=getchar();bool f=0;
	for(;c<'0'||c>'9';c=getchar()) f|=(c=='-');
	for(;c>='0'&&c<='9';c=getchar())
	x=(x<<1)+(x<<3)+(c^48);
	x=(f?-x:x);
}
const int N=2e5+5;
int B, n, m;
char s[N], t[N];
int x[N],y[N],c[N],sa[N],ht[N],rk[N];
void get_sa(){
	for(int i=1;i<=n;i++) c[x[i]=s[i]]++;
	int m='z';
	for(int i=2;i<=m;i++) c[i]+=c[i-1];
	for(int i=n;i;i--) sa[c[x[i]]--]=i;
	for(int k=1;k<=n;k<<=1){
		int num=0;
		for(int i=n-k+1;i<=n;i++) y[++num]=i;
		for(int i=1;i<=n;i++){
			if(sa[i]>k) y[++num]=sa[i]-k;
		}
		for(int i=1;i<=m;i++) c[i]=0;
		for(int i=1;i<=n;i++) c[x[i]]++;
		for(int i=2;i<=m;i++) c[i]+=c[i-1];
		for(int i=n;i;i--) sa[c[x[y[i]]]--]=y[i],y[i]=0;
		swap(x,y);
		x[sa[1]]=1;num=1;
		for(int i=2;i<=n;i++)
		x[sa[i]]=(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k])?num:++num;
		if(num==n) break;
		m=num;
	}
}
void get_ht(){
	for(int i=1; i<=n; ++i) rk[sa[i]]=i;
	for(int i=1, k=0; i<=n; ++i){
		if(rk[i]==1) continue;
		if(k) k--;
		int j=sa[rk[i]-1];
		while(i+k<=n&&j+k<=n&&s[i+k]==s[j+k]) k++;
		ht[rk[i]]=k;
	}
}
int st[N][20], lg[N];
void build(){
	for(int i=2; i<=n; ++i) lg[i]=lg[i>>1]+1;
	for(int i=1; i<=n; ++i) st[i][0]=ht[i];
	for(int t=1; t<=lg[n]; ++t){
		for(int i=1; i+(1<<t)-1<=n; ++i){
			st[i][t]=min(st[i][t-1], st[i+(1<<(t-1))][t-1]);
		}
	}
}
inline int lcp(int x, int y){
    if(x>n||y>n+m+1) return 0;
	x=rk[x]; y=rk[y];
	if(x>y) swap(x, y);
	++x;
	int t=lg[y-x+1];
	return min(st[x][t], st[y-(1<<t)+1][t]);
}
int f[35][65];
int eps=32;
int ans[35];
int dp[N];
int main(){
	// freopen("D:\\nya\\acm\\A\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\A\\test.out","w",stdout);
	read(B);
    scanf("%s", s+1); n=strlen(s+1);
    scanf("%s", t+1); m=strlen(t+1);
    s[n+1]='&';
    for(int i=1; i<=m; ++i) s[n+1+i]=t[i];
    n+=m+1;
	get_sa();
	get_ht();
	build();
    n-=m+1;
    for(int st=1; st<=m; ++st){
        memset(f, -0x3f, sizeof f);
        f[0][eps]=0;
        for(int i=0; i<=B; ++i){
            for(int j=-B; j<=B; ++j) if(f[i][j+eps]>=0){
                f[i][j+eps]=min(f[i][j+eps], n);
                f[i][j+eps]+=lcp(f[i][j+eps]+1, n+1+st+f[i][j+eps]+j);
                f[i+1][j+eps]=max(f[i+1][j+eps], f[i][j+eps]+1);
                f[i+1][j+1+eps]=max(f[i+1][j+1+eps], f[i][j+eps]);
                f[i+1][j-1+eps]=max(f[i+1][j-1+eps], f[i][j+eps]+1);
            }
        }
        for(int i=max(st, st+n-B-1); i-1<=st+n+B-1&&i-1<=m; ++i) dp[i]=B+1;
        for(int i=0; i<=B; ++i){
            for(int j=-B; j<=B; ++j) if(f[i][j+eps]==n){
                int cur=st+n+j-1;
                if(cur<st||cur>m) continue;
                dp[cur]=min(dp[cur], i);
            }
        }
        for(int i=min(st+n+B-1, m); i>=st+n-B-1&&i>=st; --i) {
            dp[i]=min(dp[i], dp[i+1]+1);
            ++ans[dp[i]];
        }
        // for(int i=0; i<=B; ++i) printf("%lld ", ans[i]); putchar('\n');
    }
    for(int i=0; i<=B; ++i) printf("%d\n", ans[i]);
	return 0;
}


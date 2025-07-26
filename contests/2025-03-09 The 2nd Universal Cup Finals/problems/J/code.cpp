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
char s[N], t[N];
int f[N];
int p[N];
void solve(){
	scanf("%s", s+1);
	scanf("%s", t+1);
	n=strlen(s+1);
	m=strlen(t+1);
	for(int i=1; i<=n; ++i) p[i]=p[i-1]+(s[i]=='1'?1:-1);
	vector<pii> v;
	for(int l=1, r; l<=m; l=r+1){
		r=l;
		while(r+1<=m&&t[r+1]==t[l]) ++r;
		v.ep(r-l+1, t[l]-'0');
	}
	if(v.size()==1){
		if(!(v.back().se==1&&p[n]>=v.back().fi)&&!(v.back().se==0&&p[n]<=-v.back().fi)){
			printf("No\n");
			return ;
		}
	}
	f[0]=0;
	f[1]=-1;
	for(int j=1; j<=n; ++j){
		int num=v[0].fi, col=v[0].se;
		if(col==1&&p[j]>=num) {f[1]=j; break;}
		else if(col==0&&p[j]<=-num) {f[1]=j; break;}
	}
	if(f[1]==-1){
		printf("No\n");
		return ;
	}
	for(int i=2; i<(int)v.size(); ++i){
		int num=v[i-1].fi, col=v[i-1].se;
		int mn=f[i-1];
		int j=f[i-1]+1;
		while(j<=n){
			if(col==1&&p[j]-p[mn]>=num) {
				break;
			}
			if(col==0&&p[j]-p[mn]<=-num) {
				break;
			}
			if(col==1&&p[j]<p[mn]) mn=j;
			else if(col==0&&p[j]>p[mn]) mn=j;
			++j;
		}
		if(j>n) {
			printf("No\n");
			return ;
		}
		f[i]=j;
		f[i-1]=mn;
	}
	int mn=f[v.size()-1];
	for(int j=f[v.size()-1]+1; j<n; ++j) if((v.back().se==1&&p[mn]>p[j])||(v.back().se==0&&p[mn]<p[j])) mn=j;
	if(v.back().se==1&&p[n]-p[mn]>=v.back().fi) f[v.size()]=n;
	else if(v.back().se==0&&p[n]-p[mn]<=-v.back().fi) f[v.size()]=n;
	else{
		printf("No\n");
		return ;
	}
	f[v.size()-1]=mn;
	printf("Yes\n");
	int it=0;
	for(int i=1; i<=(int)v.size(); ++i){
		int col=v[i-1].se, num=v[i-1].fi;
		int sum=0;
		while(num>1){
			++it; sum+=(s[it]=='1'?1:-1);
			if(sum>0&&col==1) putchar('1'), --num, sum=0;
			else if(sum<0&&col==0) putchar('1'), --num, sum=0;
			else putchar('0');
		}
		while(it<f[i]-1) putchar('0'), ++it;
		putchar('1'); ++it;
	}
	putchar('\n');
}
int main(){
	// freopen("D:\\nya\\acm\\A\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\A\\test.out","w",stdout);
	read(T);
	while(T--) solve();
	return 0;
}


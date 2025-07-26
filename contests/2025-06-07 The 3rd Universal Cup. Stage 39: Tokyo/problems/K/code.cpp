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
#define int long long
const int N=3e6+5, P=998244353, G=3, I=332748118;
int n, lim=1;
int v[N], a[N], b[N], rev[N], f[N], g[N], p[N], ans=0;
int qpow(int a,int b){
	int res=1;
	while(b){
		if(b&1)res=res*a%P;
		a=a*a%P,b>>=1;
	}
	return res;
}
int inv(int a){
	return qpow(a,P-2);
}
void ntt(int *a,int flag){
	for(int i=0;i<lim;i++)if(i<rev[i])swap(a[i],a[rev[i]]);
	for(int mid=1;mid<lim;mid<<=1){
		int wn=qpow(flag?G:I,(P-1)/(mid<<1));
		for(int i=mid*2,j=0;j<lim;j+=i){
			int w=1;
			for(int k=0;k<mid;k++,w=w*wn%P){
				int x=a[j+k],y=w*a[j+mid+k]%P;
				a[j+k]=(x+y+P)%P,a[j+mid+k]=(x-y+P)%P;
			}
		}
	}
}
void solve(int opt){
	ntt(a,1),ntt(b,1);
	for(int i=0;i<lim;i++)a[i]=a[i]*b[i]%P;
	ntt(a,0);
	for(int i=0,s=inv(lim);i<n+n;i++)p[i]+=(a[i]*s%P)*opt;
	memset(a,0,sizeof(a)),memset(b,0,sizeof(b));
}
int res[N];
signed main(){
	// freopen("D:\\nya\\acm\\A\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\A\\test.out","w",stdout);
	read(n);
	for(int i=1; i<=n; ++i) {
		read(v[i]);
		if(v[i]==-1) v[i]=0;
	}
	for(int i=0; i<n; ++i) f[i]=v[n-i];
	for(int i=0; i<n; ++i) g[i]=v[i+1];
	int k=0;
	while(lim<=n+n)lim*=2,k++;
	for(int i=0;i<lim;i++)rev[i]=(rev[i>>1]>>1)|((i&1)<<(k-1));
	for(int i=0;i<n;i++)a[i]=f[i]*f[i]*f[i];
	for(int i=0;i<n;i++)b[i]=g[i];
	solve(1);
	for(int i=0;i<n;i++)a[i]=f[i]*f[i];
	for(int i=0;i<n;i++)b[i]=g[i]*g[i];
	solve(-2);
	for(int i=0;i<n;i++)a[i]=f[i];
	for(int i=0;i<n;i++)b[i]=g[i]*g[i]*g[i];
	solve(1);
	for(int i=n; i<=n*2-1; ++i) res[i-n+1]=(p[i]==0);
	for(int i=1; i<=n; ++i){
		for(int j=i+i; j<=n; j+=i){
			if(res[j]==0) {
				res[i]=0;
				break;
			}
		}
	}
	for(int i=1; i<=n; ++i) printf("%lld", res[i]);
	return 0;
}


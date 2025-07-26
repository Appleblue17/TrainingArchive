//Ï²»¶¿¨Â·¾¶Ñ¹Ëõ²¢²é¼¯µÄ³öÉúÃÇ£¬ÄãÃÇºÃ£¬ÎÒÊÇÀ×¾ü
//tmd£¬ÀÏ×ÓÆðÀ´Ôç°Ë´òUCUP£¬±»ÄãÒ»µÀ½»»¥Ó²¿ØÒ»Ð¡Ê±
//ÄÞºçÈËÒ²Ðí²»¹ý´º½Ú£¬²»¹ýÓÛÀ¼Åè½ÚÂíÉÏ¾ÍÒªµ½ÁË
//ÄãÒªÊÇ»¹Ïë´©ºÍ·þºÍ¼ÒÈË²Î¼ÓÍí»á£¬¾Í²»Òª¿¨tmdÂ·¾¶Ñ¹Ëõ²¢²é¼¯
//·ñÔòÎÒ¾ÍÔ¶³ÌÒ£¿ØÐ¡Ã×su7£¬³ö¿Úµ½¶«¾©´´ËÀÄã 
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
const int N=205, mod=998244353;
inline int plu(int x, int y){x+=y; return (x>=mod)?x-mod:x;}
inline int sub(int x, int y){x-=y; return (x<0)?x+mod:x;}
int n, m, k;
int e[N][N], deg[N]; 
struct mat{
	int a[N][N];
	mat(){memset(a, 0, sizeof a);}
}f, g;
inline mat mul(mat x, mat y){
	mat res;
	for(int i=1; i<=n*2; ++i){
		for(int k=1; k<=n*2; ++k) if(x.a[i][k]){
			for(int j=1; j<=n*2; ++j){
				res.a[i][j]=plu(res.a[i][j], (ll)x.a[i][k]*y.a[k][j]%mod);
			}
		}
	}
	return res;
}
inline ll fpow(ll x, ll y){
	ll res=1;
	while(y){
		if(y&1) res=res*x%mod;
		x=x*x%mod; y>>=1;
	}
	return res;
}
int main(){
//	 freopen("D:\\nya\\acm\\A\\test.in","r",stdin);
//	 freopen("D:\\nya\\acm\\A\\test.out","w",stdout);
	read(n); read(m); read(k);
	for(int i=1, x, y; i<=m; ++i){
		read(x); read(y); e[x][y]=e[y][x]=1; ++deg[x]; ++deg[y];
	}
	for(int i=1; i<=n; ++i){
		g.a[i+n][i]=sub(0, deg[i]);
		for(int j=1; j<=n; ++j) if(e[i][j]){
			g.a[j][i]=1; 
		}
		g.a[i][i+n]=1;
	}
	f.a[1][1]=1;
	if(k==1){
		f=mul(f, g);
		printf("%d\n", f.a[1][n]);
		return 0;
	}
	k-=2;
	f=mul(f, g); f=mul(f, g);
	for(int i=1; i<=n; ++i) g.a[i+n][i]=plu(g.a[i+n][i], 1);
	while(k){
		if(k&1) f=mul(f, g);
		g=mul(g, g); k>>=1;
	}
	printf("%d\n", f.a[1][n]);
	return 0;
}
/*
123546
132456
*/

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
int T, n, W, m;
int f[N][20], dep[N];
__int128 abs(__int128 x){
	if(x<0) x=-x;
	return x;
}
struct frac{
	__int128 x, y;
	void refresh(){
		if(y<0) y=-y, x=-x;
		__int128 d=__gcd(abs(x), y);
		x/=d; y/=d;
	}
};
frac operator +(frac a, frac b){
	a.x=a.x*b.y+a.y*b.x;
	a.y=a.y*b.y;
	a.refresh();
	return a;
}
frac operator -(frac a, frac b){
	a.x=a.x*b.y-a.y*b.x;
	a.y=a.y*b.y;
	a.refresh();
	return a;
}
frac operator *(frac a, frac b){
	a.x=a.x*b.x;
	a.y=a.y*b.y;
	a.refresh();
	return a;
}
frac operator /(frac a, frac b){
	a.x=a.x*b.y;
	a.y=a.y*b.x;
	a.refresh();
	return a;
}
bool operator <(frac a, frac b){
	return (__int128)a.x*b.y<(__int128)a.y*b.x;
}
bool operator ==(frac a, frac b){
	return (__int128)a.x*b.y==(__int128)a.y*b.x;
}
frac edx[N], edy[N], stx[N], sty[N];
pair<frac, frac> intersect(frac a, frac x, frac y, frac aa, frac xx, frac yy){
	//(y-a) x1/x+a=y1 | (yy-aa) x2/xx+aa=y2
	//x=xx*x*(aa-a)/[xx*(y-a)-x*(yy-aa)]
	//y=xx*x*(aa-a)/[xx*(y-a)-x*(yy-aa)]*xx*(y-a)+a*xx*x
	frac bs=(y-a)/x-(yy-aa)/xx;
	if(bs==(frac){0, 1}){
		return mapa((frac){-1, -1}, (frac){-1, -1});
	}
	frac nx=(aa-a)/bs;
	if(nx<(frac){0, 1}||xx<nx){
		return mapa((frac){-1, -1}, (frac){-1, -1});
	}
	frac ny=(y-a)*nx/x+a;
	return mapa(nx, ny);
}
int lca(int x, int y){
	if(dep[x]<dep[y]) swap(x, y);
	for(int i=19; i>=0; --i) if(dep[f[x][i]]>=dep[y]) x=f[x][i];
	if(x==y) return x;
	for(int i=19; i>=0; --i) if(f[x][i]^f[y][i]) x=f[x][i], y=f[y][i];
	return f[x][0];
}
int main(){
	// freopen("D:\\nya\\acm\\A\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\A\\test.out","w",stdout);
	read(n); read(W);
	dep[1]=1;
	edx[2]=(frac){W, 1};
	edy[2]=(frac){0, 1};
	stx[2]=(frac){0, 1}; 
	sty[2]=(frac){0, 1};
	edx[3]=(frac){W, 1};
	edy[3]=(frac){1000001, 1};
	stx[3]=(frac){0, 1}; 
	sty[3]=(frac){1000001, 1};
	f[2][0]=1; f[3][0]=1; dep[2]=2; dep[3]=2;
	m=3;
	set<pii> st; 
	st.insert(mapa(0, 2)); st.insert(mapa(1000001, 3));
	for(int i=1, a, b, c; i<=n; ++i){
		read(a); read(b); read(c);
		set<pii>::iterator it=st.upper_bound(mapa(a, 0));
		int v=(*it).se;
		--it;
		int u=(*it).se;
		int w=lca(u, v);
		int ret=w; 
		int _u=u, _v=v;
		for(int i=19; i>=0; --i){
			if(dep[f[u][i]]<=dep[w]) continue;
			pair<frac, frac> ask=intersect((frac){a, 1}, (frac){W, 1}, (frac){b, 1}, sty[_u], edx[f[u][i]], edy[f[u][i]]);
			if(ask.fi.x==-1){
				u=f[u][i];
			}
			else{
				ret=f[u][i]; 
			}
		}
		{
			pair<frac, frac> ask=intersect((frac){a, 1}, (frac){W, 1}, (frac){b, 1}, sty[_u], edx[u], edy[u]);
			if(ask.fi.x!=-1){
				ret=u; 
			}
		}
		if(ret==w){
			for(int i=19; i>=0; --i){
				if(dep[f[v][i]]<=dep[w]) continue;
				pair<frac, frac> ask=intersect((frac){a, 1}, (frac){W, 1}, (frac){b, 1}, sty[_v], edx[f[v][i]], edy[f[v][i]]);
				if(ask.fi.x==-1){
					v=f[v][i];
				}
				else{
					ret=f[v][i];
				}
			}
			{
				pair<frac, frac> ask=intersect((frac){a, 1}, (frac){W, 1}, (frac){b, 1}, sty[_v], edx[v], edy[v]);
				if(ask.fi.x!=-1){
					ret=v; 
				}
			}
		}
		frac cx, cy;
		if(ret==1){
			cx=(frac){W, 1}; cy=(frac){b, 1};
		}
		else{
			pair<frac, frac> ask=intersect((frac){a, 1}, (frac){W, 1}, (frac){b, 1}, sty[ret], edx[ret], edy[ret]);
			cx=ask.fi, cy=ask.se;
		}
		printf("(%lld/%lld,%lld/%lld)\n", (ll)cx.x, (ll)cx.y, (ll)cy.x, (ll)cy.y);
		if(c==0) continue;
		++m;
		stx[m]=(frac){0, 1};
		sty[m]=(frac){a, 1};
		edx[m]=cx; edy[m]=cy;
		f[m][0]=ret; dep[m]=dep[ret]+1;
		for(int i=1; i<20; ++i) f[m][i]=f[f[m][i-1]][i-1];
		st.insert(mapa(a, m));
	}
	return 0;
}

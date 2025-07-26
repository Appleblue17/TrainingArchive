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
template <typename T>inline void read(T &x){
	x=0;char c=getchar();bool f=0;
	for(;c<'0'||c>'9';c=getchar()) f|=(c=='-');
	for(;c>='0'&&c<='9';c=getchar())
	x=(x<<1)+(x<<3)+(c^48);
	x=(f?-x:x);
}
#define ep emplace_back
const int N=1e5+5;
int Test, n;
struct point{
    int x, y;
}a[N]; 
inline bool check(point a, point b, point c){
    return (ll)(b.x-a.x)*(c.y-a.y)<(ll)(b.y-a.y)*(c.x-a.x);
}
inline bool cmp(point a, point b){return (a.x==b.x)?a.y<b.y:a.x<b.x;}
int stk[N], top;
vector<point> res;
bool vis[N];
inline vector<point> getc(vector<point> p){
	res.clear();
	if(p.size()<=3) {
		return p;
	}
	sort(p.begin(), p.end(), cmp);
    for(int i=0; i<(int)p.size(); ++i) vis[i]=0;
    top=0;
    for(int i=0; i<(int)p.size(); ++i){
        while(top>1&&check(p[stk[top-1]], p[stk[top]], p[i])) top--;
        stk[++top]=i;
    }
    vector<point> ret;
    for(int i=1; i<top; ++i) vis[stk[i]]=1, ret.push_back(p[stk[i]]);
    top=0;
	for(int i=(int)p.size()-1; i>=0; --i){
        while(top>1&&check(p[stk[top-1]], p[stk[top]], p[i])) top--;
        stk[++top]=i;
    }
    for(int i=1; i<top; ++i) vis[stk[i]]=1, ret.push_back(p[stk[i]]);
    for(int i=0; i<(int)p.size(); ++i) {
    	if(!vis[i]) res.push_back(p[i]);
	}
	return ret;
}
inline ll cross(point x, point y){
	return (ll)x.x*y.y-(ll)x.y*y.x;
}
inline ll tran(point x, point y, point z){
	return cross(x, y)+cross(y, z)+cross(z, x);
}
inline int add(int x, int all){
	if(x==all-1) x=0;
	else ++x;
	return x;
}
inline int del(int x, int all){
	if(x==0) x=all-1;
	else --x;
	return x;
}
int main(){
	// freopen("D:\\nya\\test.in","r",stdin);
	// freopen("D:\\nya\\test.out","w",stdout);
	read(Test);
	while(Test--){
		read(n);
		vector<point> pnt;
		for(int i=1; i<=n; ++i) read(a[i].x), read(a[i].y), pnt.push_back(a[i]);
		vector<point> c1=getc(pnt);
		if((int)c1.size()==n){
			printf("-1\n");
			continue;
		}
		vector<point> c2=getc(res);
		c1.push_back(c1[0]);
		ll all=0;
		for(int i=0; i<(int)c1.size()-1; ++i) all+=cross(c1[i], c1[i+1]);
		int mnpos=-1; ll mnsz=6e18;
		ll mnans=6e18;
		for(int j=0; j<(int)c2.size(); ++j){
			if(tran(c1[0], c1[1], c2[j])<=mnsz){
				mnsz=tran(c1[0], c1[1], c2[j]); mnpos=j;
			}
		}
		for(int i=0; i<(int)c1.size()-1; ++i) mnans=min(mnans, tran(c1[i], c1[i+1], c2[mnpos]));
		int cur=mnpos;
		for(int i=0; i<(int)c1.size()-1; ++i){
			while(add(cur, c2.size())!=mnpos&&tran(c1[i], c1[i+1], c2[cur])>=tran(c1[i], c1[i+1], c2[add(cur, c2.size())])) {
				cur=add(cur, c2.size());
			}
			mnans=min(mnans, tran(c1[i], c1[i+1], c2[cur]));
		}
		cur=mnpos;
		for(int i=0; i<(int)c1.size()-1; ++i){
			while(del(cur, c2.size())!=mnpos&&tran(c1[i], c1[i+1], c2[cur])>=tran(c1[i], c1[i+1], c2[del(cur, c2.size())])) {
				cur=del(cur, c2.size());
			}
			mnans=min(mnans, tran(c1[i], c1[i+1], c2[cur]));
		}
		printf("%lld\n", all-mnans);
	}
	return 0;
}

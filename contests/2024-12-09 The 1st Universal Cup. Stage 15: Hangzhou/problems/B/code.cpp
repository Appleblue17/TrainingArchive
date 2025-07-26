#pragma GCC optimize(3)
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double dou;
typedef pair<int,int> pii;
#define fi first
#define se second
#define mapa make_pair
typedef unsigned long long ull;
#define ep emplace_back
template <typename T>inline void read(T &x){
	x=0;char c=getchar();bool f=0;
	for(;c<'0'||c>'9';c=getchar()) f|=(c=='-');
	for(;c>='0'&&c<='9';c=getchar())
	x=(x<<1)+(x<<3)+(c^48);
	x=(f?-x:x);
}
const int N=25;
int n;
dou X[N], Y[N];
#define dc deque<char>
#define vd vector<dou>
map<vd, dc> h2[10];
inline void ins(int x, dc tem, vd tem2){
	h2[x][tem2]=tem;
}
dou eps=0.00001, eps2=0.01;
inline void dfs(int x){
	if(!h2[x].empty()){
		return ;
	} 
	if(x==0) {
		dc tem;
		tem.push_back('x');
		vd tem2;
		for(int i=0; i<n; ++i) tem2.ep(X[i]);
		h2[0][tem2]=tem;
		return ;
	}
	dc tem; vd tem2;
	dfs(x-1);
	if(x==2){
		bool flag=1;
		for(int i=0; i<n; ++i) {
			if(fabsl(X[i])<eps2) {
				flag=0; break;
			}
		}
		if(flag){
			tem.clear();
			tem.push_back('(');
			tem.push_back('x');
			tem.push_back('/');
			tem.push_back('x');
			tem.push_back(')');
			tem2.clear();
			for(int i=0; i<n; ++i) tem2.push_back(1.0);
			ins(x, tem, tem2);
		}
		tem.clear();
		tem.push_back('(');
		tem.push_back('x');
		tem.push_back('-');
		tem.push_back('x');
		tem.push_back(')');
		tem2.clear();
		for(int i=0; i<n; ++i) tem2.push_back(0.0);
		ins(x, tem, tem2);
	}
	for(auto d:h2[x-1]){
		tem=d.se; tem2=d.fi;
		tem.push_front('(');
		tem.push_front('s');
		tem.push_back(')');
		for(auto &v:tem2) v=sin(v);
		ins(x, tem, tem2);
		tem=d.se; tem2=d.fi;
		tem.push_front('(');
		tem.push_front('c');
		tem.push_back(')');
		for(auto &v:tem2) v=cos(v);
		ins(x, tem, tem2);
	}
	for(int i=0; i+2<=x; ++i){
		dfs(i);
		dfs(x-i-2);
		for(auto d1:h2[i]){
			dc cur1=d1.se; vd nv=d1.fi;
			cur1.push_front('(');
			for(auto d2:h2[x-i-2]){
				dc cur2;
				if(d1.se!=d2.se){
					cur2=cur1; nv=d1.fi;
					cur2.push_back('-');
					for(int j=0; j<n; ++j) nv[j]-=d2.fi[j];
					for(auto e:d2.se) cur2.ep(e);
					cur2.push_back(')');
					ins(x, cur2, nv);
					bool flag=1;
					for(int i=0; i<n; ++i) {
						if(fabsl(d2.fi[i])<eps2) {
							flag=0; break;
						}
					}
					if(flag){
						cur2=cur1; nv=d1.fi;
						for(int j=0; j<n; ++j) nv[j]/=d2.fi[j];
						cur2.push_back('/');
						for(auto e:d2.se) cur2.ep(e);
						cur2.push_back(')');
						ins(x, cur2, nv);
					}
				}
				if(i<=x-i-2){
					cur2=cur1; nv=d1.fi;
					for(int j=0; j<n; ++j) nv[j]*=d2.fi[j];
					cur2.push_back('*');
					for(auto e:d2.se) cur2.ep(e);
					cur2.push_back(')');
					ins(x, cur2, nv);
					cur2=cur1; nv=d1.fi;
					for(int j=0; j<n; ++j) nv[j]+=d2.fi[j];
					cur2.push_back('+');
					for(auto e:d2.se) cur2.ep(e);
					cur2.push_back(')');
					ins(x, cur2, nv);
				}
			}
		}
	}
	for(auto t:h2[x]){
		vd val=t.fi;
		bool flag=1;
		for(int i=0; i<n; ++i) {
			if(fabs(val[i]-Y[i])/max((dou)1.0, fabsl(Y[i]))>eps) {
				flag=0;
				break;
			}
		}
		if(flag){
			for(auto e:t.se){
				if(e=='s') printf("sin");
				else if(e=='c') printf("cos");
				else putchar(e);
			}
			exit(0);
		}
	}
	return ;
}
int main(){
	// freopen("D:\\nya\\acm\\C\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\C\\test.out","w",stdout);
	read(n);
	for(int i=0; i<n; ++i){
		scanf("%LF%LF", &X[i], &Y[i]);
	}
	dfs(9);
	return 0;
}

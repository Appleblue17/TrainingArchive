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
const int N=1e5+5;
int n, m;
ll a[N];
ll st[20][N]; int lg[N];
inline ll get(int l, int r){
	if(l>r) return 0;
	if(l==r) return st[0][l];
	int t=lg[r-l+1];
	return __gcd(st[t][l], st[t][r-(1<<t)+1]);
}
inline ll get1(int l, int r){
	ll ans=0;
	for(int cl=l, cr; cl<r;){
		int lp=cl+1, rp=r-1, mid, ret=cl;
		ll curv=get(l, cl);
		while(lp<=rp){
			mid=(lp+rp)>>1;
			if(get(l, mid)==curv){
				ret=mid; lp=mid+1; 
			}
			else{
				rp=mid-1;
			}
		}
		cr=ret;
		ans=max(ans, __gcd(curv, get(cr+2, r)));
		cl=cr+1;
	}
	for(int cr=r, cl; cr>l;){
		int lp=l+1, rp=cr-1, mid, ret=cr;
		ll curv=get(cr, r);
		while(lp<=rp){
			mid=(lp+rp)>>1;
			if(get(mid, r)==curv){
				ret=mid; rp=mid-1; 
			}
			else{
				lp=mid+1;
			}
		}
		cl=ret;
		ans=max(ans, __gcd(curv, get(l, cl-2)));
		cr=cl-1;
	}
	return ans;
}
inline ll get2(int l, int r){
	ll ans=max(get1(l+1, r), get1(l, r-1));
	ans=max(ans, max(get(l+2, r), get(l, r-2)));
	vector<pair<int, ll> > p1, p2;
	for(int cl=l, cr; cl<r;){
		int lp=cl+1, rp=r-1, mid, ret=cl;
		ll curv=get(l, cl);
		while(lp<=rp){
			mid=(lp+rp)>>1;
			if(get(l, mid)==curv){
				ret=mid; lp=mid+1; 
			}
			else{
				rp=mid-1;
			}
		}
		cr=ret;
		p1.ep(cr, curv);
		cl=cr+1;
	}
	for(int cr=r, cl; cr>l;){
		int lp=l+1, rp=cr-1, mid, ret=cr;
		ll curv=get(cr, r);
		while(lp<=rp){
			mid=(lp+rp)>>1;
			if(get(mid, r)==curv){
				ret=mid; rp=mid-1; 
			}
			else{
				lp=mid+1;
			}
		}
		cl=ret;
		p2.ep(cl, curv);
		cr=cl-1;
	}
	for(auto t:p1) for(auto tt:p2){
		if(t.fi+1<tt.fi-1) ans=max(ans, __gcd(__gcd(t.se, tt.se), get(t.fi+2, tt.fi-2)));
	}
	return ans;
}
ll pre[40][N], suf[40][N];
inline ll get3(int l, int r){
	ll ans=max(get2(l+1, r), get2(l, r-1));
	ans=max(ans, max(get1(l+2, r), get1(l, r-2)));
	ans=max(ans, max(get(l+3, r), get(l, r-3)));
	vector<pair<int, ll> > p1, p2;
	for(int cl=l, cr; cl<r;){
		int lp=cl+1, rp=r-1, mid, ret=cl;
		ll curv=get(l, cl);
		while(lp<=rp){
			mid=(lp+rp)>>1;
			if(get(l, mid)==curv){
				ret=mid; lp=mid+1; 
			}
			else{
				rp=mid-1;
			}
		}
		cr=ret;
		p1.ep(cr, curv);
		cl=cr+1;
	}
	for(int cr=r, cl; cr>l;){
		int lp=l+1, rp=cr-1, mid, ret=cr;
		ll curv=get(cr, r);
		while(lp<=rp){
			mid=(lp+rp)>>1;
			if(get(mid, r)==curv){
				ret=mid; rp=mid-1; 
			}
			else{
				lp=mid+1;
			}
		}
		cl=ret;
		p2.ep(cl, curv);
		cr=cl-1;
	}
	for(int _=0; _<(int)p1.size(); ++_){
		pre[_][p1[_].fi+1]=0;
		for(int i=p1[_].fi+2; i<=p2[0].fi; ++i) pre[_][i]=__gcd(pre[_][i-1], a[i]);
	}
	for(int _=0; _<(int)p2.size(); ++_){
		suf[_][p2[_].fi-1]=0;
		for(int i=p2[_].fi-2; i>=p1[0].fi; --i) suf[_][i]=__gcd(suf[_][i+1], a[i]);
	}
	for(int _=0; _<(int)p1.size(); ++_){
		for(int __=0; __<(int)p2.size(); ++__){
			if(p1[_].fi+1<p2[__].fi-1) {
				ll tem=__gcd(p1[_].se, p2[__].se);
				for(int o=p1[_].fi+2; o<=p2[__].fi-2; ++o)
				ans=max(ans, __gcd(tem, __gcd(pre[_][o-1], suf[__][o+1])));
			}
		}
	}
	return ans;
}
int main(){
	// freopen("D:\\nya\\acm\\C\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\C\\test.out","w",stdout);
	read(n); read(m);
	for(int i=1; i<=n; ++i) read(a[i]), st[0][i]=a[i];
	for(int i=2; i<=n; ++i) lg[i]=lg[i>>1]+1;
	for(int t=1; t<=lg[n]; ++t){
		for(int i=1; i+(1<<t)-1<=n; ++i){
			st[t][i]=__gcd(st[t-1][i], st[t-1][i+(1<<(t-1))]);
		}
	}
	while(m--){
		int l, r, k; read(l); read(r); read(k);
		if(k==1){
			printf("%lld\n", get1(l, r));
		}
		else if(k==2){
			printf("%lld\n", get2(l, r));
		}
		else if(k==3){
			printf("%lld\n", get3(l, r));
		}
	}
	return 0;
}

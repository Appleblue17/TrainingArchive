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
struct IO{
    static const int S=1<<21;
    char buf[S],*p1,*p2;int st[105],Top;
    ~IO(){clear();}
    inline void clear(){fwrite(buf,1,Top,stdout);Top=0;}
    inline void pc(const char c){Top==S&&(clear(),0);buf[Top++]=c;}
    inline char gc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;}
    inline IO&operator >> (char&x){while(x=gc(),x==' '||x=='\n'||x=='\r');return *this;}
    template<typename T>inline IO&operator >> (T&x){
        x=0;bool f=0;char ch=gc();
       while(!isdigit(ch)){if(ch=='-') f^=1;ch=gc();}
        while(isdigit(ch)) x=(x<<3)+(x<<1)+ch-'0',ch=gc();
        f?x=-x:0;return *this;
    }
    inline IO&operator << (const char c){pc(c);return *this;}
    template<typename T>inline IO&operator << (T x){
        if(x<0) pc('-'),x=-x;
        do{st[++st[0]]=x%10,x/=10;}while(x);
        while(st[0]) pc('0'+st[st[0]--]);return *this;
    }
}fin,fout;
const int N=1e5+5;
int T, n, m;
ll a[N];
struct sgt{
	ll tr[N<<2], tag[N<<2], mn[N<<2];
	void clr(int p, int l, int r){
		tr[p]=mn[p]=tag[p]=0;
		if(l==r) return ;
		int mid=(l+r)>>1;
		clr(p<<1, l, mid); clr(p<<1|1, mid+1, r);
	}
	inline void down(int p){
		if(tag[p]!=0){
			tr[p<<1]=max(tr[p<<1], tag[p]); tr[p<<1|1]=max(tr[p<<1|1], tag[p]);
			mn[p<<1]=max(mn[p<<1], tag[p]); mn[p<<1|1]=max(mn[p<<1|1], tag[p]);
			tag[p<<1]=max(tag[p<<1], tag[p]); tag[p<<1|1]=max(tag[p<<1|1], tag[p]);
			tag[p]=0;
		}
	}
	void mdf(int p, int l, int r, int L, int R, ll v){
		if(L<=l&&r<=R){
			tr[p]=max(tr[p], v); mn[p]=max(mn[p], v); tag[p]=max(tag[p], v);
			return ;
		}
		int mid=(l+r)>>1;
		down(p);
		if(L<=mid) mdf(p<<1, l, mid, L, R, v);
		if(R>mid) mdf(p<<1|1, mid+1, r, L, R, v);
		tr[p]=max(tr[p<<1], tr[p<<1|1]);
		mn[p]=min(mn[p<<1], mn[p<<1|1]);
	}
	ll get(int p, int l, int r, int L, int R){
		if(L<=l&&r<=R) return tr[p];
		int mid=(l+r)>>1; ll ret=0;
		down(p);
		if(L<=mid) ret=get(p<<1, l, mid, L, R);
		if(R>mid) ret=max(ret, get(p<<1|1, mid+1, r, L, R));
		return ret;
	}
}tf, tg;
struct cnt{
	ll sum[N<<2], tag[N<<2];
	void clr(int p, int l, int r){
		sum[p]=0; tag[p]=-1;
		if(l==r) return ;
		int mid=(l+r)>>1;
		clr(p<<1, l, mid); clr(p<<1|1, mid+1, r);
	}
	void down(int p, int l, int r){
		if(tag[p]!=-1){
			int mid=(l+r)>>1;
			sum[p<<1]=tag[p]*(mid-l+1);
			sum[p<<1|1]=tag[p]*(r-mid);
			tag[p<<1]=tag[p]; tag[p<<1|1]=tag[p];
			tag[p]=-1;
		}
	}
	void mdf(int p, int l, int r, int L, int R, ll v){
		if(L>R) return ;
		if(L<=l&&r<=R){
			sum[p]=v*(r-l+1); tag[p]=v;
			return ;
		}
		int mid=(l+r)>>1;
		down(p, l, r);
		if(L<=mid) mdf(p<<1, l, mid, L, R, v);
		if(R>mid) mdf(p<<1|1, mid+1, r, L, R, v);
		sum[p]=sum[p<<1]+sum[p<<1|1];
	}
	ll get(int p, int l, int r, int L, int R){
		if(L<=l&&r<=R) return sum[p];
		int mid=(l+r)>>1; ll ret=0;
		down(p, l, r);
		if(L<=mid) ret+=get(p<<1, l, mid, L, R);
		if(R>mid) ret+=get(p<<1|1, mid+1, r, L, R);
		return ret;
	}
}tc;
int getlg(int p, int l, int r, int L, int R, ll v){
	if(L>R) return R+1;
	if(L<=l&&r<=R){
		if(tg.mn[p]>v) return R+1;
		if(l==r) return l;
		int mid=(l+r)>>1;
		tg.down(p);
		if(tg.mn[p<<1]==v) return getlg(p<<1, l, mid, L, R, v);
		else return getlg(p<<1|1, mid+1, r, L, R, v);
	}
	int mid=(l+r)>>1;
	tg.down(p);
	int ret=R+1;
	if(L<=mid) ret=getlg(p<<1, l, mid, L, R, v);
	if(ret==R+1&&R>mid) ret=getlg(p<<1|1, mid+1, r, L, R, v);
	return ret;
}
int getrf(int p, int l, int r, int L, int R, ll v){
	if(L>R) return L-1;
	if(L<=l&&r<=R){
		if(tf.mn[p]>v) return L-1;
		if(l==r) return l;
		int mid=(l+r)>>1;
		tf.down(p);
		if(tf.mn[p<<1|1]==v) return getrf(p<<1|1, mid+1, r, L, R, v);
		else return getrf(p<<1, l, mid, L, R, v);
	}
	int mid=(l+r)>>1;
	tf.down(p);
	int ret=L-1;
	if(R>mid) ret=getrf(p<<1|1, mid+1, r, L, R, v);
	if(ret==L-1&&L<=mid) ret=getrf(p<<1, l, mid, L, R, v);
	return ret;
}
int getfg1(int p, int l, int r, int L, int R){
	if(L>R) return R+1;
	if(L<=l&&r<=R){
		if(tf.tr[p]<tg.mn[p]) return R+1;
		if(l==r) return l;
		int mid=(l+r)>>1;
		tf.down(p); tg.down(p);
		int ret=getfg1(p<<1, l, mid, L, R);
		if(ret==R+1) ret=getfg1(p<<1|1, mid+1, r, L, R);
		return ret;
	}
	int mid=(l+r)>>1;
	tf.down(p); tg.down(p);
	int ret=R+1;
	if(L<=mid) ret=getfg1(p<<1, l, mid, L, R);
	if(ret==R+1&&R>mid) ret=getfg1(p<<1|1, mid+1, r, L, R);
	return ret;
}
int getfg2(int p, int l, int r, int L, int R){
	if(L>R) return L-1;
	if(L<=l&&r<=R){
		if(tf.mn[p]>tg.tr[p]) return L-1;
		if(l==r) return l;
		int mid=(l+r)>>1;
		tf.down(p); tg.down(p);
		int ret=getfg2(p<<1|1, mid+1, r, L, R);
		if(ret==L-1) ret=getfg2(p<<1, l, mid, L, R);
		return ret;
	}
	int mid=(l+r)>>1;
	tf.down(p); tg.down(p);
	int ret=L-1;
	if(R>mid) ret=getfg2(p<<1|1, mid+1, r, L, R);
	if(ret==L-1&&L<=mid) ret=getfg2(p<<1, l, mid, L, R);
	return ret;
}
void work(int x, ll v){
	ll cur=a[x]+v;
	tf.mdf(1, 1, n, x, n, cur);
	tg.mdf(1, 1, n, 1, x, cur);
	tc.mdf(1, 1, n, x, x, min(tf.get(1, 1, n, x, x), tg.get(1, 1, n, x, x)));
	
	//mdf left g
	int mr=x-1, ml=1;
	ml=max(ml, getlg(1, 1, n, 1, x-1, cur));
	int ret=getfg1(1, 1, n, 1, x-1);
	ml=max(ml, ret);
	tc.mdf(1, 1, n, ml, mr, cur);
	--ret;
	while(ret>=1){
		ll tem=tf.get(1, 1, n, ret, ret);
		if(tem==tc.get(1, 1, n, ret, ret)) break;
		int lv=1, rv=ret-1, mid, res=ret; ll ttem=0;
		while(lv<=rv){
			mid=(lv+rv)>>1;
			ttem=tf.get(1, 1, n, mid, mid);
			if(ttem!=tem){
				lv=mid+1;
			}
			else if(ttem!=tc.get(1, 1, n, mid, mid)) {
				res=mid; rv=mid-1;
			}
			else {
				lv=mid+1;
			}
		}
		tc.mdf(1, 1, n, res, ret, ttem);
		ret=res-1;
	}

	//mdf right f
	ml=x+1, mr=n;
	mr=min(mr, getrf(1, 1, n, x+1, n, cur));
	ret=getfg2(1, 1, n, x+1, n);
	mr=min(mr, ret);
	tc.mdf(1, 1, n, ml, mr, cur);
	++ret;
	while(ret<=n){
		ll tem=tg.get(1, 1, n, ret, ret);
		if(tem==tc.get(1, 1, n, ret, ret)) break;
		int lv=ret+1, rv=n, res=ret, mid; ll ttem=0;
		while(lv<=rv){
			mid=(lv+rv)>>1;
			ttem=tg.get(1, 1, n, mid, mid);
			if(ttem!=tem){
				rv=mid-1;
			}
			else if(ttem!=tc.get(1, 1, n, mid, mid)) {
				res=mid; lv=mid+1;
			}
			else {
				rv=mid-1;
			}
		}
		tc.mdf(1, 1, n, ret, res, ttem);
		ret=res+1;
	}

	// for(int i=1; i<=n; ++i) printf("%lld ", tc.get(1, 1, n, i, i));
	// putchar('\n');

	a[x]+=v;
	a[0]+=v;
}
void solve(){
	fin>>n;
	tf.clr(1, 1, n); tg.clr(1, 1, n); tc.clr(1, 1, n);
	for(int i=0; i<=n; ++i) a[i]=0;
	for(int i=1, v; i<=n; ++i) fin>>v, work(i, v);
	fin>>m;
	int x, v;
	while(m--){
		fin>>x>>v;
		work(x, v);
		fout<<tc.sum[1]-a[0];
		fout.pc('\n');
		// printf("%lld\n", tc.sum[1]-a[0]);
	}
}
int main(){
	// freopen("D:\\nya\\acm\\A\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\A\\test.out","w",stdout);
	fin>>T;
	while(T--){
		solve();
	}
	return 0;
}


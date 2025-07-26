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
const int N=4005;
int Test;
ull mi[200];
__int128 p=1;
struct Bit {
	ull bit[200]; int len = 200;
	#define I inline 
	I void reset() {memset(bit, 0, sizeof(bit));}
	Bit() {memset(bit, 0, sizeof(bit));}
	I void set1(int x) { bit[x>>6] |= mi[x&63];}
	I void set0(int x) { bit[x>>6] &= ~mi[x&63];}
	I void flip(int x) { bit[x>>6] ^= mi[x&63];}
	bool operator [](int x) { 
		return (bit[x>>6] >> (x&63)) & 1;
	}
	
	#define re register
	Bit operator ~ (void) const {
		Bit res;
		for (re int i = 0;i < len; i++) res.bit[i] = ~bit[i];
		return res;
	}
	
	Bit operator & (const Bit &b) const {
		Bit res;
		for (re int i = 0;i < len; i++) res.bit[i] = bit[i] & b.bit[i];
		return res;
	}
	
	Bit operator | (const Bit &b) const {
		Bit res;
		for (re int i = 0;i < len; i++) res.bit[i] = bit[i] | b.bit[i];
		return res;
	}	
	
	Bit operator ^ (const Bit &b) const {
		Bit res;
		for (re int i = 0;i < len; i++) res.bit[i] = bit[i] ^ b.bit[i];
		return res;
	}
	
	void operator &= (const Bit &b)  {
		for (re int i = 0;i < len; i++) bit[i] &= b.bit[i];
	}
	
	void operator |= (const Bit &b)  {
		for (re int i = 0;i < len; i++) bit[i] |= b.bit[i];
	}
	
	void operator ^= (const Bit &b)  {
		for (re int i = 0;i < len; i++) bit[i] ^= b.bit[i];
	}
	
	Bit operator << (const int t) const {
		Bit res; int high = t >> 6, low = t & 63;
		ull last = 0;
		for (register int i = 0;i + high < len; i++) {
			res.bit[i + high] = (last | (bit[i] << low));
			if (low) last = (bit[i] >> (64 - low));
		}
		return res;
	}
	
	Bit operator >> (const int t) const {
		Bit res; int high = t >> 6, low = t & 63;
		ull last = 0;
		for (register int i = len - 1;i >= high; i--) {
			res.bit[i - high] = last | (bit[i] >> low);
			if (low) last = bit[i] << (64 - low);
		}
		return res;
	}
	
	void operator <<= (const int t) {
		int high = t >> 6, low = t & 63;
		for (register int i = len - high - 1; ~i; i--) {
			bit[i + high] = (bit[i] << low);
			if (low && i) bit[i + high] |= bit[i - 1] >> (64 - low);
		}
		for (register int i = 0;i < high; i++) bit[i] = 0;
	}
	bool operator == (const Bit t){
		for(register int i=len-1; i>=0; --i) if(bit[i]^t.bit[i]) return false;
		return true;
	}
	void operator -=(const Bit &t){
		for(int i=len-1; i>=0; --i){
			if(bit[i]>=t.bit[i]) {bit[i]-=t.bit[i]; continue;}
			int cur=i+1;
			while(bit[cur]==0) ++cur;
			--bit[cur];
			for(int j=cur-1; j>=i+1; --j) bit[j]=p-1;
			bit[i]=p+bit[i]-t.bit[i];
		}
	}
	bool operator <(const Bit t)const{
		for(int i=len-1; i>=0; --i) if(bit[i]^t.bit[i]){
			if(bit[i]<t.bit[i]) return true;
			else return false;
		}
		return false;
	}
}n, m, emp, tem;
Bit mymin(Bit x, Bit y){
	if(x<y) return x;
	else return y;
}
char s[N], t[N];
int ln, lm;
int bt[N];
int pw[3520][3520], len[3520]; 
int res[3520];
int mx;
int main(){
	// freopen("D:\\nya\\acm\\A\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\A\\test.out","w",stdout);
	mi[0]=1;
	for(int i=1; i<64; ++i) mi[i]=mi[i-1]<<1ull;
	for(int i=1; i<=64; ++i) p*=(__int128)2;
	pw[0][1]=1; len[0]=1;
	for(int i=1; i<=3500; ++i){
		for(int j=1; j<=len[i-1]; ++j) pw[i][j]=pw[i-1][j]*2;
		for(int j=1; j<=len[i-1]; ++j){
			if(pw[i][j]>=10) pw[i][j+1]+=pw[i][j]/10;
			pw[i][j]%=10;
		}
		len[i]=len[i-1];
		while(pw[i][len[i]+1]) ++len[i];
	}
	read(Test);
	while(Test--){
		scanf("%s", s+1);
		scanf("%s", t+1);
		ln=strlen(s+1); lm=strlen(t+1);
		for(int i=1; i<=ln; ++i) s[i]=s[i]-'0';
		for(int i=1; i<=lm; ++i) t[i]=t[i]-'0';
		mx=4*ln;
		n.reset(); m.reset();
		reverse(s+1, s+ln+1);
		vector<int> vec;
		if(!(ln==1&&s[1]==0)){
			while(ln){
				if(s[1]&1){
					s[1]--;
					vec.ep(1);
				}
				else vec.ep(0);
				int lst=0;
				for(int i=ln; i>=1; --i){
					lst*=10; lst+=s[i];
					s[i]=lst/2; lst&=1;
				}
				while(ln&&s[ln]==0) --ln; 
			}
		}
		for(int i=0; i<(int)vec.size(); ++i) if(vec[i]) n.set1(i);
		reverse(t+1, t+lm+1);
		vec.clear();
		while(lm){
			if(t[1]&1){
				t[1]--;
				vec.ep(1);
			}
			else vec.ep(0);
			int lst=0;
			for(int i=lm; i>=1; --i){
				lst*=10; lst+=t[i];
				t[i]=lst/2; lst&=1;
			}
			while(lm&&t[lm]==0) --lm; 
		}
		for(int i=0; i<(int)vec.size(); ++i) if(vec[i]) m.set1(i);
		m=mymin(m, n);
		mx=min(mx, 3500);
		for(int t=mx; t>=0; --t){
			bt[t]=0;
			if(t==0){
				if(n==emp) break;
				else {bt[0]=1; break;}
			}
			tem=m;
			tem<<=t;
			tem-=m;
			if(tem<n){
				bt[t]=1;
				n-=mymin(n>>t, m)<<t;
			}
		}
		for(int t=1; t<=mx; ++t) res[t]=0;
		for(int t=mx; t>=0; --t) if(bt[t]){
			for(int i=1; i<=len[t]; ++i) res[i]+=pw[t][i];
		}
		for(int i=1; i<=mx; ++i) {
			res[i+1]+=res[i]/10; res[i]%=10;
		}
		while(mx&&res[mx]==0) --mx;
		if(mx==0){
			printf("0\n");
		}
		else{
			for(int i=mx; i>=1; --i) printf("%d", res[i]);
			putchar('\n');
		}
	}
	return 0;
}

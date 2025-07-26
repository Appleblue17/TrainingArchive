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
int a[N], b[N];
vector<pii> vec;
void perform(int x, int y){
    vec.ep(x, y);
    int it=0;
    for(int i=n-y+1; i<=n; ++i) b[++it]=a[i];
    for(int i=x+1; i<=n-y; ++i) b[++it]=a[i];
    for(int i=1; i<=x; ++i) b[++it]=a[i];
    for(int i=1; i<=n; ++i) a[i]=b[i];
}
void solve(){
    read(n); 
    for(int i=1; i<=n; ++i) read(a[i]);
    if(n==3){
        if(a[1]>a[3]){
            printf("1\n1 1\n");
        }
        else{
            printf("0\n");
        }
        return ;
    }
    vec.clear();
    if(a[1]!=1){
        int pos=2;
        for(int i=3; i<=n; ++i) if(a[i]==1) pos=i;
        if(pos==2){
            perform(2, 1);
            perform(2, 1);
        }
        else{
            perform(1, n-pos+1);
        }
    }
    while(true){
        int c=1;
        while(c<n&&a[c+1]==c+1) ++c;
        if(c==n) break;
        if(c==n-2){
            perform(1, 1);
            perform(1, 2);
            perform(1, 1);
            perform(2, 1);
            perform(1, 1);
            break;
        }
        int pos=c+2;
        for(int i=c+3; i<=n; ++i) if(a[i]==c+1) pos=i;
        if(pos==n){
            perform(c, 2);
            perform(1, c);
        }
        else{
            perform(c, n-pos);
            perform(pos-1-c+n-pos, c);
        }
    }
    // printf("seq:"); for(int i=1; i<=n; ++i) cout<<a[i]<<' '; cout<<endl;
    printf("%d\n", (int)vec.size());
    for(auto t:vec) printf("%d %d\n", t.fi, t.se);
}
int main(){
	// freopen("D:\\nya\\acm\\A\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\A\\test.out","w",stdout);
	read(T);
	while(T--){
		solve();
	}
	return 0;
}


#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double dou;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
#define fi first
#define se second
#define MAXN 1000010
#define mapa make_pair
typedef long double ld;
typedef unsigned long long ull;
typedef pair<ull,ull> puu;
mt19937 rng(time(0));
template <typename T>inline void read(T &x){
	x=0;char c=getchar();bool f=0;
	for(;c<'0'||c>'9';c=getchar()) f|=(c=='-');
	for(;c>='0'&&c<='9';c=getchar())
	x=(x<<1)+(x<<3)+(c^48);
	x=(f?-x:x);
}
const int mo=1e9+7;
using namespace std;
int a[MAXN],b[MAXN];
ll t,n,m,x,y,ans,k;
int query(int x){
	int y;
	printf("walk %d\n",x);fflush(stdout);
	scanf("%d",&y);
	return y;
}
const int N=998244353;
int cur=0;
int query2(int x){
    cur+=x;
    cur%=N;
    return cur;
}

void answer(int n){
    printf("\nguess %d\n",n);fflush(stdout);
    exit(0);
}
 
int main(){
    int n=0;
	for(int i=1;i<=3332;i++){
		int x = rng()%1000000000;
        n = max(n,query(x));
	}
    int x = rng()%1000000000;
    a[0]=query(x);
    n = max(n,a[0]);
    //printf("n=%d,a[0]=%d\n",n,a[0]);
    for(int i=1;i<=3333;i++){
        a[i] = query(1);
        if(a[i]==a[0])answer(i);
    }
    b[0]=query(n);
    //printf("b[0]=%d\n",b[0]);
        for(int j=0;j<=3333;j++){
            if(b[0]==a[j]){
                answer(n+3333-j);
            }
        }
    for(int i=1;i<=3330;i++){
        b[i] = query(3330);
        //printf("b[%d]=%d\n",i,b[i]);
        for(int j=0;j<=3333;j++){
            if(b[i]==a[j]){
                answer(n+3333+i*3330-j);
            }
        }
    }
}


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
const int N=8005;
const int inf=1e9;
int n, m;
char s[N], t[N];
int dp[N][N];
int sum[N], sum2[N];\
int x, y;
struct myheap{
    priority_queue<int, vector<int>, greater<int> > p, q;
    void push(int x){
        p.push(x);
    }
    void pop(int x){
        q.push(x);
    }
    int top(){
        while(q.size()&&p.top()==q.top()) p.pop(), q.pop();
        return p.top();
    }
};
int main(){
	// freopen("D:\\nya\\acm\\A\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\A\\test.out","w",stdout);
    scanf("%s", s+1);
    scanf("%s", t+1);
    n=strlen(s+1); m=strlen(t+1);
    read(x); read(y);
    if(x<y){
        for(int i=1; i<=n; ++i) s[i]=(s[i]=='A')?'B':'A';
        for(int i=1; i<=m; ++i) t[i]=(t[i]=='A')?'B':'A';
        swap(x, y);
    }
    for(int i=1; i<=n; ++i){
        sum2[i]=sum2[i-1]+((s[i]=='B')?-1:1);
    }
    for(int i=1; i<=m; ++i){
        sum[i]=sum[i-1]+((t[i]=='B')?-1:1);
    }
    sum2[n+1]=sum2[n];
    sum[m+1]=sum[m];
    for(int i=0; i<=n+1; ++i){
        for(int j=0; j<=m+1; ++j){
            dp[i][j]=inf;
        }
    }
    dp[0][0]=0;
    for(int i=1; i<=n+1; ++i){
        vector<pii> rem;
        myheap pq;
        for(int j=1; j<=m+1; ++j){
            int cur=dp[i-1][j-1];
            while(rem.size()&&rem.back().fi<sum[j-1]){
                pq.pop(rem.back().se);
                cur=min(cur, rem.back().se+sum[j-1]-rem.back().fi);
                rem.pop_back();
            }
            if(rem.size()&&rem.back().fi==sum[j-1]){
                if(rem.back().se>cur){
                    pq.pop(rem.back().se);
                    rem.back().se=cur;
                    pq.push(cur);
                }
                else{
                    cur=rem.back().se;
                }
            }
            else{
                pq.push(cur);
                rem.ep(sum[j-1], cur);
            }
            if(s[i]==t[j]&&sum2[i]==sum[j]){
                dp[i][j]=min(dp[i][j], pq.top());
                // int mx=-m;
                // for(int k=j-1; k>=0; --k){
                //     mx=max(mx, sum[k]);
                //     dp[i][j]=min(dp[i][j], dp[i-1][k]+mx-sum[k]);
                // }
            }
        }
    }
    if(dp[n+1][m+1]==inf) {
        printf("-1\n");
    }
    else{
        printf("%lld\n", 1ll*dp[n+1][m+1]*x+1ll*((m-n)/2-dp[n+1][m+1])*y);
    }
	return 0;
}


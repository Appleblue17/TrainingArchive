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
const int N=2e6+5;
int n, m;
char s[N];
struct PAM{
    struct node{
        int ch[26];
        int fail, len, num;
    };
    node a[N];
    int lst, cnt;
    PAM(){
        a[0].len=0; a[0].fail=1;
        a[1].len=-1; a[1].fail=0;
        lst=0; cnt=1;
    }
    int get_fail(int x, int lim){
        while(s[lim-a[x].len-1]!=s[lim]) x=a[x].fail;
        return x;
    }
    void insert(int c, int lim){
        int p=get_fail(lst, lim);
        if(!a[p].ch[c]){
            a[++cnt].len=a[p].len+2;
            int q=get_fail(a[p].fail, lim);
            a[cnt].fail=a[q].ch[c];
            a[cnt].num=a[a[cnt].fail].num+1;
            a[p].ch[c]=cnt;
        }
        lst=a[p].ch[c];
    }
    int ans[N];
    void build(){
        for(int i=1; i<=n; ++i) {
            insert(s[i]-'a', i);
            ans[i]=a[lst].num;
        }
    }
}P;
struct SAM{
    int cnt=1, lst=1;
    struct node{
        int len, fa;
        int ch[26];
    }sam[N];
    ll f1[N], f2[N];
    vector<int> e[N];
    void extend(int c, int val){
        int p=lst, np=lst=++cnt;
        f1[np]=1; f2[np]=val;
        sam[np].len=sam[p].len+1;
        for(; p&&!sam[p].ch[c]; p=sam[p].fa) sam[p].ch[c]=np;
        if(!p) sam[np].fa=1;
        else{
            int q=sam[p].ch[c];
            if(sam[q].len==sam[p].len+1) sam[np].fa=q;
            else{
                int nq=++cnt;
                sam[nq]=sam[q]; sam[nq].len=sam[p].len+1;
                sam[q].fa=sam[np].fa=nq;
                for(; p&&sam[p].ch[c]==q; p=sam[p].fa) sam[p].ch[c]=nq;
            }
        }
    }
    void dfs(int x){
        for(auto y:e[x]) dfs(y), f1[x]+=f1[y], f2[x]+=f2[y];
    }
    void build(){
        for(int i=1; i<=n; ++i){
            extend(s[i]-'a', P.ans[n-i]);
        }
        for(int i=2; i<=cnt; ++i) e[sam[i].fa].ep(i);
        dfs(1);
    }
}S;
char t[N];
const int m1=998244353, m2=993244853;
struct hsh{
    int v1, v2;
};
hsh bs=(hsh){131, 13331};
inline hsh operator +(hsh x, hsh y){
    return (hsh){(x.v1+y.v1)%m1, (x.v2+y.v2)%m2};
}
inline hsh operator -(hsh x, hsh y){
    return (hsh){(x.v1-y.v1+m1)%m1, (x.v2-y.v2+m2)%m2};
}
inline hsh operator *(hsh x, hsh y){
    return (hsh){(int)(1ll*x.v1*y.v1%m1), (int)(1ll*x.v2*y.v2%m2)};
}
inline bool operator ==(hsh x, hsh y){
    return x.v1==y.v1&&x.v2==y.v2;
}
hsh pw[N], h1[N], h2[N];

int main(){
	// freopen("D:\\nya\\acm\\A\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\A\\test.out","w",stdout);
	read(n); read(m);
    scanf("%s", s+1);
    P.build();
    reverse(s+1, s+n+1);
    S.build();
    while(m--){
        scanf("%s", t+1);
        int len=strlen(t+1);
        int cur=1;
        pw[0]=(hsh){1, 1};
        for(int i=1; i<=len; ++i) h1[i]=h1[i-1]*bs+(hsh){t[i], t[i]}, pw[i]=pw[i-1]*bs;
        for(int i=1; i<=len; ++i) h2[i]=h2[i-1]*bs+(hsh){t[len-i+1], t[len-i+1]};
        ll ans=0;
        for(int i=1; i<=len; ++i){
            cur=S.sam[cur].ch[t[i]-'a'];
            if(cur==0) break;
            hsh tem=h1[len]-h1[i]*pw[len-i];
            if(tem==h2[len-i]){
                ans+=S.f1[cur];
            }
        }
        if(cur!=0) ans+=S.f2[cur];
        printf("%lld\n", ans);
    }
    return 0;
}


#pragma GCC optimize(3)
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=5005;
const int mod1=998244353, mod2=993244853;
struct node{
    int x, y;
};
inline node operator +(node x, node y){
    return (node){(x.x+y.x)%mod1, (x.y+y.y)%mod2};
}
inline node operator -(node x, node y){
    return (node){(x.x-y.x+mod1)%mod1, (x.y-y.y+mod2)%mod2};
}
inline node operator *(node x, node y){
    return (node){1ll*x.x*y.x%mod1, 1ll*x.y*y.y%mod2};
}
inline bool operator ==(node x, node y){
    return x.x==y.x&&x.y==y.y;
}
int Test, n;
char s[N];
node bs=(node){137, 13331};
node pw[N], hs[N];
inline node get(int l, int r){
    return hs[r]-hs[l-1]*pw[r-l+1];
}
unordered_map<ll, int> h;
inline ll gh(node x){
    return 1ll*x.x*1000000000ll+x.y;
}
int f[N][N];
int main(){
    cin>>Test;
    while(Test--){
        scanf("%s", s+1);
        n=strlen(s+1);
        pw[0]=(node){1, 1};
        for(int i=1; i<=n; ++i) {
            pw[i]=pw[i-1]*bs;
            hs[i]=hs[i-1]*bs+(node){s[i], s[i]};
        }
        for(int i=1; i<=n; ++i) for(int j=1; j<=n; ++j) f[i][j]=0;
        for(int len=1; len<=n; ++len){
            for(int i=len+1; i+len-1<=n; ++i){
                if(get(i, i+len-1)==get(i-1-len+1, i-1)){
                    ++f[i][i+len-1];
                }
            }
        }
        for(int i=1; i<=n; ++i){
            for(int j=i; j<=n; ++j) f[i][j]+=f[i][j-1];
        }
        ll ans=0;
        for(int len=2; len*2 < n; ++len){
            h.clear();
            for(int i=n-len+1; i-len+1>=1; --i){
                if(i+2+len-1<=n) h[gh(get(i+2, i+2+len-1))]++;
                ans+=1ll*h[gh(get(i-len+1, i))]*f[i-len+1][i-1];
            }
        }
        cout<<ans<<endl;
    }
}

#pragma GCC optimize(2)
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e6+5;
int n, m;
ll ans[26][26], sum[26][26], glob;
char s[N];
int tr[N][26], idx, sz[N];
int main(){
    scanf("%d%d", &n, &m);
    idx=1;
    for(int i=1; i<=n; ++i){
        scanf("%s", s+1);
        int p=1;
        for(int j=1; s[j]; ++j){
            int c=s[j]-'a';
            for(int k=0; k<c; ++k) ans[c][k]+=sz[tr[p][k]];
            for(int k=c+1; k<26; ++k) ans[c][k]+=sz[tr[p][k]];
            if(!tr[p][c]) tr[p][c]=++idx;
            p=tr[p][c];
            ++sz[p];
        }
        for(int k=0; k<26; ++k) glob+=sz[tr[p][k]];
    }
    while(m--){
        scanf("%s", s+1);
        ll res=glob;
        for(int i=1; i<=26; ++i){
            for(int j=i+1; j<=26; ++j){
                res+=ans[s[i]-'a'][s[j]-'a'];
            }
        }
        printf("%lld\n", res);
    }
}

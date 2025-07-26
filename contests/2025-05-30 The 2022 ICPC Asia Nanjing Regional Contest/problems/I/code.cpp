#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int T;
char s[N];
int cnt[26];
int main(){
    scanf("%d", &T);
    while(T--){
        scanf("%s", s+1);
        int n=strlen(s+1);
        memset(cnt, 0, sizeof cnt);
        for(int i=1; i<=n; ++i) cnt[s[i]-'a']++;
        int mx=0;
        for(int i=0; i<26; ++i) mx=max(mx, cnt[i]);
        printf("%d\n", n-mx);
    }
}

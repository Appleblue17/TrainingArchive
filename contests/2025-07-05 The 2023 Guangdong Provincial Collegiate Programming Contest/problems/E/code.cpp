#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int T;
int n, m;
char s[N];
int tr[N][26], idx, sz[N], occ[N];
char stk[N]; int top;
bool flag;
int glob;
void dfs(int x){
    if(flag) return ;
    glob+=occ[x];
    int cur=0;
    for(int i=0; i<26; ++i) if(tr[x][i]){
        int y=tr[x][i];
        cur+=min(1, sz[y]);
    }
    if(cur+glob>=m){
        flag=1;
        if(top==0) printf("EMPTY\n");
        else{
            for(int i=1; i<=top; ++i) putchar(stk[i]);
            putchar('\n');
        }
        return ;
    }
    for(int i=0; i<26; ++i) if(tr[x][i]){
        int y=tr[x][i];
        cur-=min(1, sz[y]);
        stk[++top]='a'+i;
        glob+=cur;
        dfs(y);
        glob-=cur;
        if(flag) return ;
        --top;
    }
}
void solve(){
    scanf("%d%d", &n, &m);
    for(int i=1; i<=idx; ++i) {
        sz[i]=0; occ[i]=0;
        for(int j=0; j<26; ++j) tr[i][j]=0;
    }
    idx=1;
    for(int i=1; i<=n; ++i){
        scanf("%s", s+1);
        int p=1; ++sz[1];
        for(int j=1; s[j]; ++j){
            if(!tr[p][s[j]-'a']) tr[p][s[j]-'a']=++idx;
            p=tr[p][s[j]-'a'];
            ++sz[p];
        }
        ++occ[p];
    }
    top=0; flag=0; glob=0;
    dfs(1);
}
int main(){
    scanf("%d", &T);
    while(T--){
        solve();
    }
}

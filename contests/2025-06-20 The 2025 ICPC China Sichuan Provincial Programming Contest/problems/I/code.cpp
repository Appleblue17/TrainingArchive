#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
char s[N];
int tr[N][26], idx;
int main(){
    int n;
    scanf("%d",&n);
    for(int i=1; i<=n; ++i){
        scanf("%s", s+1);
        int m=strlen(s+1);
        reverse(s+1, s+m+1);
        int p=0;
        for(int j=1; j<=m; ++j){
            int c=s[j]-'a';
            if(tr[p][c]==0) tr[p][c]=++idx;
            p=tr[p][c];
        }
    }
    printf("%d\n", idx);
}

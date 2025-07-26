#include <bits/stdc++.h>
using namespace std;
const int N=1100;
int T,n,m,k;
char A[N],B[N],C[N];

int fa[26];
int getf(int x){
    if(x==fa[x]) return x;
    return fa[x]=getf(fa[x]);
}

bool solve(){
    if(n!=m) return 0;
    if(n!=k) return 1;
    
    for(int i=0;i<26;i++) fa[i]=i;
    for(int i=1;i<=n;i++){
        int x=getf(A[i]-'a'),y=getf(B[i]-'a');
        fa[x]=y;
    }
    for(int i=1;i<=n;i++){
        int x=getf(A[i]-'a'),z=getf(C[i]-'a');
        if(x!=z) return 1;
    }
    return 0;
}

int main(){
    scanf("%d",&T);
    while(T--){
        scanf("\n%s\n%s\n%s",A+1,B+1,C+1);
        n=strlen(A+1);
        m=strlen(B+1);
        k=strlen(C+1);
        if(solve()) puts("YES");
        else puts("NO");
    }
    
}

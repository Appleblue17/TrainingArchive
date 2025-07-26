#include <bits/stdc++.h>
using namespace std;
const int N=1100;
int n,m;
char S[N][N],ans[N][N];

int L[N],R[N],D[N],U[N];

void no(){
    puts("NO");
    exit(0);
}

queue < pair<int,int> > q;
bool is_conflict(int x,int y){
    if(S[x][y]=='x') return 1;
    vector<char> tmp;
    if(L[x]==y) tmp.push_back(S[x][0]);
    if(R[x]==y) tmp.push_back(S[x][m+1]);
    if(U[y]==x) tmp.push_back(S[0][y]);
    if(D[y]==x) tmp.push_back(S[n+1][y]);
    if(!tmp.size()) return 0;
    for(char c: tmp) if(c!=tmp[0]) return 1;
    return 0;
}
void check(int x,int y){
    if(is_conflict(x,y)) q.push({x,y});
}

int main(){
    scanf("%d%d",&n,&m);
    for(int i=0;i<=n+1;i++)
        scanf("%s",S[i]);
    
    for(int j=1;j<=m;j++){
        if(S[0][j]!='.') U[j]=1,check(1,j);
        if(S[n+1][j]!='.') D[j]=n,check(n,j);
    }
    for(int i=1;i<=n;i++){
        if(S[i][0]!='.') L[i]=1,check(i,1);
        if(S[i][m+1]!='.') R[i]=m,check(i,m);
    }
    
    while(q.size()){
        pair<int,int> tmp=q.front(); q.pop();
        int x=tmp.first,y=tmp.second;
        if(!is_conflict(x,y)) continue;
        if(L[x]==y){
            L[x]++;
            if(L[x]>m) no();
            check(x,y+1);
        }
        if(R[x]==y){
            R[x]--;
            if(R[x]<=0) no();
            check(x,y-1);
        }
        if(U[y]==x){
            U[y]++;
            if(U[y]>n) no();
            check(x+1,y);
        }
        if(D[y]==x){
            D[y]--;
            if(D[y]<=0) no();
            check(x-1,y);
        }
    }
    
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            ans[i][j]='.';
    for(int j=1;j<=m;j++){
        if(U[j] && D[j] && U[j]>D[j]) no();
        if(U[j]) ans[U[j]][j]=S[0][j];
        if(D[j]) ans[D[j]][j]=S[n+1][j];
    }
    for(int i=1;i<=n;i++){
        if(L[i] && R[i] && L[i]>R[i]) no();
        if(L[i]) ans[i][L[i]]=S[i][0];
        if(R[i]) ans[i][R[i]]=S[i][m+1];
    }
    
    puts("YES");
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            putchar(ans[i][j]);
        }
        putchar('\n');
    }
}

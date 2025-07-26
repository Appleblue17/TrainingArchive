#include<bits/stdc++.h>
using namespace std;
int n=1024;
int v1[1025], v2[1025];
vector<int> e[1025];
int col[1025];
void dfs(int x, int c){
    if(col[x]) return;
    col[x]=c;
    for(auto y:e[x]) dfs(y, 3-c);
}
int main(){
    int it1=1, it2=1;
    for(int i=1; i<=n/2; ++i){
        int x=i*2-1, y=i*2;
        if(i&1){
            while(v1[it1]) ++it1;
            for(int j=1; j<it1; ++j) e[x].push_back(v2[j]), e[v2[j]].push_back(x);
            v1[it1]=x;
            while(v1[it1]) ++it1;
            for(int j=1; j<it1; ++j) e[y].push_back(v1[j]), e[v1[j]].push_back(y);
            v2[it1]=y;
        }
        else{
            while(v2[it2]) ++it2;
            for(int j=1; j<it2; ++j) e[x].push_back(v1[j]), e[v1[j]].push_back(x);
            v2[it2]=x;
            while(v2[it2]) ++it2;
            for(int j=1; j<it2; ++j) e[y].push_back(v2[j]), e[v2[j]].push_back(y);
            v1[it2]=y;
        }
    }
    int m=0;
    for(int i=1; i<=n; ++i) m+=e[i].size();
    m/=2;
    printf("%d %d 2\n", n, m);
    dfs(1, 1);
    for(int i=1; i<=n; ++i) printf("%d ", col[i]);
    putchar('\n');
    for(int i=1; i<=n; ++i){
        for(auto j:e[i]) if(i<j) printf("%d %d\n", i, j);
    }
    return 0;
}

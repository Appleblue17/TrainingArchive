#pragma GCC optimize(3)
#include <bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int Test, n, m;
vector<int> e[N];
int col[N];
inline int add(int x){
    return (x+1)%n;
}
inline int del(int x){
    return (x-1+n)%n;
}
int main(){
    cin>>Test;
    while(Test--){
        cin>>n>>m;
        if(m==0){
            putchar('B');
            for(int i=1; i<n; ++i) putchar('R');
            putchar('\n');
            continue;
        }
		for(int i=0; i<n; ++i) col[i]=-1, e[i].clear();
        for(int i=0; i<n; ++i) e[i].push_back(add(i)), e[i].push_back(del(i));
		queue<int> q;
        for(int i=1, x, y; i<=m; ++i){
            cin>>x>>y;
            e[x].push_back(y);
            e[y].push_back(x);
        }
        q.push(0);
        col[0]=0;
		while(!q.empty()){
			int x=q.front(); q.pop();
            for(auto y:e[x]) if(col[y]==-1){
                col[y]=col[x]^1; q.push(y);
            }
		}
        for(int i=0; i<n; ++i) {
            if(col[i]) putchar('R');
            else putchar('B');
        }
        putchar('\n');
    }
}

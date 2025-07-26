#include <bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int T,n,m;
int a[N],b[N];

bool solve(){
    int nw=1;
    for(int i=1;i<=m;i++){
        while(nw<=n && a[nw]!=b[i]) nw++;
        if(nw>n) return 0;
        nw++;
    }
    return 1;
}

int main(){
    cin>>T;
    while(T--){
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++) scanf("%d",&a[i]);
        for(int i=1;i<=m;i++) scanf("%d",&b[i]);
        if(solve()) puts("Yes");
        else puts("No");
        
    }
    
}

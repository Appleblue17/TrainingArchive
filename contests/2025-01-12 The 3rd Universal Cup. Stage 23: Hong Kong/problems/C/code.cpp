#include <bits/stdc++.h>
using namespace std;
const int N=5e5+5;
int T,n;
int a[N];

int main(){
    cin>>T;
    while(T--){
        scanf("%d",&n);
        int mx=0;
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
            mx=max(mx,a[i]);
        }
        for(int i=1;i<=n;i++) if(a[i]==mx) printf("%d ",i);
        puts("");
    }
    
    
}

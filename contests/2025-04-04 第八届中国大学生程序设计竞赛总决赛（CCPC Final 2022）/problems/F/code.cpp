#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int T, n;
int p[N], a[N];
int main(){
    scanf("%d", &T);
    while(T--){
        scanf("%d", &n);
        for(int i=1; i<=n; ++i) scanf("%d", &p[i]), a[p[i]]=i;
        int mx2=0;
        for(int i=1; i<n; ++i) {
            mx2=max(mx2, abs(a[i]-a[i+1]));
        }
        if(mx2>=3) puts("No");
        else puts("Yes");
    }
}

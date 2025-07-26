#include <bits/stdc++.h>
using namespace std;
const int N=1e6+5,INF=1e9;
int T, n, m;
char S[N];

signed main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        scanf("%d", &m);
        if(m>=n){
            printf("1\n");
            continue;
        }
        int cur=1, sum=0;
        int ans=1000000001;
        for(int i=1; i<=m; ++i){
            sum+=cur;
            if(sum>=n){
                ans=min(ans, cur);
                break;
            }
            if(i==m) break;
            int res=(n-sum+m-i-1)/(m-i);
            if(sum>=res-1){
                ans=min(ans, max(cur, res));
            }
            cur<<=1;
        }
        if(ans==1000000001){
            ans=-1;
        }
        printf("%d\n", ans);
    }
    
}

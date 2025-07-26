#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int T, n;
int a[N], b[N], sum[N];
int main(){
    scanf("%d", &T);
    while(T--){
        scanf("%d", &n);
        sum[0]=1;
        for(int i=1; i<=n; ++i) {
            scanf("%d", &a[i]);
            if(a[i]!=0) sum[i]=sum[i-1]+a[i], b[i]=a[i];
            else sum[i]=sum[i-1]+1, b[i]=1;
        }
        bool flag=0;
        for(int i=1; i<=n; ++i) if(sum[i]<=0) flag=1;
        if(flag){
            printf("-1\n");
            continue;
        }
        int mn=1e9;
        for(int i=n; i>=1; --i){
            mn=min(mn, sum[i]);
            if(mn<=2) break;
            if(a[i]==0){
                b[i]=-1;
                mn-=2;
            }
        }
        int s=1, t=1;
        for(int i=1; i<=n; ++i) {
            if(b[i]==1) s++, t++;
            else t--;         
        }
        int d=__gcd(s, t);
        s/=d; t/=d;
        printf("%d %d\n", s, t);
    }
}

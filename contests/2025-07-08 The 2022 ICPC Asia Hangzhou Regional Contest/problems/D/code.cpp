#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e5+5;
int n, sum;
int a[N];

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        scanf("%lld",&a[i]);
        sum+=a[i];
    }
    
    for(int i=1;i<=n;i++){
        printf("%.8lf ",sum*1.0/(n+1)*(1+(i==1)));
    }
    
}

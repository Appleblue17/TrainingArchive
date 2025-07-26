#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=30;
ll n,l[N],w[N];
double f[1100000];
int main(){
    scanf("%lld",&n);
    for(int i=1;i<=n;i++)scanf("%lld",&l[i]);
    for(int i=1;i<=n;i++)scanf("%lld",&w[i]);
    for(int i=1;i<=1099000;i++){
        f[i]=-1e9;
    }
    f[0]=0;
    for(int i=1;i<=(1<<n)-1;i++){
        ll W=0;
        for(int j=1;j<=n;j++){
            if(i & (1<<(j-1)))W += w[j];
        }
        //printf("i=%d,W=%lld\n",i,W);
        for(int j=1;j<=n;j++){
            if(i & (1<<(j-1))){
                //printf("j=%d,v=%d,add=%.2lf,f[%d]=%.10lf\n",j,i^(1<<(j-1)),(w[j]/(W*1.0))*l[j]/2.0,i,f[i]);
                f[i] = max(f[i],f[i^(1<<(j-1))]+(w[j]/(W*1.0))*l[j]/2.0);
                f[i] = max(f[i],l[j]/2.0*(W-w[j])/(W*1.0)+l[j]/2.0);
            }
        }
        //printf("f[%d]=%.10lf\n",i,f[i]);
    }
    printf("%.10lf\n",f[(1<<n)-1]);
}

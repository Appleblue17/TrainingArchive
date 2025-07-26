#include<bits/stdc++.h>
using namespace std;
const int N=1e4+5;
typedef long long ll;
int T, n, m;
ll x[N],y[N],d[N][N/2],mx[N][N/2],lst[N];
ll dis(int i,int j){
    return (x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]);
}

int pa(int i,int j,int k){
    if(i>n)i-=n;
    if(j>n)j-=n;
    if(k>n)k-=n;
    if(k == i)return 0;
    if(j < i)j+=n;
    if(k < i)k+=n;
    if(k < j)return -1;
    else if(k == j)return 0;
    else return 1;
}

int pre(int j){
    if(j == 1)j=n;
    else j = j-1;
    return j;
}
int nxt(int j){
    if(j == n)j=1;
    else j++;
    return j;
}

bool col(int i){
    ll c = (y[i]-y[pre(i)])*(x[pre(i)]-x[pre(pre(i))])-(x[i]-x[pre(i)])*(y[pre(i)]-y[pre(pre(i))]);
    if(c == 0)return 1;
    else return 0;
}

void solve(){
    scanf("%d", &n);
    for(int i=1;i<=n;i++){
        scanf("%lld%lld",&x[i],&y[i]);
        x[i+n]=x[i];y[i+n]=y[i];
    }
    for(int i=1;i<n*2;i++){
        d[i][2]=dis(i,i+1);
    }
    for(int i=1;i<=n*2;i++){
        mx[i][i]=0;
        for(int j=i-1;j>=1;j--){
            mx[i][j] = max(mx[i][j+1],dis(i,j));
        }
    }
    for(int j=3;j<=n;j++){
        for(int i=1;i+j<=n*2;i++){
            d[i][j] = max(d[i][j-1],mx[i+j-1][i]);
            //printf("d[%d][%d]=%lld\n",i,j,d[i][j]);
        }
    }
    int ori = 1;
    while(col(ori))ori++;
    lst[ori]=pre(pre(ori));
    //printf("ori=%d\n",ori);
    for(int i=ori+1;i<=ori+n;i++){
        if(col(i))lst[i]=lst[i-1];
        else lst[i]=pre(pre(i));
    }
    ll ans = 4e18;
    for(int i=ori;i<ori+n;i++){
        for(int j=i+2;j<ori+n;j++){
            if(pa(i,j,lst[j])<=0 && pa(j,i,lst[i])<=0){
                ans = min(ans,d[i][j-i+1]+d[(j-1)%n+1][n+2-j+i-1]);
                //printf("i=%d,j=%d,ans=%lld\n",i,j,ans);
            }
        }
    }
    printf("%lld\n",ans);
}
int main(){
    scanf("%d", &T);
    while(T--){
        solve();
    }
    
}

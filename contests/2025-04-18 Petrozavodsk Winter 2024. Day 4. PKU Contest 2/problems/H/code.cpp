#include<bits/stdc++.h>
using namespace std;
const int N=2e6+5,mod=1e9+7;
int n;
int a[N];

int mul(int n){
    int tot=1;
    for(int i=1;i<=n;i++) tot=1ll*tot*i%mod;
    return tot;
}

long long A,B;
int ans[1010][1010];
signed main(){
    cin>>n;
    if(n&1){
        printf("No\n");
    }
    else{
        printf("Yes\n");
        int m = (n/2);
        for(int i=1;i<=m;i++){
            for(int j=1;j<=m;j++){
                if(i+j-1 < m){
                    ans[i*2-1][j*2-1] = 1;
                    ans[i*2][j*2] = 1;
                    ans[i*2-1][j*2] = 1;
                    ans[i*2][j*2-1] = 1;
                }
                else if(i+j-1 > m){
                    ans[i*2-1][j*2-1] = -1;
                    ans[i*2][j*2] = -1;
                    ans[i*2-1][j*2] = -1;
                    ans[i*2][j*2-1] = -1;
                }
                else{
                    ans[i*2-1][j*2-1] = 1;
                    ans[i*2][j*2] = -1;
                    ans[i*2-1][j*2] = 0;
                    ans[i*2][j*2-1] = 1;
                }
            }
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                printf("%d ",ans[i][j]);
            }
            putchar('\n');
        }
    }
}

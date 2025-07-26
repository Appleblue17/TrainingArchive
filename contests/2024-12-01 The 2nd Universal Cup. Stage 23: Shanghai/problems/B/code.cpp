#include <bits/stdc++.h>
using namespace std;
// #define int long long
const int N=1e5+5,INF=1e9;
int T,n;
char S[N];
int a[N],cnt;

int dp[N][9],rec[N][9];
int f[9]={0,0,0,0,0,0,1,2,3};
int g[9]={0,0,0,0,1,0,0,0,0};

void pr(int x){
    int r=x%3;
    if(r) putchar(r+'0'),x-=r;
    for(int i=1;i<=x/3;i++) putchar('3');
}
int fd(int x,int fir){
    if(x<0) return INF;
    if(!x) return fir;
    return (x-1)%3+1;
}
int cal(int x){
    if(x<0) return INF;
    if(!x) return 0;
    return (x-1)/3+1;
}



signed main(){
    scanf("%d",&T);
    while(T--){
        scanf("\n%s",S+1);
        n=strlen(S+1);
        
        cnt=0;
        for(int i=1;i<=n;i++) if(S[i]=='V') a[++cnt]=i;
        a[cnt+1]=n+1;
        
        if(!cnt){
            pr(n);
            putchar('\n');
            continue;
        }
        
        for(int i=1;i<=cnt+1;i++){
            for(int j=4;j<=8;j++){
                dp[i][j]=INF;
            }
        }
        dp[cnt+1][5]=0;
        for(int i=cnt;i>=1;i--){
            int len=a[i+1]-a[i]-1;
            
            for(int j=4;j<=8;j++){
                for(int k=4;k<=8;k++){
                    int val=dp[i+1][j]+cal(len-g[j]-f[k])+1;
                    int j_=rec[i][k];
                    if(val<dp[i][k] || 
                        (val==dp[i][k] && fd(len-g[j]-f[k],j) < fd(len-g[j_]-f[k],j_) ) ){
                        dp[i][k]=val;
                        rec[i][k]=j;
                    }
                }
            }
            
            // cout<<i<<": ";
            // for(int j=4;j<=8;j++) cout<<dp[i][j]<<" ";
            // cout<<endl;
        }
        int mn=INF,mner=0;
        int len=a[1]-1;
        for(int j=4;j<=8;j++){
            int val=dp[1][j]+cal(len-g[j]);
            
            if(val<mn || (val==mn && fd(len-g[j],j)<fd(len-g[mner],mner))){
                mn=val,mner=j;
            }
        }
        // cout<<endl;
        
        // cout<<mn<<" "<<mner<<" ";
        
        int nw=mner,lst=5;
        for(int i=1;i<=cnt;i++){
            int len=a[i]-a[i-1]-1;
            pr(len-f[lst]-g[nw]);
            putchar(nw+'0');
            lst=nw;
            nw=rec[i][nw];
        }
        len=n-a[cnt];
        pr(len-f[lst]);
        
        
        putchar('\n');
    }
    
}

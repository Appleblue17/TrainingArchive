#include <bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int T,n,k,l;
int p[N];

bool vis[N];
int dp[N];
void check(){
    for(int i=0;i<n;i++) vis[i]=0;
    
    for(int i=1;i<=n;i++){
        int x=p[i]-k;
        if(x<0 || x>=n){
            printf("! Out of range on %d: %d\n",i,x);
            break;
        }
        if(vis[x]){
            printf("! Dub on %d: %d\n",i,x);
            break;
        }
        vis[x]=1;
    }
    
    for(int i=1;i<=n-2;i++){
        int tmp[3]={p[i],p[i+1],p[i+2]};
        sort(tmp,tmp+3);
        if(tmp[0]+tmp[1]<=tmp[2]){
            printf("! WA on %d: %d + %d <= %d\n", i, tmp[0], tmp[1], tmp[2]);
            break;
        }
    }
    
    int tot=0;
    for(int i=1;i<=n;i++){
        dp[i]=1;
        for(int j=1;j<i;j++){
            if(p[j]<p[i]) dp[i]=max(dp[i],dp[j]+1);
        }
        tot=max(tot,dp[i]);
    }
    if(tot!=l){
        // cout<<n<<" "<<k<<" "<<l<<endl;
        printf("LIS WA: %d != %d\n",tot,l);
    }
}


signed main(){
    cin>>T;
    while(T--){
        scanf("%d%d%d",&n,&k,&l);
        if(k==1){
            puts("No");
            continue;
        }
        else if(k>=4){
            if(l<=(n+1)/2){
                for(int i=1;i<=l;i++) p[i]=n-l+i;
                for(int i=l+1;i<=n;i++) p[i]=n+1-i;
            }
            else{
                for(int i=1;i<l;i++) p[i]=i;
                for(int i=l;i<=n;i++) p[i]=n+l-i;
            }
        }
        else if(k==3){
            if(l<=n/2){
                for(int i=1;i<=l;i++) p[i]=n-l+i;
                for(int i=l+1;i<=n;i++) p[i]=n+1-i;
            }
            else if(l>(n+1)/2){
                for(int i=1;i<l;i++) p[i]=i;
                for(int i=l;i<=n;i++) p[i]=n+l-i;
            }
            else {
                // cout<<" ? "<<n<<" "<<k<<" "<<l<<endl;
                p[1]=1;
                for(int i=2;i<=l;i++) p[i]=n-l+i;
                for(int i=l+1;i<=n;i++) p[i]=n+2-i;
            }
        }
        else{
            if(l<=(n-1)/2){
                for(int i=1;i<=l;i++) p[i]=n-l+i;
                for(int i=l+1;i<=n;i++) p[i]=n+1-i;
            }
            else if(l>n/2+1){
                for(int i=1;i<l;i++) p[i]=i;
                for(int i=l;i<=n;i++) p[i]=n+l-i;
            }
            else if(n>4 && n%2==0 && l==n/2+1){
                // cout<<" & "<<n<<" "<<k<<" "<<l<<endl;
                p[n]=1;
                for(int i=1;i<l;i++) p[i]=i+1;
                for(int i=l;i<n;i++) p[i]=n+l-i;
            }
            else {
                // cout<<" ? "<<n<<" "<<k<<" "<<l<<endl;
                p[1]=1;
                for(int i=2;i<=l;i++) p[i]=n-l+i;
                for(int i=l+1;i<=n;i++) p[i]=n+2-i;
            }
        }
        
        for(int i=1;i<=n;i++) p[i]+=k-1;
        
        puts("Yes");
        for(int i=1;i<=n;i++) printf("%d ",p[i]);
        printf("\n");
        // check();
    }
    
}

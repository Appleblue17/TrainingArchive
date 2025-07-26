#include <bits/stdc++.h>
using namespace std;
const int N=1100;
int T,n;
int a[N][N];
int cur[N];

bool vis[N];

int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                scanf("%d",&a[i][j]);
            }
        }
        
        for(int i=1;i<=n;i++) vis[i]=0,cur[i]=n;
        
        for(int t=1;t<=n-1;t++){
            int x;
            for(int i=1;i<=n;i++){
                if(vis[i]) continue;
                while(cur[i] && vis[a[i][cur[i]]]) cur[i]--;
                if(!cur[i]) continue;
                
                x=a[i][cur[i]];
                break;
            }
            
            int y;
            for(int j=2;j<=n;j++){
                if(!vis[a[x][j]]){
                    y=a[x][j];
                    break;
                }
            }
            printf("%d %d\n",x,y);
            
            vis[x]=1;
        }
        // cout<<endl;
        
    }
    
}


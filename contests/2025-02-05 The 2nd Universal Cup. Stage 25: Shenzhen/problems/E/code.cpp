#include <bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int T,n,ans;
int c[N];

int cal(int x,int y){
    int z= x & y;
    if(!z) return (x | y);
    int t=30;
    while(!(z>>t & 1)) t--;
    // cout<<x<<" "<<y<<" "<<t<<endl;
    return (x | y | ((1<<(t+1))-1));
}

int main(){
    cin>>T;
    while(T--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++) c[i]=0;
        for(int i=1;i<=n;i++){
            int x; scanf("%d",&x);
            c[x]++;
        }
        sort(c+1,c+n+1);
        
        int ans=c[n];
        for(int i=1;i<n;i++) ans=max(ans,cal(c[i],c[n]));
        printf("%d\n",ans);
    }
}

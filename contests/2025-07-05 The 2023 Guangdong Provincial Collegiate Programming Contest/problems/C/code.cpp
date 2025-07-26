#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+5;
int T,n;
pair<int,int> p[N];

signed main(){
    cin>>T;
    while(T--){
        scanf("%lld",&n);
        for(int i=1;i<=n;i++){
            scanf("%lld%lld",&p[i].first,&p[i].second);
        }
        sort(p+1,p+n+1);
        
        int x=1,y=n,ans=0;
        while(x<y){
            int c=min(p[x].second,p[y].second);
            ans+=(p[y].first-p[x].first)*c;
            p[x].second-=c;
            p[y].second-=c;
            if(!p[x].second) x++;
            if(!p[y].second) y--;
        }
        
        printf("%lld\n",ans);
    }
    
}

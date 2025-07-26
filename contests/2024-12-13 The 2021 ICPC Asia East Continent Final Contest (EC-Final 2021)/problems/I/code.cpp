#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int T,n;
vector <int> G[N];
int a[1000010];
long long ans,s1,e1,l1;
int main(){
    cin>>T;
    while(T--){
        ans=s1=e1=l1=0;
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
            if(a[i]<1){
                s1++;
                ans += l1+e1;
            }
            if(a[i]==1){
                e1++;
                ans += (i-1);
            }
            if(a[i]>1){
                l1++;
                ans+=s1+e1;
            }
            //cout << ans << endl;
        }
        printf("%lld\n",ans);
    }
    
}

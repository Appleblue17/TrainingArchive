#include <bits/stdc++.h>
using namespace std;
#define int long long
int T,a,b,k;

__int128 ans;

void wt(__int128 x){
    if(x>=10) wt(x/10);
    putchar('0'+x%10);
}
mt19937 rng(time(NULL));

int cal(int a,int b,int k){
    int tot=1e18;
    for(int i=a;i<=a+k;i++){
        for(int j=b;j<=b+k;j++){
            tot=min(tot,i/__gcd(i,j)*j);
        }
    }
    return tot;
}

void upd(__int128 x){
    if(!ans) ans=x;
    else ans=min(ans,x);
}

signed main(){
    scanf("%lld",&T);
    while(T--){
        scanf("%lld%lld%lld",&a,&b,&k);
        // a=rng()%1000+1,b=rng()%1000+1,k=rng()%1000+1;
        
        int tot=cal(a,b,k);
        // cout<<tot<<" ";
        if(a>b) swap(a,b);
        ans=0;
        for(int l=1,r;l<=min(a-1,b-1);l=r+1){
            r=min((a-1)/((a-1)/l),(b-1)/((b-1)/l));
            // cout<<a/l<<" "<<b/l<<" "<<a/r<<" "<<b/r<<endl;
            // cout<<l<<" "<<r<<endl;
            
            int x=(a-1)/l+1,y=(b-1)/l+1;
            int lim=min((a+k)/x,(b+k)/y);
            // cout<<l<<" "<<r<<": "<<x<<" "<<y<<" "<<lim<<endl;
            if(l<=lim){
                __int128 tmp=(__int128)x*(__int128)y*(__int128)l;
                upd(tmp);
            }
        }
        for(int l=a,r;l<=b-1;l=r+1){
            r=(b-1)/((b-1)/l);
            // cout<<a/l<<" "<<b/l<<" "<<a/r<<" "<<b/r<<endl;
            // cout<<l<<" "<<r<<endl;
            
            int x=1,y=(b-1)/l+1;
            int lim=min((a+k)/x,(b+k)/y);
            // cout<<l<<" "<<r<<": "<<x<<" "<<y<<" "<<lim<<endl;
            if(l<=lim){
                __int128 tmp=(__int128)x*(__int128)y*(__int128)l;
                upd(tmp);
            }
        }
        if(b-a<=k) upd(b);
        
        wt(ans);
        putchar('\n');
        // cout<<endl;
        // if(tot!=ans){
        //     cout<<a<<" "<<b<<" "<<k<<endl;
        //     cout<<tot<<" ";
        //     wt(ans);
        //     exit(0);
        // }
    }
    
}

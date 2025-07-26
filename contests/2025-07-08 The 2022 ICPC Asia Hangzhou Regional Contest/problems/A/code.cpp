#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e5+5;
int n,m,sum;

int exgcd(int a,int b,int &x,int &y){
    if(!b){
        x=1,y=0;
        return a;
    }
    int tmp=exgcd(b,a%b,y,x);
    y-=a/b*x;
    return tmp;
}

signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        int x; scanf("%lld",&x); sum=(sum+x)%m;
    }
    int A=n%m,B=1ll*n*(n+1)/2%m;
    int gA=__gcd(A,m),gB=__gcd(B,m);
    
    int x,y;
    exgcd(A,m,x,y);
    int xA=(x%m+m)%m;
    exgcd(B,m,x,y);
    int xB=(x%m+m)%m;
    
    int g=__gcd(gA,gB);
    exgcd(gA,gB,x,y);
    x=(x%m+m)%m;
    y=(y%m+m)%m;
    
    int res=(m-sum)%m;
    int z=0;
    if(res) z=(res-1)/g+1;
    
    int ans=z*g-res;
    cout<<ans<<endl;
    int X=x*xA%m*z%m,Y=y*xB%m*z%m;
    cout<<X<<" "<<Y<<endl;
    
    // if(ans!=(sum+X*A%m+Y*B%m)%m){
    //     cout<<ans<<" "<<(sum+X*A%m+Y*B%m)%m<<endl;
    //     exit(1);
    // }
}

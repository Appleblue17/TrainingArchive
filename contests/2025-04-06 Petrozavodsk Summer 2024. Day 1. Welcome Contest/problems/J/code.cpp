#include <bits/stdc++.h>
using namespace std;
int T,n,m,x,y;

bool solve(int n,int m,int x,int y){
    if(n>m) swap(n,m),swap(x,y);
    if(n==1) return 0;
    else if(n==2){
        if(y%4==3 || y%4==0) return 1;
        else if(y%4==1){
            if(m%4==1 || m%4==2) return 0;
            else return 1;
        }
        else if(y%4==2){
            if(m%4==2 || m%4==3) return 0;
            else return 1;
        }
    }
    else if(n==3 && m==3){
        if(x==2 && y==2) return 0;
        else return 1;
    }
    else if(n==3 && m==5){
        if((x==1 || x==3) && y==3) return 1;
        else return (x+y)%2;
    }
    else if(n%2==1 && m%2==1){
        return (x+y)%2;
    }
    else return 1;
}

signed main(){
    // freopen("1.txt","w",stdout);
    cin>>T;
    while(T--){
        scanf("%d%d%d%d",&n,&m,&x,&y);
        if(solve(n,m,x,y)) puts("Annapurna");
        else puts("Brahma");
    }
    
    // for(n=2;n<=10;n++){
    //     for(m=1;m*n<=40;m++){
    //         cout<<"[ "<<n<<" "<<m<<" ]"<<endl;
    //         for(int i=1;i<=n;i++){
    //             for(int j=1;j<=m;j++){
    //                 cout<<solve(n,m,i,j)<<" ";
    //             }
    //             cout<<endl;
    //         }
    //     }
    // }
    
}

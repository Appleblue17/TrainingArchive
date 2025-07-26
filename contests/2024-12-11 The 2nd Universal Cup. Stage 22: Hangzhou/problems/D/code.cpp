#include <bits/stdc++.h>
using namespace std;
const int N=4e5+5;
int T,n;
int a[N],id;

bool check(){
    int sum=0;
    for(int i=1;i<n*2;i+=2) sum+=a[i]*a[i+1];
    int tot=a[1]*a[n*2];
    for(int i=2;i<n*2-1;i+=2) tot*=a[i]+a[i+1];
    cout<<" check "<<sum<<" "<<tot<<endl;
    return (sum==tot);
}
void go(int x){
    a[++id]=-(x-1); a[++id]=x;
    a[++id]=-(x-1); a[++id]=x;
    a[++id]=(x-1); a[++id]=-x;
    a[++id]=(x-1); a[++id]=-x;
}

int main(){
    cin>>T;
    while(T--){
        scanf("%d",&n);
        id=0;
        if(n%4==1){
            a[++id]=1;
            for(int i=1;i<=(n-1)/4;i++){
                a[++id]=2; a[++id]=-1;
                a[++id]=2; a[++id]=-1;
                a[++id]=-2; a[++id]=1;
                a[++id]=-2; a[++id]=1;
            }
            a[++id]=1;
        }
        if(n%4==2){
            a[++id]=1; a[++id]=-3; a[++id]=-3;
            for(int i=1;i<=(n-2)/4;i++){
                go(3);
            }
            a[++id]=1;
        }
        if(n%4==3){
            a[++id]=1; a[++id]=-10; a[++id]=6; a[++id]=6; a[++id]=-10;
            for(int i=1;i<=(n-3)/4;i++){
                go(10);
            }
            a[++id]=1;
        }
        if(n%4==0){
            a[++id]=1; a[++id]=-15; a[++id]=10; a[++id]=-1; a[++id]=-1; a[++id]=10; a[++id]=-15;
            for(int i=1;i<=(n-4)/4;i++){
                go(15);
            }
            a[++id]=1;
        }
        for(int i=1;i<=n*2;i++) printf("%d ",a[i]);
        putchar('\n');
        // check();
    }
    
}

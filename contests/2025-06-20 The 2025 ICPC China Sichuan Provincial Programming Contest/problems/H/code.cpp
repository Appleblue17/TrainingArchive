#include<bits/stdc++.h>
using namespace std;
void solve(){
    int a,b,c,d;
    scanf("%d%d%d%d",&a,&b,&c,&d);
    if(a == c && b == d){
        printf("0\n");
        return;
    }
    else if(a == c && abs(b-d)<=2){
        printf("2\n");
    }
    else if(b == d && abs(a-c)<=2){
        printf("2\n");
    }
    else{
        printf("%d\n",(max(abs(a-c),abs(b-d))+1)/2);
    }
}
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        solve();
    }
}

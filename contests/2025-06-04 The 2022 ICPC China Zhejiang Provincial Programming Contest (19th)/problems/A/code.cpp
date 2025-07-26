#include <bits/stdc++.h>
using namespace std;
int T,a,b;
int main(){
    cin>>T;
    while(T--){
        scanf("%d%d",&a,&b);
        if(a==b) puts("0");
        else if(a<b){
            if((b-a)%2==0){
                if(((b-a)/2)%2==1) puts("2");
                else{
                    puts("3");
                }
            }
            else puts("1");
        }
        else{
            if((a-b)%2==0) puts("1");
            else puts("2");
        }
    }
}

#include <bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int T,l,r;


int main(){
    cin>>T;
    while(T--){
        scanf("%d%d",&l,&r);
        if(l%2==0 && r%2==1){
            puts("Bob");
        }
        if(l%2==0 && r%2==0){
            if(2*l>=r) puts("Alice");
            else puts("Bob");
        }
        if(l%2==1 && r%2==1){
            puts("Alice");
        }
        if(l%2==1 && r%2==0){
            if(2*l<=r) puts("Alice");
            else puts("Bob");
        }
    }
}

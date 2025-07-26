#include <bits/stdc++.h>
using namespace std;

int main(){
    for(int i=1;i<=100/2;i++) putchar('1'),putchar('8');
        putchar('\n');
    for(int i=2,t=100;i<=10;i++,t*=2){
        for(int j=1;j<=t;j++) putchar('9');
        putchar('\n');
    }
}

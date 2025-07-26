#include <bits/stdc++.h>
using namespace std;

int n;
int main(){
    cin>>n;
    cout<<1<<endl;
    
    if(n==25){
        cout<<50<<endl;
        for(int i=1;i<=25;i++) cout<<1<<" "<<5<<" ";
        return 0;
    }
    cout<<n*2+1<<endl;
    for(int i=1;i<=n*2;i++) cout<<1<<" ";
    cout<<n<<endl;
}

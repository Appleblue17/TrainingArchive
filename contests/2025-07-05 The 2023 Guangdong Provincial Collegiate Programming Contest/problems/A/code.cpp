#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int T;
int x,y;
int p[N],n;

int main(){
    cin>>T;
    while(T--){
        cin>>x;
        cin>>n;
        for(int i=1;i<=n;i++) cin>>p[i];
        cin>>y;
        
        int tot=y-x+1;
        for(int i=1;i<=n;i++) tot-=(x<=p[i] && p[i]<=y);
        cout<<tot<<endl;
    }
    
}

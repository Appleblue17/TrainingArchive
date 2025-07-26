#include<bits/stdc++.h>
using namespace std;
int n;
string s[1005]; int a[1005];
int rk[15];
int main(){
    cin>>n;
    vector<int> vec;
    for(int i=1; i<=n; ++i) cin>>s[i]>>a[i], ++rk[a[i]];
    for(int i=10; i>=1; --i) rk[i]+=rk[i+1];
    string opt="";
    for(int i=1; i<=n; ++i){
        if(s[i].size()>rk[a[i]+1]+1){
            opt+=s[i].substr(0, s[i].size()-rk[a[i]+1]-1);
        }
    }
    cout<<"Stage: ";
    if(opt.size()>0){
        opt[0]=opt[0]-'a'+'A';
    }
    cout<<opt<<endl;
}

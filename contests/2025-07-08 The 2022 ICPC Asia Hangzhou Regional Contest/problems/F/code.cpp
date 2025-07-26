#include<bits/stdc++.h>
using namespace std;
int n, m;
unordered_map<string, bool> h;
int main(){
    cin>>n;
    for(int i=1; i<=n; ++i){
        cin>>m;
        bool flag=0;
        
        for(int j=1; j<=m; ++j){
            string s; cin>>s; bool flag2=0;
            if(h.find(s)!=h.end()) continue;
            for(int k=0; k+3<=(int)s.size(); ++k) if(s.substr(k, 3)=="bie"){
                flag=1; flag2=1; break;
            }
            if(flag2) cout<<s<<endl, h[s]=1;
        }
        if(!flag) cout<<"Time to play Genshin Impact, Teacher Rice!"<<endl;
    }
}

#include <bits/stdc++.h>
using namespace std;
#define int long long
#define int128 __int128
const int N=2e6+5,B=1e6;
int T,n_,k_;
int128 n,k;

int128 pw(int128 x,int k){
    int128 tot=1;
    for(int i=1;i<=k;i++) tot*=x;
    return tot;
}
int128 p[N];
int id;

int sqt(int x){
    if(x<0) return -1;
    int y=sqrt(x);
    while(y*y<x) y++;
    while(y*y>x) y--;
    return (y*y==x)?y:-1;
}


signed main(){
    cin>>T;
    while(T--){
        cin>>n_>>k_;
        n=n_,k=k_;
        int ans=0;
        
        id=0;
        
        for(int t=1;pw(t,k-1)<=n && t<=B;t++) p[++id]=pw(t,k);
        
        int cur=1;
        for(int i=1;i<=id;i++){
            while(cur+1<=id && p[cur]<p[i]+n) cur++;
            if(p[cur]==p[i]+n) ans++;
        }
        
        if(k==3){
            for(int d=1;d<=B;d++){
                if(n%d) continue;
                int delta2=9*d*d-12*(d*d-n/d);
                int delta=sqt(delta2);
                if(delta==-1) continue;
                for(int c=-1;c<=1;c+=2){
                    if((-3*d+delta*c)%6) continue;
                    int a=(-3*d+delta*c)/6;
                    if(a>0 && a+d>B){
                        ans++;
                        // cout<<a<<endl;
                    }
                }
            }
        }
        
        cout<<ans<<endl;
    }
}

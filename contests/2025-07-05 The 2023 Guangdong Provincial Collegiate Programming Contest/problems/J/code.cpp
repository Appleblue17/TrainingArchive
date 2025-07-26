#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e5+5;
int T,x,y,A,B;
int sx,sy,sA,sB;

int d[N],id;

int p[N],pid;
int q[N],qid;

void check(int a,int b){
    // assert(a>=2 && a<=sA);
    // assert(b>=2 && b<=sB);
    
    // int tx=sx,ty=sy;
    // pid=qid=0;
    // while(sx) p[++pid]=sx%a,sx/=a;
    // while(sy) q[++qid]=sy%b,sy/=b;
    
    // assert(pid==qid);
    // for(int i=1;i<=pid;i++){
    //     assert(p[i]<a);
    //     assert(q[i]<b);
    //     assert(p[i]==q[i]);
    // }
}

void solve(){
    bool swp=0;
    if(x>y){
        swap(x,y);
        swap(A,B);
        swp=1;
    }
    
    if(x==y){
        puts("YES");
        cout<<2<<" "<<2<<endl;
        check(2,2);
        return ;
    }
    
    
    int z=y-x;
    id=0;
    for(int i=1;i*i<=z;i++){
        if(z%i==0){
            d[++id]=i;
            if(i*i!=z) d[++id]=z/i;
        }
    }
    for(int i=1;i<=id;i++){
        int q=d[i],del=z/d[i];
        int a=max(q+1,x/(q+1)+1);
        int p=x-a*q;
        
        if(p<0 || p>=a) continue;
        int b=a+del;
        if(a<=A && b<=B){
            puts("YES");
            if(swp) swap(a,b);
            cout<<a<<" "<<b<<endl;
            check(a,b);
            return ;
        }
    }
    
    for(int b=2;b<=B && b*b<=y;b++){
        pid=0;
        int u=y,mx=0;
        while(u){
            p[++pid]=u%b;
            mx=max(mx,p[pid]);
            u/=b;
        }
        
        int l=max(2ll,mx+1),r=min(A,b),a=-1;
        while(l<=r){
            int mid=(l+r)>>1;
            
            long long sum=0;
            for(int i=pid;i>=1;i--){
                sum=(sum*mid+p[i]);
            }
            if(sum>=x){
                r=mid-1;
                if(sum==x){
                    a=mid;
                    break;
                }
            }
            else l=mid+1;
        }
        if(a!=-1){
            puts("YES");
            if(swp) swap(a,b);
            cout<<a<<" "<<b<<endl;
            check(a,b);
            return ;
        }
    }
    
    // cout<<sx<<" "<<sy<<" "<<sA<<" "<<sB<<endl;
    puts("NO");
    // exit(1);
}

signed main(){
    cin>>T;
    while(T--){
        cin>>x>>y>>A>>B;
        sx=x,sy=y,sA=A,sB=B;
        solve();
    }
    
}

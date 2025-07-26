#pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e5+5;
int T,n,k;
struct abc{
    int c,w,f;
}p[N];
bool operator <(abc X,abc Y){
    return X.f<Y.f;
}
signed main(){
    // freopen("1.txt","r",stdin);
    // freopen("2.txt","w",stdout);
    scanf("%lld",&T);
    while(T--){
        scanf("%lld%lld",&n,&k);
        for(int i=1;i<=n;i++){
            scanf("%lld%lld%lld",&p[i].c,&p[i].w,&p[i].f);
        }
        sort(p+1,p+n+1);
        
        int ans=0,cur=n;
        bool hole=0;
        while(cur){
            if(p[cur].w==1 && hole){
                p[cur].c--; hole=0;
                if(!p[cur].c) cur--;
                // cout<<"fill\n";
            }
            
            if(p[cur].c*p[cur].w>=k){
                // cout<<" "<<cur<<": "<<p[cur].c<<" "<<p[cur].w<<endl;
                int d=p[cur].c/(k/p[cur].w);
                // cout<<"buy "<<d<<endl;
                p[cur].c-=d*(k/p[cur].w);
                ans+=p[cur].f*d;
                
                // cout<<p[cur].f<<" *"<<d<<endl;
                if(!p[cur].c) cur--;
                continue;
            }
            
            int lft=k;
            ans+=p[cur].f;
            
            // cout<<p[cur].f<<": ";
            
            
            while(cur){
                if(p[cur].w==1 && hole){
                    p[cur].c--; hole=0;
                }
                int num=lft/p[cur].w;
                // for(int t=1;t<=min(num,p[cur].c);t++) cout<<p[cur].f<<" ";
                
                if(num<p[cur].c){
                    p[cur].c-=num;
                    lft-=num*p[cur].w;
                    break;
                }
                else{
                    lft-=p[cur].c*p[cur].w;
                    p[cur].c=0;
                    cur--;
                }
            }
            // cout<<endl;
            
            if(!cur) break;
            if(lft){
                assert(lft==1);
                hole=1;
                // cout<<"hole\n";
            }
            
        }
        printf("%lld\n",ans);
    }
    
}

#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e5+5;
int T,n,f;
int ans;
vector <int> ANS;

struct abc{
    int l,r,num;
}p[N],q[N];
int id;
bool cmp1(abc X,abc Y){
    return X.l<Y.l;
}
bool cmp2(abc X,abc Y){
    return X.r>Y.r;
}

signed main(){
    cin>>T;
    while(T--){
        ans=0;
        ANS.clear();
        
        scanf("%lld%lld",&n,&f);
        for(int i=1;i<=n;i++){
            int l,r; scanf("%lld%lld",&l,&r);
            p[i]=(abc){l,r,i};
            ans+=r-l;
        }
        sort(p+1,p+n+1,cmp1);
        
        int mx=0,nw=f;
        id=0;
        
        for(int i=1;i<=n;i++){
            if(p[i].r<=mx) q[++id]=p[i];
            else{
                mx=p[i].r;
                
                if(p[i].r>=f){
                    ans+=max(0ll,p[i].l-nw);
                    ANS.push_back(p[i].num);
                    nw=p[i].r;
                }
                else q[++id]=p[i];
            }
        }
        
        sort(q+1,q+id+1,cmp2);
        for(int i=1;i<=id;i++){
            assert(q[i].l<=nw);
            nw=q[i].r;
            
            ANS.push_back(q[i].num);
        }
        
        printf("%lld\n",ans);
        for(int x: ANS) printf("%lld ",x);
        printf("\n");
        
    }
    
}

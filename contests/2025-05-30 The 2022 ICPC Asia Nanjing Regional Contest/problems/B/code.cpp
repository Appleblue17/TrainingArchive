#include "bits/stdc++.h"
using namespace std;
#define int long long
const int N=1e6+5,INF=1e18;

int T,n,k,q;
int a[N];
char S[N];

int f[N],g[N];

int calA(int pos){
    return f[pos]+g[pos]-a[pos]*2;
}
int calB(int pos){
    if(S[pos]=='1') return INF;
    int mn=INF,tot=INF;
    
    int L=pos,R=pos;
    while(L-1>=pos-k+1 && S[L]=='0') L--;
    while(R+1<=pos+k-1 && S[R]=='0') R++;
    
    // cout<<pos<<" "<<L<<" "<<R<<endl;
    
    for(int i=pos-k+1;i<=pos-1;i++){
        int l=pos+1,r=i+k;
        if(r<=R) mn=min(mn,g[r]);
        if(i>=L) tot=min(tot,f[i]+mn);
        // cout<<f[i]<<" "<<mn<<endl;
    }
    return tot;
}


int que[N],head,tail;

signed main(){
    // freopen("1.txt","r",stdin);
    // freopen("2.txt","w",stdout);
    scanf("%lld",&T);
    while(T--){
        scanf("%lld%lld",&n,&k);
        for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
        scanf("\n%s",S+1);
        S[0]=S[n+1]='1';
        
        for(int i=0;i<=n+1;i++) f[i]=g[i]=INF;
        
        head=1,tail=1; que[1]=0;
        f[0]=0;
        for(int i=1;i<=n+1;i++){
            f[i]=f[que[head]]+a[i];
            if(S[i]=='1'){
                head=tail=1;
                que[1]=i;
            }
            else{
                while(head<=tail && que[head]<=i-k) head++;
                while(head<=tail && f[que[tail]]>=f[i]) tail--;
                que[++tail]=i;
            }
        }
        
        
        g[n+1]=0;
        head=1,tail=1; que[1]=n+1;
        for(int i=n;i>=0;i--){
            g[i]=g[que[head]]+a[i];
            if(S[i]=='1'){
                head=tail=1;
                que[1]=i;
            }
            else{
                while(head<=tail && que[head]>=i+k) head++;
                while(head<=tail && g[que[tail]]>=g[i]) tail--;
                que[++tail]=i;
            }
        }
        // for(int i=1;i<=n;i++) cout<<f[i]<<" "; cout<<endl;
        // for(int i=1;i<=n;i++) cout<<g[i]<<" "; cout<<endl;
        
        scanf("%lld",&q);
        while(q--){
            int pos,val;
            scanf("%lld%lld",&pos,&val);
            
            int A=calA(pos),B=calB(pos);
            // cout<<"   "<<A<<" "<<B<<endl;
            int ans=min(A+val,B);
            printf("%lld\n",ans);
        }
        
    }
    
    
}


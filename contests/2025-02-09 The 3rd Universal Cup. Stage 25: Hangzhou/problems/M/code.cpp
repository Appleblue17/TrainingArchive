#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e5+5,INF=1e9;
int T,n,k,ans1,ans2;
int a[N],b[N];


int d[N],id;
void decomp(int x){
    id=0;
    for(int i=1;i*i<=x;i++){
        if(x%i==0){
            d[++id]=i;
            if(i*i!=x) d[++id]=x/i;
        }
    }
}


int sta[N],cur;
int ls[N],rs[N];
void ins(int x){
    int sav=cur;
    while(cur && b[sta[cur]]>b[x]) cur--;
    if(cur) rs[sta[cur]]=x;
    if(cur<sav) ls[x]=sta[cur+1];
    sta[++cur]=x;
}


bool dfs(int l,int r,int x,int fa){
    if(fa && b[x]%b[fa]) return 0;
    if(l>=r) return 1;
    return dfs(l,x-1,ls[x],x) && dfs(x+1,r,rs[x],x);
}

bool check(int x){
    for(int i=1;i<=n;i++) b[i]=a[i]+x;
    
    // cout<<"check: "<<x<<"  ";
    // for(int i=1;i<=n;i++) cout<<b[i]<<" ";
    // cout<<endl;
    
    cur=0;
    for(int i=1;i<=n;i++) ls[i]=rs[i]=0;
    for(int i=1;i<=n;i++) ins(i);
    
    // for(int i=1;i<=n;i++) cout<<ls[i]<<" "<<rs[i]<<endl;
    // cout<<sta[1];
    // exit(0);
    return dfs(1,n,sta[1],0);
}

signed main(){
    cin>>T;
    while(T--){
        ans1=ans2=0;
        
        scanf("%lld%lld",&n,&k);
        int mn=INF;
        for(int i=1;i<=n;i++) scanf("%lld",&a[i]),mn=min(mn,a[i]);
        
        int g=0;
        for(int i=1;i<n;i++) g=__gcd(g,abs(a[i]-a[i+1]));
        
        if(g==0){
            printf("%lld %lld\n",k,k*(k+1)/2);
            continue;
        }
        
        decomp(g);
        // cout<<g<<endl;
        // for(int i=1;i<=id;i++) cout<<d[i]<<" ";
        // cout<<endl;
        // return 0;
        
        for(int t=1;t<=id;t++){
            int x=d[t]-mn;
            if(x<1 || x>k) continue;
            int ret=check(x);
            // cout<<x<<" "<<ret<<endl;
            if(ret) ans1++,ans2+=x;
        }
        printf("%lld %lld\n",ans1,ans2);
    }
    
}

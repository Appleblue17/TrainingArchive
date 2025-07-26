#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=550,mod=1e9+7;
int n,m,ans;
int pos[N],v[N];

void gmod(int &x){
    x%=mod;
}
int ksm(int a,int x){
    int tot=1;
    while(x){
        if(x & 1ll) tot=tot*a%mod;
        a=a*a%mod;
        x>>=1ll;
    }
    return tot;
}

struct frac{
    int x,y;
    int num,pos;
}p[N*N];
int cnt;
bool operator <(frac X,frac Y){
    return X.x*Y.y<Y.x*X.y;
}

int dp[N],siz;
void multi(int A,int B){
    // *(A+Bx)
    for(int i=siz;i>=0;i--){
        gmod(dp[i+1]+=dp[i]*B%mod);
        gmod(dp[i]=dp[i]*A%mod);
    }
    siz++;
}
void divide(int A,int B){
    // /(A+Bx)
    int iA=ksm(A,mod-2);
    gmod(dp[0]=dp[0]*iA%mod);
    for(int i=1;i<=siz;i++) gmod(dp[i]=(dp[i]+mod-B*dp[i-1]%mod)%mod*iA%mod);
    siz--;
}

signed main(){
//	freopen("1.txt","r",stdin);
    ios::sync_with_stdio(false);
    cin.tie(0);
    dp[0]=1;
    
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>pos[i],pos[i]=-pos[i];
    for(int i=1;i<=m;i++) cin>>v[i];
    sort(pos+1,pos+n+1);
    
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            p[++cnt]={pos[j],v[i],i,j};
        }
    }
    sort(p+1,p+cnt+1);
    int invn=ksm(n,mod-2);
    
    int tme=0,lst=1;
    for(int i=1;i<=cnt;i++){
        frac& u=p[i];
        int nw=u.x*ksm(u.y,mod-2)%mod;
        int pos=u.pos;
        
//        cout<<" "<<1.0*u.x/u.y<<": "<<u.num<<" "<<pos<<endl;
        
        if(pos>1) divide((n-(pos-1))*invn%mod,(pos-1)*invn%mod);
        multi((n-pos)*invn%mod,pos*invn%mod);
        
        int tot=0;
        for(int j=0;j<(m+1)/2;j++) gmod(tot+=dp[j]);
        
//        cout<<"  ";
//        for(int j=0;j<=m;j++) cout<<dp[j]<<" ";
//        cout<<" => "<<tot<<" "<<lst;
//        cout<<endl;
        
        gmod(ans+=(nw+mod-tme)%mod*lst%mod);
        lst=tot;
        
        tme=nw;
    }
    cout<<ans;
}

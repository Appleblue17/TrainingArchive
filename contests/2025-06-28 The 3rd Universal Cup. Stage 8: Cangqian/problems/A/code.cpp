#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e6+5,INF=1e18;
int T,len,m;
char S[N];
int a[N];

int pw[18];

signed main(){
    // freopen("1.txt","w",stdout);
    pw[0]=1;
    for(int i=1;i<=12;i++) pw[i]=pw[i-1]*10;
    
    scanf("%lld",&T);
    while(T--){
        scanf("\n%s",S);
        scanf("%lld",&m);
        len=strlen(S)-1;
        for(int i=0;i<=len;i++) a[i]=S[len-i]-'0';
        
        
        a[0]++;
        for(int i=0;i<=len;i++) a[i+1]+=a[i]/10,a[i]%=10;
        if(a[len+1]) len++;
        
        int r=0;
        for(int i=len;i>=0;i--){
            r=(r*10%m+a[i])%m;
        }
        int ans=(m-r)%m;
        
        
        int cnt=0,tmp=m;
        while(tmp) cnt++,tmp/=10;
        
        int rem=0;
        for(int i=0;i<=len;i++){
            int x=0;
            for(int j=i+cnt-1;j>=i;j--) x=x*10+a[j];
            
            if(m==x){
                ans=0;
            }
            else if(rem<INF){
                int tmp=m-x+(m<x)*pw[cnt];
                if(tmp-1==0 || i<=9) ans=min(ans,(tmp-1)*pw[i]+(1+rem));
            }
            
            if(i<=9 || a[i]==9) rem+=(9-a[i])*pw[i];
            else rem=INF;
        }
        
        // cout<<"  "<<ans<<endl;
        
        a[0]+=ans;
        for(int i=0;i<=len;i++){
            a[i+1]+=a[i]/10;
            a[i]%=10;
        }
        if(a[len+1]) printf("%lld",a[len+1]);
        for(int i=len;i>=0;i--) printf("%lld",a[i]);
        printf("\n");
        
        
        for(int i=0;i<=len+10;i++) a[i]=0;
    }
    
    
    
}

#pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;
const int N=550,M=2e4+5,mod1=998244353,mod2=1e9+7,mod3=1e9+9;
int n,k;
char S[M];
int sum[M],has1[N],has2[N],has3[N];
int HAS1,HAS2,HAS3;

int cal(int *sum,int mod){
    int tot=0;
    for(int i=k-1;i>=0;i--){
        tot=(1ll*tot*10%mod+sum[i])%mod;
    }
    return tot;
}
bool chk(int *sum,int d){
    for(int i=0;i<k;i++) if(sum[i]!=d) return 0;
    return 1;
}


map < tuple<int,int,int>, int> mp;

int main(){
    scanf("%d%d",&n,&k);
    
    int tot1=0,tot2=0;
    for(int i=1;i<=n;i++){
        scanf("\n%s",S);
        int len=strlen(S);
        
        for(int j=0;j<=k;j++) sum[j]=0;
        for(int j=0;j<len;j++) sum[j%k]+=(S[len-1-j]-'0');
        while(1){
            for(int j=0;j<k;j++){
                sum[j+1]+=sum[j]/10;
                sum[j]%=10;
            }
            if(!sum[k]) break;
            else sum[0]+=sum[k],sum[k]=0;
        }
        
        has1[i]=cal(sum,mod1);
        has2[i]=cal(sum,mod2);
        has3[i]=cal(sum,mod3);
        tot1+=chk(sum,0);
        tot2+=chk(sum,9);
        // cout<<has1[i]<<" "<<has2[i]<<" "<<has3[i]<<endl;
        // for(int j=k-1;j>=0;j--) cout<<sum[j];
        // cout<<endl;
    }
    
    for(int j=0;j<k;j++) sum[j]=9;
    HAS1=cal(sum,mod1);
    HAS2=cal(sum,mod2);
    HAS3=cal(sum,mod3);
    
    int ans=1ll*(tot1+2)*(tot1+1)/2*tot1/3 + 1ll*(tot2+2)*(tot2+1)/2*tot2/3;
    for(int i=1;i<=n;i++){
        mp[make_tuple(has1[i],has2[i],has3[i])]++;
        
        for(int j=i;j<=n;j++){
            for(int c=1;c<=2;c++){
                int w1=(HAS1*c%mod1+mod1-(has1[i]+has1[j])%mod1)%mod1;
                int w2=(HAS2*c%mod2+mod2-(has2[i]+has2[j])%mod2)%mod2;
                int w3=(HAS3*c%mod3+mod3-(has3[i]+has3[j])%mod3)%mod3;
                ans+=mp[make_tuple(w1,w2,w3)];
                
            }
            
        }
    }
    cout<<ans;
}

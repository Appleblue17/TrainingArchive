#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=3e5+5,mod=1e9+7;

int T,n;
int a[N],s[N];
int ksm(int a,int x){
    int tot=1;
    while(x){
        if(x & 1ll) tot=tot*a%mod;
        a=a*a%mod;
        x>>=1ll;
    }
    return tot;
}

signed main(){
    cin>>T>>n;
    
    int sum=1;
    for(int i=1;i<=n;i++) scanf("%d",&a[i]),sum=sum*a[i]%mod;
    
    sort(a+1,a+n+1);
    
    for(int i=1;i<=n;i++){
        int del=a[i]-a[i-1];
        if(T>del*(n-i+1)){
            s[i]+=del;
            T-=(n-i+1)*del;
        }
        else{
            int x=T/(n-i+1),r=T%(n-i+1);
            s[i]+=x;
            s[n-r+1]++;
            break;
        }
    }
    int tot=1;
    for(int i=1;i<=n;i++) s[i]+=s[i-1],tot=tot*s[i]%mod;
    
    // for(int i=1;i<=n;i++) cout<<s[i]<<" "; cout<<endl;
    
    cout<<tot<<" "<<sum<<endl;
}

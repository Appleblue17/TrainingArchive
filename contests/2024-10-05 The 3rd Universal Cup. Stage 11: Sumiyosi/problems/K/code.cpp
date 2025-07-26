#include <bits/stdc++.h>
using namespace std;
// #define int long long
const int N=110,M=1e5+5,INF=1e9,mod=998244353;

//void gmod(int &x){
//	if(x>=mod) x-=mod;
//}
//
//int ksm(int a,int x){
//	int tot=1;
//	while(x){
//		if(x & 1ll) tot=tot*a%mod;
//		a=a*a%mod;
//		x>>=1ll;
//	}
//	return tot;
//}
//
//int mul[N],inv[N];
//void init(int lim){
//	mul[0]=inv[0]=1;
//	for(int i=1;i<=lim;i++) mul[i]=mul[i-1]*i%mod;
//	inv[lim]=ksm(mul[lim],mod-2);
//	for(int i=lim-1;i>=1;i--) inv[i]=inv[i+1]*(i+1)%mod;
//	
//}
//int C(int m,int n){
//	if(m<0 || n<0 || m<n) return 0;
//	return mul[m]*inv[n]%mod*inv[m-n]%mod;
//}

int n,a[N],ans=INF;
bitset <M> f,g;

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>n; n--;
    int sum=0;
    for(int i=1;i<=n;i++) cin>>a[i],sum+=a[i];
    
    for(int t=0;t<=n;t++){
        f.reset();
        g.reset();
        
        f.set(0,1);
        for(int i=t;i>=1;i--) f = (f<<a[i]) | (f>>a[i]);
        g.set(0,1);
        for(int i=t+1;i<=n;i++) g = (g<<a[i]) | (g>>a[i]);
        
        int tot1=0,tot2=0;
        while(!f[tot1]) tot1++;
        while(!g[tot2]) tot2++;
        ans=min(ans,(sum+tot1+tot2)/2);
//        cout<<tot1<<" "<<tot2<<endl;
    }
    cout<<ans;
}

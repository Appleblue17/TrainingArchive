#pragma GCC optimize(2)
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,mod;

void gmod(int &x){
	x+=x>>31 & mod;
}
int ksm(int a,int x){
	if(x<0) return 0;
	int tot=1;
	while(x){
		if(x & 1ll) tot=1ll*tot*a%mod;
		a=1ll*a*a%mod;
		x>>=1ll;
	}
	return tot;
}
int ID(int x){
	if(x & 1ll) return mod-1;
	else return 1;
}
int mul[N],inv[N],pw2[N],ipw2[N];
int C(int m,int n){
	if(m<0 || n<0 || m<n) return 0;
	return 1ll*mul[m]*inv[n]%mod*inv[m-n]%mod;
}
void init(int lim){
	mul[0]=inv[0]=1;
	for(int i=1;i<=lim;i++) mul[i]=1ll*mul[i-1]*i%mod;
	inv[lim]=ksm(mul[lim],mod-2);
	for(int i=lim-1;i>=1;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
	
	pw2[0]=ipw2[0]=1;
	for(int i=1;i<=lim;i++) pw2[i]=pw2[i-1]*2%mod;
	for(int i=1;i<=lim;i++) ipw2[i]=1ll*ipw2[i-1]*inv[2]%mod;
}

int p[N],f[N];
int ans[N];

signed main(){
    cin>>n>>mod;
    init(N-5);
    int B=sqrt(n);
    for(int k=1;k<B;k++){
		for(int i=0;i<k;i++) p[i]=0;
		p[k]=1;
		for(int i=k+1;i<=n;i++) p[i]=(p[i-1]*2%mod+mod-p[i-k-1])%mod;
		for(int i=k;i<=n;i++) gmod(ans[i]+=p[i]-mod);
    }
    for(int r=1;r<=n/B;r++){
		for(int i=0;i<r;i++) f[i]=0;
		for(int i=r;i<=n;i++) f[i]=1ll*(f[i-r]+1ll*ipw2[r*(B-1)]*C(i-r*B,r-1)%mod)%mod*ipw2[r]%mod;
		for(int pos=r;pos<=n;pos++) gmod(ans[pos]+=1ll*f[pos]*ID(r-1)%mod*pw2[pos-r+1]%mod-mod);
    }
	for(int pos=1;pos<=n;pos++) printf("%lld ",ans[pos]);
}

#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=8080,mod=998244353,inv2=(mod+1)/2;

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

int mul[N],inv[N],invv[N],S2[N][N];
void init(int lim){
	mul[0]=inv[0]=1;
	for(int i=1;i<=lim;i++) mul[i]=mul[i-1]*i%mod;
	inv[lim]=ksm(mul[lim],mod-2);
	for(int i=lim-1;i>=1;i--) inv[i]=inv[i+1]*(i+1)%mod;
	
	invv[1]=1;
	for(int i=2;i<=lim;i++) invv[i]=(mod-mod/i)*invv[mod%i]%mod;
	
	S2[0][0]=1;
	for(int i=1;i<=lim;i++){
		for(int j=1;j<=i;j++) gmod(S2[i][j]=S2[i-1][j-1]+S2[i-1][j]*j%mod);
	}
}
int C(int m,int n){
	if(m<0 || n<0 || m<n) return 0;
	return mul[m]*inv[n]%mod*inv[m-n]%mod;
}
int ID(int x){
    return (x & 1)?(mod-1):1;
}
int T,n,m; 
signed main(){
	init(N-5);
	cin>>T;
	while(T--){
		scanf("%lld%lld",&n,&m);
		printf("%lld\n",(m+(ID(m+1)*mul[m+1]%mod*S2[n][m+1]%mod+mod-ID(m+1)*ksm(m+1,n)%mod+mod-ID(m)*ksm(m,n)%mod*(m+1)%mod)%mod*ksm(invv[m],n)%mod*ID(m)%mod)%mod);
	}
}

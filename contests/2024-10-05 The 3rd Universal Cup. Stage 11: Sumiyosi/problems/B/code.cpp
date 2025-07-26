#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=3300,mod=998244353;
int n,m;
int a[N];

void gmod(int &x){
	if(x>=mod) x-=mod;
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

int mul[N],inv[N];
void init(int lim){
	mul[0]=inv[0]=1;
	for(int i=1;i<=lim;i++) mul[i]=mul[i-1]*i%mod;
	inv[lim]=ksm(mul[lim],mod-2);
	for(int i=lim-1;i>=1;i--) inv[i]=inv[i+1]*(i+1)%mod;
	
}
int C(int m,int n){
	if(m<0 || n<0 || m<n) return 0;
	return mul[m]*inv[n]%mod*inv[m-n]%mod;
}

int dp[N][N],g[N],id;
int ans[N];

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	init(N-5);
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i],a[i]=min(a[i],m);
	sort(a+1,a+n+1);
	
	dp[n+1][0]=1;
	for(int t=n;t>=1;t--){
		for(int j=0;j<m;j++){
			gmod(dp[t][j]+=dp[t+1][j]);
			if(j+a[t]<m){
				gmod(dp[t][j+a[t]]+=dp[t+1][j]);
				gmod(g[t]+=dp[t+1][j]);
			}
		}
		int tot=0;
		for(int i=1;i<=n-t+1;i++) gmod(tot+=C(n-t,i-1));
		gmod(tot+=mod-g[t]);
		for(int k=0;k<=t-1;k++){
			gmod(ans[k]+=tot*C(t-1,k)%mod);
		}
	}
	
	for(int i=0;i<=n;i++) cout<<ans[i]<<endl;
}

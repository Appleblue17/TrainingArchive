#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=4e5+5,mod=998244353;

int ksm(int a,int x){
	int tot=1;
	while(x){
		if(x & 1ll) tot=tot*a%mod;
		a=a*a%mod;
		x>>=1ll;
	}
	return tot;
}

int mul[N],inv[N],pw[N];
void init(int lim){
	// mul[0]=inv[0]=1;
	// for(int i=1;i<=lim;i++) mul[i]=mul[i-1]*i%mod;
	// inv[lim]=ksm(mul[lim],mod-2);
	// for(int i=lim-1;i>=1;i--) inv[i]=inv[i+1]*(i+1)%mod;
	
	pw[0]=1;
	for(int i=1;i<=lim;i++) pw[i]=pw[i-1]*2%mod;
}

int C(int m,int n){
	if(m<0 || n<0 || m<n) return 0;
	return mul[m]*inv[n]%mod*inv[m-n]%mod;
}

int n;
int p[N];

int c[N];
int lowbit(int x){
	return x & (-x);
}
void modify(int x,int k){
	while(x<=n) c[x]=max(c[x],k),x+=lowbit(x);
}
int query(int x){
	int tot=0;
	while(x) tot=max(tot,c[x]),x-=lowbit(x);
	return tot;
}


signed main(){
	init(N-5);
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	cin>>n;
	for(int i=1;i<=n;i++) cin>>p[i];
	
	int ans=1;
	modify(n+1-p[1],1);
	for(int i=2;i<=n;i++){
//		int j=i-1;
//		while(j-1>=0 && p[j]<p[i]) j--;
		
		int x=query(n+1-p[i]);
		modify(n+1-p[i],i);
		
//		cout<<i<<" "<<j<<" "<<x<<endl;
		if(!x) ans=ans*pw[i-1]%mod;
		else ans=ans*(pw[i-1]+mod-pw[x-1])%mod;
	}
	cout<<ans;
	
}

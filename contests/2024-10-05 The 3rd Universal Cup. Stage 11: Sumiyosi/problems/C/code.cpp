#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+5,INF=1e18;
int n,ans=INF;
int a[N],b[N],c[N],d[N];

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>b[i];
	for(int i=1;i<=n;i++) cin>>c[i];
	for(int i=1;i<=n;i++) cin>>d[i];
	
	int sum=0;
	for(int i=1;i<=n;i++){
		sum+=a[i];
		b[i]-=a[i];
		c[i]+=c[i-1];
		d[i]+=d[i-1];
	}
	sort(b+1,b+n+1);
	for(int i=1;i<=n;i++) b[i]+=b[i-1];
	
	for(int i=0;i<=n;i++){
		ans=min(ans,sum+b[n-i]+c[i]+d[n-i]);
	}
	cout<<ans;
}

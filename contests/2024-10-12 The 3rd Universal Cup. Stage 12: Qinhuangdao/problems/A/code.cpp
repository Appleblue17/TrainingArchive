#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+5,INF=1e18;
int T,n,m,q;
int s[N],p[N],t[N];
int d[N];

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>T;
	
	while(T--){
		cin>>n>>m>>q;
		for(int i=1;i<=n;i++) cin>>s[i];
		int sum=0;
		for(int i=1;i<=q;i++){
			int a,b; cin>>a>>b;
			p[i]=s[a],t[i]=b;
			d[i]=(p[i]%m+m-t[i]%m)%m;
			sum+=d[i];
		}
		sort(d+1,d+q+1);
		
		int ans=INF;
		for(int i=1;i<=q;i++){
			ans=min(ans,(i-1)*m-q*d[i]);
		}
		cout<<ans+sum<<endl;
	}
	
}

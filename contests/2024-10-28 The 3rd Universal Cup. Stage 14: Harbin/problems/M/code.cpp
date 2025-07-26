#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll t,n,ans;
vector<ll> g;
int main(){
	cin >> t;
	while(t--){
		scanf("%lld",&n);
		g.clear();ans=0;
		for(int i=1;i*i<=n;i++){
			if(n%i==0){
				g.push_back(i);
				g.push_back(n/i);
			}
		}
		sort(g.begin(),g.end());
		for(int i=0;i<g.size()-1;i++){
			ans += (g[i+1]-g[i])*(n/g[i]);
		}
		ans++;
		printf("%lld\n",ans);
	}
}

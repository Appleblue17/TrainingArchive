#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll m,a[1000010],ya[1000010],b[1000010],yb[1000010],ans,sm;
void solve(){
	ans=0;
	sm=0;
	scanf("%lld",&m);
	for(int i=0;i<m;i++){
		scanf("%lld",&a[i]);
		sm -= a[i];
	}
	for(int i=0;i<m;i++){
		scanf("%lld",&b[i]);
		sm += b[i];
	}
	if(sm > 0)a[0] += sm;
	else b[0] -= sm;
	for(int i=0;i<m;i++){
		ya[i]=a[i];yb[i]=b[i];
	}
	for(int i=0;i<m/2;i++){
		swap(b[i],b[m-i-1]);
		swap(yb[i],yb[m-i-1]);
	}
	int j=m-1;
	bool f=0;
	for(int i=m-1;i>=0;i--){
		if(j>i)j=i;
		while(a[i] >= b[j]){
			if(b[j] != 0 && j != i)f=1;
			a[i]-=b[j];
			ans += b[j];
			b[j]=0;
			
			j--;
			if(j<0)break;
		}
		if(j<0)break;
		if(a[i] != 0 && j != i)f=1;
		b[j]-=a[i];
		ans += a[i];
	}
	//printf("f=%d\n",f);
	if(f){
		printf("%lld\n",ans);
		return;
	}
	else{
		bool f=0,f2=0;
		int f3=0,mx=0,mn=m;
		for(int i=0;i<m;i++){
			if(ya[i]>=1)mx = max(mx,i);
			if(yb[i]>=1)mn = min(mn,i);
		}
		if(mx + m-mn-1 < m){
			printf("0\n");
			return;
		}
		for(int i=m-1;i>=0;i--){
			if(ya[i]!=0){
				if(!f){
					f=1;
					continue;
				}
			}
			if(f){
				if(ya[i] < yb[i]){
					f2=1;
				}
			}
		}
		if(f2)printf("%lld\n",ans);
		else printf("%lld\n",ans-1);
	}
}
int main(){
	int t;
	cin >> t;
	while(t--){
		solve();
	}
}

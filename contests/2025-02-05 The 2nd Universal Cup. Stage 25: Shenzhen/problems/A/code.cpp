#include <bits/stdc++.h>
using namespace std;
const int N=1100;
int n,a[N],b[N];

vector <pair<int,int> > ANS;
void ins(int x,int y){
	ANS.push_back(make_pair(x,y));
	if(x==1){
		for(int i=1;i<=n;i++) if(a[i]==y) a[i]++;
	}
	else a[y]++;
}

void solve(int L,int R){
	if(L==R) return ;
	int mid=(L+R)>>1;
	
	for(int i=1;i<=n;i++){
		if(b[i]>mid && b[i]<=R) ins(2,i);
	}
	for(int t=L+1;t<=mid;t++) ins(1,t);
	
	solve(L,mid);
	solve(mid+1,R);
}

int main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>b[i];
	
	// n=1000;
	// for(int i=1;i<=n;i++) b[i]=i;
	solve(0,n);
	
	// for(int i=1;i<=n;i++) cout<<a[i]<<" ";
	// cout<<endl;
	
	cout<<ANS.size()<<endl;
	for(auto x: ANS) printf("%d %d\n",x.first,x.second);
}

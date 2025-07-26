#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=4e5+5,mod=998244353;

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

int n,m,ans;
int f[33][2];


struct mat{
	int a[5][5];
	mat(int x=0){memset(a, 0, sizeof a);
		for(int i=1;i<=4;i++) a[i][i]=x;
	}
}F;
inline mat mul(mat x, mat y){
	mat res;
	for(int i=1; i<=4; ++i){
		for(int k=1; k<=4; ++k) if(x.a[i][k]){
			for(int j=1; j<=4; ++j){
				res.a[i][j]=(res.a[i][j]+ x.a[i][k]*y.a[k][j]%mod)%mod;
			}
		}
	}
	return res;
}
mat ksm(mat a,int x){
	mat tot(1);
	while(x){
		if(x & 1ll) tot=mul(tot,a);
		a=mul(a,a);
		x>>=1ll;
	}
	return tot;
}

signed main(){
	cin>>n>>m;
	
	F.a[2][1]=1;
	F.a[3][1]=1;
	F.a[1][2]=1;
	F.a[2][3]=1;
	
	for(int st=1;st<=3;st++){
		mat P(0);
		P.a[st][1]=1;
		
		mat q=mul(ksm(F,n-2),P);
		
//		cout<<q.a[1][1]<<" "<<q.a[2][1]<<" "<<q.a[3][1]<<"    ";
		if(st==1){
			gmod(ans+=q.a[1][1]%mod);
			gmod(ans+=q.a[3][1]%mod);
		}
		else if(st==2){
			gmod(ans+=q.a[1][1]%mod);
			gmod(ans+=q.a[2][1]%mod);
		}
		else{
			gmod(ans+=q.a[2][1]%mod);
		}
//		cout<<ans<<endl;
	}
	
//	cout<<ans<<endl;
//	return 0;
	
	f[0][0]=1;
	for(int t=0;t<=30;t++){
		int x=(m>>t & 1);
		if(!x){
			gmod(f[t+1][0]+=f[t][0]);
			gmod(f[t+1][1]+=f[t][1]*ans%mod);
			gmod(f[t+1][1]+=f[t][0]);
		}
		else{
			gmod(f[t+1][0]+=f[t][1]);
			gmod(f[t+1][0]+=f[t][0]*ans%mod);
			gmod(f[t+1][1]+=f[t][1]);
		}
		
//		cout<<f[t][0]<<" "<<f[t][1]<<endl;
	}
	
	cout<<f[31][0];
}

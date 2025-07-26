#include<bits/stdc++.h>
using namespace std;
// #define int long long
const int N=2e5+5,INF=1e9;
int T,n;
char S[N];

int dp[N][6][8];

void gmax(int &x,int y){
	x=max(x,y);
}

signed main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		scanf("\n%s",S+1);
		
		for(int i=0;i<=n;i++)
			for(int j=0;j<=5;j++)
				for(int mac=0;mac<(1<<3);mac++) dp[i][j][mac]=-INF;
		
		dp[0][0][7]=0;
		for(int j=0;j<5;j++){
			for(int t=0;t<=1;t++){
				for(int mac=0;mac<(1<<3);mac++)
					gmax(dp[0][j+1][(mac<<1 | t) & 7], dp[0][j][mac] + (mac==1 && t==0)-j);
			}
		}
//		for(int mac=0;mac<(1<<3);mac++){
//			cout<<dp[0][0][mac]<<" ";
//		}
//		cout<<endl;
		for(int i=1;i<=n;i++){
			bool c=(S[i]=='P');
			for(int j=0;j<=5;j++){
				for(int mac=0;mac<(1<<3);mac++)
					gmax(dp[i][j][((mac<<1 | c) & 7)], dp[i-1][j][mac] + (mac==1 && c==0));
			}
			for(int j=0;j<5;j++){
				for(int t=0;t<=1;t++){
					for(int mac=0;mac<(1<<3);mac++)
						gmax(dp[i][j+1][(mac<<1 | t) & 7], dp[i][j][mac] + (mac==1 && t==0)-j);
				}
			}
//			cout<<i<<": "<<endl;
//			for(int j=0;j<=5;j++){
//				for(int mac=0;mac<(1<<3);mac++){
//					cout<<dp[i][j][mac]<<" ";
//				}
//				cout<<endl;
//			}
		}
		int ans=0;
		for(int j=0;j<=5;j++){
			for(int mac=0;mac<(1<<3);mac++)
				gmax(ans, dp[n][j][mac]);
		}
		printf("%d\n",ans);
	}
	
}

#include<bits/stdc++.h>
using namespace std;
// #define int long long
const int N=10;
int T,n;
char S[N];
int a[N];
int mx[3],mn[3];
int f[N][3];

signed main(){
	scanf("%d",&T);
	while(T--){
		scanf("\n%s",S+1);
        for(int i=0;i<3;i++) mx[i]=0,mn[i]=10;
        memset(f,0,sizeof(f));
        
		for(int i=1;i<=9;i++){
                 if(S[i]=='a') a[i]=0,mx[0]=max(mx[0],i),mn[0]=min(mn[0],i);
            else if(S[i]=='g') a[i]=1,mx[1]=max(mx[1],i),mn[1]=min(mn[1],i);
            else if(S[i]=='o') a[i]=2,mx[2]=max(mx[2],i),mn[2]=min(mn[2],i);
            f[i][a[i]]=1;
            for(int t=0;t<3;t++) f[i][t]+=f[i-1][t];
        }
        
        int ans=0;
        for(int mac=1;mac<(1<<3);mac++){
            bool fl=1;
            for(int t=0;t<3;t++){
                if(!(mac>>t & 1)) continue;
                for(int i=0;i<3;i++){
                	if(t==i || !(mac>>i & 1)) continue;
                	int x=f[mx[t]][i]-f[mn[t]][i];
                	if(x==1 || x==2) fl=0;
				}
            }
            if(fl) ans=max(ans,__builtin_popcount(mac));
        }
        cout<<ans<<endl;
		
	}
	
}

#pragma GCC optimize(3)
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int T, n, m;
int p[N];
int mn[N], f[N], g[N];
vector<int> prm;
mt19937 rnd(time(0));
int del[N];
int main(){
	// freopen("D:\\nya\\acm\\A\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\A\\test.out","w",stdout);
    for(int i=1; i<N; ++i) mn[i]=i;
    for(int i=2; i<N; ++i) if(mn[i]==i){
        for(int j=i+i; j<N; j+=i) mn[j]=min(mn[j], i);
    }
    for(int i=2; i<N; ++i) if(mn[i]==i) prm.push_back(i);
    for(int i=1; i<N; ++i) f[i]=1;
    scanf("%d", &T);
    while(T--){
        scanf("%d%d", &n, &m);
        if((n-m)&1) {
            printf("-1\n");
            continue;
        }
        if(n==m){
            for(int i=1; i<=n; ++i) printf("1 ");
            putchar('\n');
            continue;
        }
		for(int i=0; i<(int)prm.size()&&prm[i]<=n; ++i){
			del[i]=0;
			long long bs=prm[i];
			while(bs<=n){
				for(int j=bs; j<=n; j+=bs) if((j/bs)%prm[i]!=0) {
					++del[i];
				}
				bs=bs*prm[i]*prm[i];
			}
		}
        int t=(n-m)/2;
        for(int i=1; i<=n; ++i) f[i]=1;
        int it=0;
        while(it<(int)prm.size()&&del[it]>t){
            ++it;
        }
        int lim=prm[it];
        vector<int> vec;
        for(int i=n; i>lim; --i){
            if(i*2<=n) break;
            if(mn[i]==i) vec.push_back(i);
        }
        int dt=(t-del[it]);
        if(dt<=(int)vec.size()){
            f[lim]=-1;
            for(int i=0; i<dt; ++i) f[vec[i]]=-1;
            for(int i=1; i<=n; ++i) f[i]=f[i/mn[i]]*f[mn[i]];
            int sum2=0;
            for(int i=1; i<=n; ++i) sum2+=f[i];
            for(int i=1; i<=n; ++i) printf("%d ", f[i]);
            for(int i=1; i<=n; ++i) f[i]=1;
            putchar('\n');
        }
        else{
            bool flag=0;
            vector<int> box;
            for(int d=0; d<80; ++d){
                if(it+d>=(int)prm.size()) break;
                if(prm[it+d]>n) break;
                box.push_back(prm[it+d]);
				g[prm[it+d]]=1;
            }
			double temp=1000;
			double stp=0.999;
			double eps=1e-6;
			int ans=dt;
            while(temp>eps){
                int s=0;
				int x=rnd()%(box.size()+1);
				g[prm[it+x]]=-g[prm[it+x]];
				for(auto t:box) f[t]=g[t];
                int cnt=0;
                for(auto t:vec) if(f[t]==1) ++cnt;
                for(int i=1; i<=n; ++i) f[i]=f[i/mn[i]]*f[mn[i]];
                for(int i=1; i<=n; ++i) s+=(f[i]==-1), f[i]=1;
				int now=abs(t-s);
                if(0<=t-s&&t-s<=cnt){
                    for(auto t:box) f[t]=g[t];
                    cnt=t-s;
                    for(auto t:vec) {
                        if(cnt==0) break;
                        if(f[t]==1) f[t]=-1, --cnt;
                    }
                    for(int i=1; i<=n; ++i) f[i]=f[i/mn[i]]*f[mn[i]];
                    int sum2=0;
                    for(int i=1; i<=n; ++i) sum2+=f[i];
                    // printf("ok\n");
                    for(int i=1; i<=n; ++i) printf("%d ", f[i]);
                    for(int i=1; i<=n; ++i) f[i]=1;
                    putchar('\n');
                    flag=1;
                    break;
                }
				else if(now<ans){
					ans=now;
				}
				else if(exp((ans-now)/temp)*INT_MAX<rnd()){
					g[prm[it+x]]=-g[prm[it+x]];
				}
				temp*=stp;
            }
            if(!flag) printf("-1\n");
        }
    }
}

#include <bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,q;

vector <int> D[N],U[N];
int c[N];

double f[N];

signed main(){
    // freopen("out.txt","w",stdout);
    cin>>n>>q;
    
    for(int i=1;i<=n;i++){
        for(int j=i*2;j<=n;j+=i){
            D[j].push_back(i);
            U[i].push_back(j);
        }
    }
    for(int i=1;i<=n;i++) c[i]=D[i].size()+U[i].size()+1;
    // cout<<endl;
    
    for(int i=1;i<=n;i++) f[i]=i;
    
    for(int T=1;T<=300;T++){
        for(int i=1;i<=n;i++){
            double tot=f[i-1];
            for(int x: D[i]) tot+=f[x-1];
            for(int x: U[i]) tot+=f[x-1];
            
            f[i]=min(f[i-1],tot/c[i])+1;
        }
    }
    
    // for(int i=1;i<=n;i++){
    //     printf("%d %.6lf\n",i,f[i]);
    // }
    while(q--){
        int x;
        scanf("%d",&x);
        printf("%.8lf\n",f[x]);
    }
    
}

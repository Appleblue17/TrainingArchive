#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=110;
int n;
ll x[N],y[N];
char c[N];

struct Point{
    ll x,y;
    Point(ll x=0,ll y=0):x(x),y(y){}
} p[N];

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        scanf("%lld%lld",&x[i],&y[i]);
        getchar();
        c[i]=getchar();
    }
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            for(int k=j+1;k<=n;k++){
                ll ux = x[j]-x[i];
                ll uy = y[j]-y[i];
                ll vx = x[k]-x[j];
                ll vy = y[k]-y[j];
                if(ux*vy-uy*vx != 0){
                    if(c[i]==c[j] || c[i]==c[k] || c[j]==c[k]){
                        printf("Infinity\n");
                        return 0;
                    }
                }
            }
        }
    }
    bool f=0,vis[256];
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=n;i++){
        if(!vis[c[i]])vis[c[i]]=1;
        else f=1;
    }
    if(f)printf("2\n");
    else printf("1\n");
}

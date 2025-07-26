#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
#define double ld
int n,m,k,s1,t1,s2,t2;
const int N=5100;
const double SQ2=sqrt(2);
vector<int> g[N];
int dist[N][N];
void bfs(int x){
    queue<int> q;
    q.push(x);
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(int v:g[u]){
            if(dist[x][v]>=10000){
                q.push(v);
                dist[x][v]=dist[x][u]+1;
            }
        }
    }
}
int mton(int m){
    double nd = -0.5+sqrt(8*m*(m+1))/2.0;
    int n = floor(nd);
    return n;
}

double cal0(int n,int x){
    if(!n) return 0;
    int d=x/n,r=x%n;
    return 1.0*(n-r)/(d+1)+1.0*r/(d+2);
}
double cal2(int n,int m,int k){
    if(n>10000 || m>10000) return 1e9;
    if(!n && !m) return 0;
    double x=n*(k+m*(1.0-SQ2))/(SQ2*m+n);
    if(x<0) x=0;
    if(x>k) x=k;
    // cout<<n<<" "<<m<<" "<<k<<": "<<x<<endl;
    
    int t=x;
    double tot=1e18;
    int mn;
    for(int i=-1;i<=2;i++){
        int y=t+i;
        if(y<0 || y>k) continue;
        double val=cal0(n,y)+cal0(m,k-y)*2;
        if(val<tot) tot=val,mn=y;
    }
    // cout<<n<<" "<<m<<" "<<k<<": "<<x<<" "<<mn<<" "<<tot<<endl;
    return tot;
}

double f[N][N];

int main(){
    cin >> n >> m >> k;
    //printf("%.12LF\n",cal(4,1,k));
    for(int i=1;i<=m;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    scanf("%d%d%d%d",&s1,&t1,&s2,&t2);
    memset(dist,24,sizeof(dist));
    for(int i=1;i<=n;i++){
        dist[i][i]=0;
        bfs(i);
    }
    
    double ans=n*4;
    
    for(int i=0;i<=n;i++)
    	for(int j=0;j<=n;j++)
    		f[i][j]=cal2(i,j,k);
    
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            int y = dist[i][j];
            int x = dist[s1][i]+dist[s2][i]+dist[j][t1]+dist[j][t2];
            if(x<=n) ans = min(ans,f[x][y]);
            
            x = dist[s1][i]+dist[s2][j]+dist[j][t1]+dist[i][t2];
            if(x<=n) ans = min(ans,f[x][y]);
            
            x = dist[s1][j]+dist[s2][j]+dist[i][t1]+dist[i][t2];
            if(x<=n) ans = min(ans,f[x][y]);
            
            x = dist[s1][j]+dist[s2][i]+dist[i][t1]+dist[j][t2];
            if(x<=n) ans = min(ans,f[x][y]);
        }
    }
    int x = dist[s1][t1]+dist[s2][t2];
    ans = min(ans,cal2(x,0,k));
    printf("%.12LF",ans);
}

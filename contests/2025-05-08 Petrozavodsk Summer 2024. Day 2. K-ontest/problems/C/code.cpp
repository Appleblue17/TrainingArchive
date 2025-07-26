#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=4e3+10;
ll n,m,k,nxt[N][N][4],fa[N][N][4],vis[N][N];
char dir[N][N];
ll ans;
ll findfa(int i,int j,int d){//find first not visited
    if(d == 1 || d == 3){
        if(fa[i][j][d]==i)return i;
        else return fa[i][j][d] = findfa(fa[i][j][d],j,d);
    }
    else{
        if(fa[i][j][d]==j)return j;
        else return fa[i][j][d] = findfa(i,fa[i][j][d],d);
    }
}
queue<ll> q;
void enq(int i,int j){
    //printf("enqueue %d %d\n",i,j);
    //if(vis[i][j])printf("???ij already visited\n");
    vis[i][j]=1;
    q.push(i*10000+j);
    int x=i,y=j;
    ll fx=0,fy=-114514;
    if(dir[i][j] == 'D'){
        fx = findfa(i,j,1);
        if(nxt[i][j][1] == -1)return;
        fy = findfa(nxt[i][j][1],j,1);
        if(fx != fy){
            fa[fx][j][1] = fy;
        }
    }
    if(dir[i][j] == 'U'){
        fx = findfa(i,j,3);
        if(nxt[i][j][3] == -1)return;
        fy = findfa(nxt[i][j][3],j,3);
        if(fx != fy){
            fa[fx][j][3] = fy;
        }
    }
    if(dir[i][j] == 'R'){
        fx = findfa(i,j,2);
        if(nxt[i][j][2] == -1)return;
        fy = findfa(i,nxt[i][j][2],2);
        if(fx != fy){
            fa[i][fx][2] = fy;
        }
    }
    if(dir[i][j] == 'L'){
        fx = findfa(i,j,0);
        if(nxt[i][j][0]==-1)return;
        fy = findfa(i,nxt[i][j][0],0);
        if(fx != fy){
            fa[i][fx][0] = fy;
        }
    }
    //printf("dir = %c,fx = %lld,fy=%lld\n",dir[i][j],fx,fy);
    return;
}


int main(){
    //freopen("c.in","r",stdin);
    scanf("%lld%lld%lld",&n,&m,&k);
    for(int i=1;i<=n;i++){
        scanf("%s",dir[i]+1);
    }
    memset(nxt,48,sizeof(nxt));
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            nxt[i][j][2] = nxt[i][j-1][2]+1;
            nxt[i][j][1] = nxt[i-1][j][1]+1;
            if(dir[i][j]=='D'){
                
                fa[i][j][1]=i;
            }
            if(dir[i-1][j]=='D'){
                nxt[i][j][1]=1;
            }
            if(dir[i][j]=='R'){
                
                fa[i][j][2]=j;
            }
            if(dir[i][j-1]=='R'){
                nxt[i][j][2]=1;
            }
            //cout << nxt[i][j][1] << ' ';
        }
       // putchar('\n');
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(nxt[i][j][1] <= k){
                nxt[i][j][1]=i-nxt[i][j][1];
            }
            else{
                nxt[i][j][1]=-1;
            }
            if(nxt[i][j][2]<= k){
                nxt[i][j][2] = j-nxt[i][j][2];
            }
            else{
                nxt[i][j][2]=-1;
            }
            //cout << nxt[i][j][1] << ' ';
        }
        //putchar('\n');
    }
    for(int i=n;i>=1;i--){
        for(int j=m;j>=1;j--){
            nxt[i][j][0] = nxt[i][j+1][0]+1;
            nxt[i][j][3] = nxt[i+1][j][3]+1;
            if(dir[i][j]=='U'){
                
                fa[i][j][3]=i;
            }
            if(dir[i+1][j]=='U'){
                nxt[i][j][3]=1;
            }
            if(dir[i][j]=='L'){
                
                fa[i][j][0]=j;
            }
            if(dir[i][j+1]=='L'){
                nxt[i][j][0]=1;
            }
            //cout << nxt[i][j][1] << ' ';
        }
       // putchar('\n');
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(nxt[i][j][3] <= k){
                nxt[i][j][3]=i+nxt[i][j][3];
            }
            else{
                nxt[i][j][3]=-1;
            }
            if(nxt[i][j][0]<= k){
                nxt[i][j][0] = j+nxt[i][j][0];
            }
            else{
                nxt[i][j][0]=-1;
            }
            //cout << nxt[i][j][3] << ' ';
        }
        //putchar('\n');
    }
    
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            int x=i,y=j;
            if(dir[i][j]=='R')y += k;
            if(dir[i][j]=='L')y -= k;
            if(dir[i][j]=='D')x += k;
            if(dir[i][j]=='U')x -= k;
            if(x <= 0 || x > n || y <= 0 || y > m){
                enq(i,j);
            }
        }
    }
    //printf("pre end\n");
    while(!q.empty()){
        int i = q.front()/10000;
        int j = q.front()%10000;
        q.pop();
        for(int d=0;d<=3;d++){
            if(d == 1 || d == 3){
                int x = nxt[i][j][d];
                //printf("(%d,%d),nxt,d=%d,(%d,%d)\n",i,j,d,x,j);
                if(x == -1)continue;
                x= findfa(x,j,d);
                //printf("(%d,%d),findfa,d=%d,(%d,%d)\n",i,j,d,x,j);
                if(!vis[x][j])enq(x,j);
            }
            if(d == 0 || d == 2){
                int y = nxt[i][j][d];
                //printf("(%d,%d),nxt,d=%d,(%d,%d)\n",i,j,d,i,y);
                if(y == -1)continue;
                y = findfa(i,y,d);
                //printf("(%d,%d),findfa,d=%d,(%d,%d)\n",i,j,d,i,y);
                if(!vis[i][y])enq(i,y);
            }
            
        }
    }
    ll ans=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(vis[i][j])ans++;
        }
    }
    printf("%lld\n",ans);
}

#include <bits/stdc++.h>
using namespace std;
const int N=550;
int n,m;
long long ans[N*N];
int a[N][N];

int p[N];
int ls[N],rs[N];
int sta[N],cur;
void ins(int x){
    int sav=cur;
    while(cur && p[sta[cur]]>p[x]) cur--;
    if(cur) rs[sta[cur]]=x;
    if(cur<sav) ls[x]=sta[cur+1];
    sta[++cur]=x;
}

void dfs(int l,int r,int x){
    if(l>r) return ;
    int LS=ls[x],RS=rs[x];
    
    dfs(l,x-1,LS);
    dfs(x+1,r,RS);
    
    ans[p[x]-1]+=1ll*(x-l+1)*(r-x+1);
}

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n*m;i++){
        int x,y; scanf("%d%d",&x,&y);
        a[x][y]=i;
    }
    
    for(int l=1;l<=n;l++){
        for(int i=1;i<=m;i++) p[i]=n*m+1;
        
        for(int r=l;r<=n;r++){
            for(int i=1;i<=m;i++) p[i]=min(p[i],a[r][i]);
            for(int i=1;i<=m;i++) ls[i]=rs[i]=0;
            cur=0;
            for(int i=1;i<=m;i++) ins(i);
            
            // cout<<l<<" "<<r<<": ";
            // for(int i=1;i<=m;i++) cout<<p[i]<<" ";
            // cout<<endl;
            
            dfs(1,m,sta[1]);
        }
    }
    for(int i=n*m;i>=0;i--) ans[i]+=ans[i+1];
    for(int i=1;i<=n*m;i++) printf("%lld\n",ans[i]);
}

#include <bits/stdc++.h>
using namespace std;
const int N=110000;
int T,n,m,k;
vector<int> a[N];
int b[N],id[N];

bool check(int x){
    for(int i=1;i<=n;i++){
        int cnt=0;
        for(int j=0;j<m;j++){
            
            if(a[i][j]>x)cnt++;
        }
        if(cnt <= k)return 1;
    }
    return 0;
}
bool cmp(int x,int y){
    return b[x]<b[y];
}
void solve(){
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n;i++){
        a[i].clear();
    }
    for(int i=1;i<=n*m;i++){
        scanf("%d",&b[i]);
        id[i]=i;
    }
    sort(id+1,id+n*m+1,cmp);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            //rintf("%d ",id[(i-1)*m+j]);
            a[i].push_back(id[(i-1)*m+j]);
        }
        //putchar('\n');
    }
    if(n == 1){
        printf("%d\n",m);
        return;
    }
    int le=m,ri=n*m,mi=(le+ri)/2;
    while(le<ri){
        if(check(mi )){
            ri = mi;
        }
        else le = mi+1;
        mi = (le+ri)/2;
    }
    printf("%d\n",mi);
}

int main(){
    scanf("%d",&T);
    while(T--){
        solve();
    }
    
}

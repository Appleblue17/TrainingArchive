#include <bits/stdc++.h>
using namespace std;
// #define int long long
const int N=1100;
int n,m,p;
int a[N][N],b[N][N],c[N][N];
bitset <N> f[N],g[N];
void ins(bitset <N> x, int id){
    bitset <N> rec;
    rec[id]=1;
    for(int i=1;i<=n;i++){
        if(!x[i]) continue;
        if(!f[i][i]){
            f[i]=x;
            g[i]=rec;
            return ;
        }
        else{
            x^=f[i];
            rec^=g[i];
        }
    }
}

mt19937 rng(time(NULL));
signed main(){
    // freopen("1.txt","w",stdout);
    scanf("%d%d%d",&n,&m,&p);
    
    // for(int i=1;i<=n;i++)
    //     for(int j=1;j<=m;j++)
    //         a[i][j]=rng()%2;
    
    // for(int i=1;i<=m;i++)
    //     for(int j=1;j<=p;j++)
    //         b[i][j]=rng()%2;
    // for(int i=1;i<=n;i++){
    //     for(int j=1;j<=m;j++){
    //         for(int k=1;k<=p;k++){
    //             c[i][k]^=a[i][j]*b[j][k];
    //         }
    //     }
    // }
    // for(int i=1;i<=n;i++){
    //     for(int j=1;j<=p;j++) cout<<c[i][j]<<" ";
    //     cout<<endl;
    // }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            scanf("%d",&a[i][j]);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=p;j++)
            scanf("%d",&c[i][j]);
    
    for(int j=1;j<=m;j++){
        bitset<N> tmp;
        for(int i=1;i<=n;i++) tmp[i]=a[i][j];
        ins(tmp,j);
    }
    for(int j=1;j<=p;j++){
        bitset<N> x,tot;
        for(int i=1;i<=n;i++) x[i]=c[i][j];
        
        for(int t=1;t<=n;t++){
            if(x[t] && f[t][t]){
                x^=f[t];
                tot^=g[t];
            }
        }
        if(x.any()){
            puts("No");
            return 0;
        }
        
        for(int i=1;i<=m;i++) b[i][j]=tot[i];
    }
    puts("Yes");
    for(int i=1;i<=m;i++){
        for(int j=1;j<=p;j++)
            printf("%d ",b[i][j]);
        printf("\n");
    }
    
    // memset(c,0,sizeof(c));
    // cout<<endl;
    // for(int i=1;i<=n;i++){
    //     for(int j=1;j<=m;j++){
    //         for(int k=1;k<=p;k++){
    //             c[i][k]^=a[i][j]*b[j][k];
    //         }
    //     }
    // }
    // for(int i=1;i<=n;i++){
    //     for(int j=1;j<=p;j++) cout<<c[i][j]<<" ";
    //     cout<<endl;
    // }
}

#include <bits/stdc++.h>
using namespace std;
//#define int long long
const int N=3e5+5,INF=1e9,M=50;
int n,a[N][M+5],q,b[N][M+5];
map<int,int> ch[M+5];

void solvebf(){
    for(int i=1;i<=n;i++)b[i][0]=a[i][0];
    for(int o=1;o<=M;o++){
        for(int i=1;i<=n;i++)b[i][o]=0;
        for(int i=1;i<=n;i++){
            b[b[i][o-1]][o]++;
        }
    }
}

signed main(){
    //freopen("N.in","r",stdin);
    cin>>n >> q;
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i][0]);
    }
    for(int o=1;o<=M;o++){
        for(int i=1;i<=n;i++){
            a[a[i][o-1]][o]++;
        }
    }
    
    for(int i=1;i<=q;i++){
        int op,x,y;
        scanf("%d%d%d",&op,&x,&y);
        //printf("i=%d,op=%d, x=%d, y=%d\n",i,op,x,y);
        //fflush(stdout);
        if(op == 1){
            //a[a[x][0]][1]--;a[y][1]++;
            ch[1].clear();
            if(a[x][0]>0)
                ch[1][a[x][0]]--;
            if(y>0)
                ch[1][y]++;
            a[x][0]=y;
            //solvebf();
            //printf("o-1=%d,",0);
            //    for(int j=1;j<=n;j++){
            //        printf("%d ",a[j][0]);
            //    }
            //    putchar('\n');
            for(int o=2;o<=M;o++){
                //map<int,int>::iterator it;
                ch[o].clear();
                if(ch[o-1].empty())break;
                for(auto it:ch[o-1]){
                    
                    int x = it.first;
                    int y = it.second;
                    //printf("consequence change layer %d,add a[%d] by %d\n",o,x,y);
                    //fflush(stdout);
                    if(y==0)continue;
                    if(a[x][o-1]>0)
                        ch[o][a[x][o-1]]--;
                    if(a[x][o-1]+y>0)
                        ch[o][a[x][o-1]+y]++;
                    a[x][o-1]+=y;
                }
                
                //printf("o-1=%d,",o-1);
                //for(int j=1;j<=n;j++){
                    //printf("%d ",a[j][o-1]);
                    //assert(a[j][o-1]==b[j][o-1]);
                //}
                //putchar('\n');
            }
        }
        else{
            if(x >= M){
                x = M-1;
            }
            printf("%d\n",a[y][x]);
        }
    }
}

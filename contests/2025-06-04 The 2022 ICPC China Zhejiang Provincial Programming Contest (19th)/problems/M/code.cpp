#include <bits/stdc++.h>
using namespace std;
// #define int long long
const int N=1100;
int n,m;
char S[N][N];
bool f[N][N];

bool check(int x,int y){
    if(x<1 || x>n || y<1 || y>m) return 0;
    if(S[x][y]=='#') return 0;
    return 1;
}

int s1,s2;

signed main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("\n%s",S[i]+1);
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            bool fl=1;
            for(int x=-3;x<=6;x++){
                for(int y=-4;y<=5;y++){
                    if(x>=0 && x<=3 && y>=0 && y<=1) fl &= check(i+x,y+j);
                    else if(x>=1 && x<=2 && y>=-1 && y<=2) fl &= check(i+x,y+j);
                    else fl &= check(i+x,y+j)^1;
                }
            }
            f[i][j]=fl;
            s2+=fl;
        }
    }
    // for(int i=1;i<=n;i++){
    //     for(int j=1;j<=m;j++){
    //         cout<<f[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
    
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(f[i][j]){
                if(i>7 && f[i-7][j]){
                    s1++,s2-=2;
                    f[i][j]=f[i-7][j]=0;
                }
                else if(j>7 && f[i][j-7]){
                    s1++,s2-=2;
                    f[i][j]=f[i][j-7]=0;
                }
            }
        }
    }
    cout<<s1<<" "<<s2;
}

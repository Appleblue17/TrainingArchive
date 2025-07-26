#include <bits/stdc++.h>
using namespace std;
const int N=110;

int T,n,ans;
bool f[N][N];

void fillHor(int l,int L){
    f[l][L]=1;
    f[l][L+1]=1;
    ans++;
}
void fillVer(int l,int L){
    f[l][L]=1;
    f[l+1][L]=1;
    ans++;
}
void fill(int l,int L){
    fillHor(l,L);
    fillHor(l,L+3);
    fillHor(l+2,L);
    fillHor(l+2,L+3);
    fillHor(l+4,L);
    fillHor(l+4,L+3);
}

void solve(int l,int L,int n){
    if(n<=0) return ;
    if(n%6==0 || n%6==2 || n%6==3 || n%6==4){
        assert(l==0 && L==0);
        int i=0,j=0;
        for(i=0;i+6<=n;i+=6){
            for(j=0;j+6<=n;j+=6){
                fill(i,j);
            }
        }
        if(n%6==2){
            for(j=0;j+3<=n;j+=3) fillHor(i,j);
            for(i=0;i+3<=n;i+=3) fillVer(i,j);
        }
        else if(n%6==3){
            int sj=j;
            for(j=0;j+2<=n;j+=2) fillVer(i,j);
            for(i=0;i+4<=n;i+=2) fillHor(i,sj);
        }
        else if(n%6==4){
            int sj=j;
            for(j=0;j+3<=n;j+=3){
                fillHor(i,j);
                fillHor(i+2,j);
            }
            for(i=0;i+6<=n;i+=3){
                fillVer(i,sj);
                fillVer(i,sj+2);
            }
        }
        return ;
    }
    
    if(n%6==5){
        for(int i=0;i+3<=n;i+=3) fillVer(l+i,L),fillVer(l+n-i-3,L+n-2);
        for(int j=2;j+3<=n;j+=3) fillHor(l,L+j),fillHor(l+n-2,L+n-j-3);
        solve(l+2,L+2,n-4);
    }
    else if(n%6==1){
        for(int j=0;j+4<=n;j+=2) fillVer(l,L+j),fillVer(l+n-3,L+n-j-2);
        for(int i=3;i+2<=n;i+=2) fillHor(l+i,L),fillHor(l+n-i-2,L+n-3);
        solve(l+3,L+3,n-6);
    }
}


int main(){
    cin>>T;
    while(T--){
        scanf("%d",&n);
        n++;
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                f[i][j]=0;
        ans=0;
        solve(0,0,n);
        for(int i=0;i<n-1;i++){
            for(int j=0;j<n-1;j++){
                if(f[i][j]) putchar('#');
                else putchar('.');
            }
            putchar('\n');
        }
        // cout<<ans<<" "<<n*n-ans*6<<endl;
    }
    
}

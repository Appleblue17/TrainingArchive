#include <bits/stdc++.h>
using namespace std;
const int N=3e5+5,INF=1e9;
int q, m;
int lp[N], rp[N];
int st1[20][N], st2[20][N], lg[N*2];
int fl[20][N], fr[20][N];
inline int get1(int l, int r){
    l=max(0, l); r=min(N-1, r);
    int t=lg[r-l+1];
    return min(st1[t][l], st1[t][r-(1<<t)+1]);
}
inline int get2(int l, int r){
    l=max(0, l); r=min(N-1, r);
    int t=lg[r-l+1];
    return max(st2[t][l], st2[t][r-(1<<t)+1]);
}
signed main(){
    scanf("%d%d", &q, &m);
    lp[0]=0; rp[0]=(m-1)/2;
    for(int i=1; i<N; ++i){
        int mx=1;
        for(int j=1; j*j<=i&&j<=m; ++j) {
            if(i%j==0) {
                mx=max(mx, j);
                if(i/j<=m) mx=max(mx, i/j);
            }
        }
        lp[i]=max(0, i-mx/2); rp[i]=min(N-1, i+(mx-1)/2);
    }
    for(int i=2; i<=N; ++i) lg[i]=lg[i>>1]+1;
    for(int i=0; i<N; ++i) st1[0][i]=lp[i], st2[0][i]=rp[i];
    for(int i=1; i<=lg[N]; ++i){
        for(int j=0; j+(1<<i)-1<N; ++j){
            st1[i][j]=min(st1[i-1][j], st1[i-1][j+(1<<(i-1))]);
            st2[i][j]=max(st2[i-1][j], st2[i-1][j+(1<<(i-1))]);
        }
    }
    for(int i=0; i<N; ++i) fl[0][i]=get1(i, N-1), fr[0][i]=get2(0, i); 
    for(int t=1; t<20; ++t) for(int i=0; i<N; ++i) fl[t][i]=fl[t-1][fl[t-1][i]], fr[t][i]=fr[t-1][fr[t-1][i]];
    while(q--){
        int x, y; scanf("%d%d", &x, &y);
        int lstl=y, lstr=y, cl=y, cr=y, ans=0;
        while(cr-cl+1<=m){
            // cout<<cl<<' '<<cr<<endl;
            if(cl<=x&&x<=cr){
                break;
            }
            ++ans;
            cl=get1(lstl, lstr); cr=get2(lstl, lstr);
            if(cl==lstl&&cr==lstr){
                ans=-1;
                break;
            }
            lstl=cl; lstr=cr;
        }
        if(cl<=x&&x<=cr||ans==-1){
            printf("%d\n", ans);
            continue;
        }
        for(int i=19; i>=0; --i){
            if(fl[i][cl]<=x&&x<=fr[i][cr]){
                continue;
            }
            ans+=(1<<i);
            cl=fl[i][cl]; cr=fr[i][cr];
        }
        ++ans;
        cl=fl[0][cl]; cr=fr[0][cr];
        if(cl<=x&&x<=cr){
            printf("%d\n", ans);
        }
        else{
            printf("-1\n");
        }
    }
}

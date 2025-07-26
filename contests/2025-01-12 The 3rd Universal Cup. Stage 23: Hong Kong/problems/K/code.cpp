#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1000010;
char s[N],a[N];
ll nxt[N][2],lst[2];//0: next L. 1: next R.
ll q,n,l;
void solve(){
    scanf("%s",s+1);
    n = strlen(s+1);
    scanf("%lld",&q);
    lst[0]=lst[1]=0;
    //bool all[2];
    //all[0]=all[1]=1;
    for(int i=n;i>=1;i--){
        nxt[i][0]=lst[0];
        nxt[i][1]=lst[1];
        //printf("nxt[%d] = %d,%d\n",i,nxt[i][0],nxt[i][1]);
        if(s[i]=='L'){
            lst[0]=i;
            //all[1]=0;
        }
        else{
            lst[1]=i;
            //all[0]=0;
        }
        
    }
    nxt[0][0]=lst[0];
    nxt[0][1]=lst[1];
    while(q--){
        scanf("%s",a+1);
        l = strlen(a+1);
        ll u=0;
        if(s[1] == 'L' && a[1] != 'L'){
            printf("NO\n");
            continue;
        }
        if(s[n] == 'R' && a[l] != 'R'){
            printf("NO\n");
            continue;
        }
        bool f=0;
        for(int i=1;i<=l;i++){
            if(a[i] == 'L'){
                u = nxt[u][0];
            }
            else{
                u = nxt[u][1];
            }
            //printf("u=%lld\n",u);
            if(u == 0){
                printf("NO\n");
                f=1;
                break;
            }
        }
        if(!f){
            printf("YES\n");
        }
    }
}
int main(){
    int T;
    cin >> T;
    while(T--){
        solve();
    }
}

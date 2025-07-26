#include <bits/stdc++.h>
using namespace std;
const int N=1e6+5,INF=1e9;
int T,n;
char S[N];

signed main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        scanf("\n%s",S+1);
        if(S[1]!=S[n]) puts("empty");
        else{
            bool fl=0;
            int mn=INF;
            for(int l=1,r;l<=n;l=r+1){
                r=l;
                while(r+1<=n && S[r+1]==S[l]) r++;
                if(S[l]==S[1]){
                    mn=min(mn,r-l+1);
                }
                else{
                    if(r-l+1>=2) fl=1;
                }
            }
            if(fl) puts("empty");
            else{
                for(int i=1;i<=mn;i++) putchar(S[1]);
                putchar('\n');
            }
        }
    }
    
}

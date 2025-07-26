#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int T;
char s[N];
int lp[N], rp[N];
int main(){
    scanf("%d", &T);
    while(T--){
        scanf("%s", s+1);
        int n=strlen(s+1);
        for(int i=1; i<=n; ++i){
            if(s[i]=='p') lp[i]=0;
            else lp[i]=lp[i-1]+1;
        }
        rp[n+1]=0;
        for(int i=n; i>=1; --i){
            if(s[i]=='p') rp[i]=0;
            else rp[i]=rp[i+1]+1;
        }
        long long ans=0;
        for(int i=2; i<n; ++i) if(s[i]!='c'){
            ans+=min(lp[i-1]/2, rp[i+1]);
        }
        cout<<ans<<endl;
    }
}

#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int T,n;
char S[N];
int f[N];
int lowbit(int x){
    return x & (-x);
}

int main(){
    cin>>T;
    while(T--){
        scanf("%d",&n);
        scanf("\n%s",S+1);
        
        for(int i=1;i<=n;i++) f[i]=0;
        int ans=0;
        for(int i=1;i<=n;i++){
            int fa=i+lowbit(i);
            if(fa>n) continue;
            f[fa]+=S[i]-'0';
        }
        for(int i=1;i<=n;i++){
            if(S[i]=='1' && !f[i]) ans++;
            if(S[i]=='0' && f[i]==1) ans++;
        }
        printf("%d\n",ans);
    }
    
}

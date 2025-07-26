#pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;
#define uint64 unsigned int
#define int64 long long
const int N=1e5+5,M=2e7+5,INF=1e9;

mt19937 rng(114514);

int T,n;
int a[N];

uint64 X[9][3];

int pw3[11];
int buc[9];
uint64 hasL[N];

int pos[9][N],num[9];
int mp[M];
// unordered_map <uint64, int> mp;
int64 solve(){
    for(int t=1;t<=8;t++){
        num[t]=0;
        pos[t][1]=INF;
    }
    mp[0]=1;
    
    int64 tot=0;
    uint64 hasR=0;
    
    // for(int t=1;t<=8;t++) cout<<buc[t]<<" ";
    // cout<<endl;
    
    int cur=0,cnt=0;
    for(int t=1;t<=8;t++) cnt+=(num[t]>=buc[t]);
    for(int i=1;i<=n;i++){
        // cout<<i<<": "<<endl;
        int c=a[i];
        if(num[c]>=buc[c]){
            hasR^=X[c][(num[c]-buc[c])%3];
        }
        
        bool fl=(cur==pos[c][num[c]-buc[c]+1] || cur==i-2);
        
        pos[c][++num[c]]=i;
        if(num[c]==buc[c]) cnt++;
        
        if(cnt==8 && fl){
            // cout<<"OK "<<i<<endl;
            int mn=i-1;
            for(int t=1;t<=8;t++) if(buc[t]) mn=min(mn,pos[t][num[t]-buc[t]+1]);
            while(cur+1<=mn){
                cur++;
                // cout<<" move "<<cur<<endl;
                mp[hasL[cur]]++;
            }
            // cout<<" hasR: "<<hasR<<" "<<mp[hasR]<<endl;
        }
        if(cnt==8) tot+=mp[hasR];
    }
    for(int i=1;i<=cur;i++) mp[hasL[i]]=0;
    return tot;
}

int rd(){
    char c=getchar();
    int tot=0;
    while(!isdigit(c)) c=getchar();
    while(isdigit(c)) tot=(tot<<1)+(tot<<3)+(c^'0'),c=getchar();
    return tot;
}

int main(){
    // freopen("1.txt","r",stdin);
    pw3[0]=1;
    for(int i=1;i<=8;i++) pw3[i]=pw3[i-1]*3;
    
    for(int i=1;i<=8;i++){
        X[i][0]=rng() & ((1<<24)-1);
        X[i][1]=rng() & ((1<<24)-1);
        X[i][2]=X[i][0]^X[i][1];
        // cout<<X[i][0]<<" "<<X[i][1]<<" "<<X[i][2]<<endl;
    }
    
    T=rd();
    while(T--){
        n=rd();
        for(int i=1;i<=n;i++) a[i]=rd();
        
        memset(num,0,sizeof(num));
        for(int i=1;i<=n;i++){
            int c=a[i];
            hasL[i]=hasL[i-1]^X[c][num[c]%3];
            num[c]++;
        }
        // for(int i=1;i<=n;i++) cout<<i<<" "<<hasL[i]<<endl;
        
        int64 ans=0;
        for(int mac=0;mac<pw3[6];mac++){
            memset(buc,0,sizeof(buc));
            for(int i=0;i<6;i++){
                int x=mac/pw3[i]%3;
                buc[i+1]+=x;
                buc[i+2]+=x;
                buc[i+3]+=x;
            }
            ans+=solve();
        }
        printf("%lld\n",ans);
    }
    
}

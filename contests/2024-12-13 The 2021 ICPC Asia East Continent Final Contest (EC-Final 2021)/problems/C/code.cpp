#include <bits/stdc++.h>
using namespace std;
const int N=22,M=4e5+5,mod=1e9+7;
int m,n;
char S[N],T[N];

int alc;
char fix[N];
int must_be[26],not_be[26];
int L[26],R[26];

int buc[26],full[26];

int tmp[N];
int f[N][M],g[N][M];

void gmod(int &x){
    if(x>=mod) x-=mod;
}
void FWTor(int *f,int n,int opt){
    for(int k=1;k<n;k<<=1){
        for(int i=0;i<n;i+=k<<1){
            for(int j=0;j<k;j++){
                int x=i+j,y=i+j+k;
                if(opt==1) gmod(f[y]+=f[x]);
                else gmod(f[y]+=mod-f[x]);
            }
        }
    }
}


signed main(){
    scanf("%d%d",&n,&m);
    
    alc=(1<<m)-1;
    for(int c=0;c<26;c++) L[c]=0,R[c]=m;
    for(int i=1;i<=n;i++){
        scanf("\n%s",S);
        scanf("\n%s",T);
        
        memset(buc,0,sizeof(buc));
        memset(full,0,sizeof(full));
        for(int j=0;j<m;j++){
            char s=S[j],t=T[j];
            int c=s-'A';
            
            if(t=='O'){
                if(fix[j] && fix[j]!=s) return puts("0"),0;
                fix[j]=s;
                
                buc[c]++;
                must_be[c] |= 1<<j;
                alc ^= 1<<j;
            }
            else if(t=='-'){
                if(full[c]) return puts("0"),0;
                buc[c]++;
                not_be[c] |= 1<<j;
            }
            else if(t=='x'){
                full[c]=1;
                not_be[c] |= 1<<j;
            }
        }
        for(int c=0;c<26;c++){
            L[c]=max(L[c],buc[c]);
            if(full[c]) R[c]=min(R[c],buc[c]);
        }
    }
    for(int c=0;c<26;c++){
        if(L[c]>R[c]){
            // cout<<c<<" : "<<L[c]<<" "<<R[c]<<endl;
            return puts("0"),0;
        }
        if(must_be[c] & not_be[c]){
            // cout<<c<<" - "<<must_be[c]<<" "<<not_be[c]<<endl;
            return puts("0"),0;
        }
    }
    
    // cout<<"alc "<<alc<<endl;
    for(int mac=0;mac<(1<<m);mac++) g[0][mac]=1;
    for(int c=0;c<26;c++){
        // cout<<c<<": "<<L[c]<<" "<<R[c]<<endl;
        for(int t=0;t<=m;t++)
            for(int mac=0;mac<(1<<m);mac++)
                f[t][mac]=0;
         
        // cout<<c<<": ";
        for(int mac=0;mac<(1<<m);mac++){
            if((mac | alc)!=alc) continue;
            if(mac & not_be[c]) continue;
            int nmac = mac | must_be[c];
            int cnt=__builtin_popcount(nmac);
            if(cnt>=L[c] && cnt<=R[c]) f[cnt][nmac]=1;
            // ,cout<<nmac<<" ";
        }
        // cout<<endl;
        for(int t=0;t<=m;t++) FWTor(f[t],1<<m,1);
        for(int mac=0;mac<(1<<m);mac++){
            for(int i=0;i<=m;i++) tmp[i]=0;
            for(int i=0;i<=m;i++){
                for(int j=0;i+j<=m;j++){
                    gmod(tmp[i+j]+=1ll*g[i][mac]*f[j][mac]%mod);
                }
            }
            for(int i=0;i<=m;i++) g[i][mac]=tmp[i];
        }
    }
    
    for(int t=0;t<=m;t++) FWTor(g[t],1<<m,-1);
    cout<<g[m][(1<<m)-1];
    
}

#pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;
const int N=6e5+5,mod=998244353;

int ksm(int a,int x){
    int tot=1;
    while(x){
        if(x & 1ll) tot=1ll*tot*a%mod;
        a=1ll*a*a%mod;
        x>>=1ll;
    }
    return tot;
}

void gmod(int &x){
    x+=x>>31 & mod;
}
namespace NTT{
    int A[N],B[N],C[N];
    int rev[N],pre[N];
    int init(int n){
        int lim=0;
        while((1<<lim)<=n) lim++;
        for(int i=0;i<(1<<lim);i++)
            rev[i]=(rev[i>>1]>>1) | ((i & 1)<<(lim-1));
        
        int omega=ksm(3,(mod-1)/(1<<lim));
        pre[0]=1;
        for(int i=1;i<=(1<<lim);i++)
            pre[i]=1ll*pre[i-1]*omega%mod;
        return lim;
    }
    void ntt(int *f,int n,int opt){
        for(int i=0;i<n;i++)
            if(i<rev[i]) swap(f[i],f[rev[i]]);
        for(int l=1;l<n;l*=2){
            for(int i=0;i<n;i+=l*2){
                int u=n/l/2,nw=(opt==1)?0:n;
                for(int j=0;j<l;j++){
                    int x=f[i+j],y=1ll*pre[nw]*f[i+j+l]%mod;
                    gmod(f[i+j]=x+y-mod),gmod(f[i+j+l]=x-y);
                    nw+=opt*u;
                }
            }
        }
        if(opt==-1){
            int t=ksm(n,mod-2);
            for(int i=0;i<=n-1;i++)
                f[i]=1ll*f[i]*t%mod;
        }
    }
    void solve(int *s,int *f,int *g,int n,int m){
        if(n+m<=150){
            for(int i=0;i<=n+m;i++) s[i]=0;
            for(int i=0;i<=n;i++){
                for(int j=0;j<=m;j++){
                    gmod(s[i+j]+=1ll*f[i]*g[j]%mod-mod);
                }
            }
            return ;
        }
        
        int lim=init(n+m);
        for(int i=0;i<(1<<lim);i++) A[i]=B[i]=0;
        for(int i=0;i<=n;i++) A[i]=f[i];
        for(int i=0;i<=m;i++) B[i]=g[i];
        ntt(A,1<<lim,1);
        ntt(B,1<<lim,1);
        for(int i=0;i<(1<<lim);i++) C[i]=1ll*A[i]*B[i]%mod;
        ntt(C,1<<lim,-1);
        for(int i=0;i<=n+m;i++) s[i]=C[i];
    }
}

const int st=6561,B=10000;
int n,q,m,pw3[N],mp[N];
int X[N],C[N],a[N];
vector <int> V[N];

int ans[22][N];// 0 => 2^9(512)
int f[22][N],g[22][N];
int F[N],G[N],H[N];

inline int rd(){
    char c=getchar();
    int tot=0;
    while(!isdigit(c)) c=getchar();
    while(isdigit(c)) tot=(tot<<1)+(tot<<3)+(c^'0'),c=getchar();
    return tot;
}

int main(){
    pw3[0]=st;
    for(int i=1;i<=20;i++) pw3[i]=pw3[i-1]*3;
    
    n=rd(),q=rd();
    for(int i=1;i<=n;i++){
        X[i]=rd(),C[i]=rd();
        a[X[i]]=C[i];
        V[C[i]].push_back(i);
        m=max(m,X[i]);
    }
    
    int lim=min(n,st);
    int r=0;
    while(pw3[r]<=n) r++;
    for(int t=1;t<=r;t++){
        for(int i=pw3[t-1]+1;i<=min(pw3[t],n);i++) mp[i]=t;
    }
    
    for(int i=lim;i>=1;i--){
        int x=X[i],c=C[i];
        for(int j=x+1;j<=m;j++){
            if(a[j] && a[j]!=c) ans[0][j-x]=i;
        }
    }
    for(int i=0;i<=m;i++) F[i]=0;
    for(int i=1;i<=n;i++) F[X[i]]=1;
    
    int num=0;
    for(int t=1;t<=r;t++){
        num++;
        for(int i=0;i<=m;i++) G[i]=0;
        for(int i=pw3[t-1]+1;i<=min(n,pw3[t]);i++) G[m-X[i]]=1;
        NTT::solve(H,F,G,m,m);
        for(int i=1;i<=m;i++) f[t][i]=H[m+i];
    }
    for(int c=1;c<=n;c++){
        int siz=V[c].size();
        if(!siz) continue;
        
        if(siz<=B){
            // bruteforce
            for(int i=0;i<siz;i++){
                for(int j=i+1;j<siz;j++){
                    int p=V[c][i],q=V[c][j];
                    int x=X[p],y=X[q];
                    if(x<y) g[mp[p]][y-x]++;
                    else g[mp[q]][x-y]++;
                }
            }
        }
        else{
            //NTT
            for(int i=0;i<=m;i++) F[i]=0;
            for(int i=1;i<=n;i++){
                if(C[i]==c) F[X[i]]=1;
            }
            
            for(int t=1;t<=r;t++){
                num++;
                for(int i=0;i<=m;i++) G[i]=0;
                for(int i=pw3[t-1]+1;i<=min(n,pw3[t]);i++){
                    if(C[i]==c) G[m-X[i]]=1;
                }
                NTT::solve(H,F,G,m,m);
                for(int i=1;i<=m;i++) g[t][i]+=H[m+i];
            }
        }
    }
    
    for(int t=1;t<=r;t++){
        for(int i=1;i<=m;i++){
            ans[t][i]=(f[t][i]>g[t][i]);
        }
    }
    
    while(q--){
        int d=rd();
        if(ans[0][d]) printf("%d\n",ans[0][d]);
        else{
            int x=0; // > 2^x
            while(x<=r && !ans[x+1][d]) x++;
            if(x>r) printf("0\n");
            else{
                int l=pw3[x],r=pw3[x+1];
                // printf("(%d, %d]\n",l,r);
                printf("%d\n",(r+1)/2);
            }
            
        }
    }
}

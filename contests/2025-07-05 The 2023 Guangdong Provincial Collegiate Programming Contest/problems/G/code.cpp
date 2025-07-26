#include <bits/stdc++.h>
using namespace std;
const int N=1e5+5,MX=(1<<30)-1;
int T,n,alc,ext;
int a[33][N];
int b[2][N];
int pre[2][N],suf[2][N];
int pre2[2][N],suf2[2][N];

int PRE[N],SUF[N];
int p[N],pid,c[N];
int cal(int f,int x,int y){
    int *prex = pre[f], *sufx = suf[f];
    int *prex2 = pre2[f], *sufx2 = suf2[f];
    if(x>y) swap(x,y);
    
    for(int t=0;t<=29;t++){
        if(x>prex[t]) PRE[t]=prex[t];
        else if(x<prex[t]){
            if(!(b[f][y]>>t & 1)) PRE[t]=x;
            else PRE[t]=prex[t];
        }
        else if(x==prex[t]){
            if(!(b[f][y]>>t & 1)) PRE[t]=prex[t];
            else{
                if(y<prex2[t]) PRE[t]=y;
                else PRE[t]=prex2[t];
            }
        }
    }
    for(int t=0;t<=29;t++){
        if(y<sufx[t]) SUF[t]=sufx[t];
        else if(y>sufx[t]){
            if(!(b[f][x]>>t & 1)) SUF[t]=y;
            else SUF[t]=sufx[t];
        }
        else if(y==sufx[t]){
            if(!(b[f][x]>>t & 1)) SUF[t]=sufx[t];
            else{
                if(x>sufx2[t]) SUF[t]=x;
                else SUF[t]=sufx2[t];
            }
        }
    }
    
    pid=0;
    for(int t=0;t<=29;t++){
        if(ext>>t & 1) continue;
        p[++pid]=PRE[t]-1;
        p[++pid]=SUF[t];
    }
    sort(p+1,p+pid+1);
    pid=unique(p+1,p+pid+1)-p-1;
    
    for(int i=1;i<=pid;i++) c[i]=0;
    for(int t=0;t<=29;t++){
        if(ext>>t & 1) continue;
        int L=lower_bound(p+1,p+pid+1,PRE[t]-1)-p;
        int R=lower_bound(p+1,p+pid+1,SUF[t])-p;
        c[1]+=(1<<t),c[L+1]-=(1<<t); c[R]+=(1<<t);
    }
    int tot=0;
    for(int i=1;i<=pid;i++){
        c[i]+=c[i-1];
        if(p[i]>=1 && p[i]<n) tot=max(tot,c[i]);
    }
    return tot+ext;
}

int q[N],qid;
bool check(int cur,int t){
    cur |= (1<<t);
    if((alc & cur) == cur) return 1;
    
    for(int f=0;f<=1;f++){
        int *prex = pre[f], *sufx = suf[f];
        int *prex2 = pre2[f], *sufx2 = suf2[f];
        
        qid=0;
        for(int i=t;i<=29;i++){
            if(!(cur>>i & 1)) continue;
            q[++qid]=i;
        }
        sort(q+1,q+qid+1,[&](int x,int y){
            return prex[x]<prex[y];
        });
        
        for(int i=1;i<=qid;i++){
            int u=q[i],nw=1,lim=prex[u];
            if(lim==1) continue;
            
            int sp=-1;
            while(nw<=qid && prex[q[nw]]<lim){
                int v=q[nw],pos=sufx[v];
                if(prex[v]==prex[u]){
                    nw++;
                    continue;
                }
                if(pos>=prex2[u]){
                    sp=pos;
                    break;
                }
                lim=max(lim,pos);
                nw++;
            }
            
            if(sp==-1) sp=lim;
            int ret=cal(f,prex[u],sp);
            if((ret & cur)==cur) return 1;
        }
        
    }
    return 0;
}

signed main(){
    cin>>T;
    while(T--){
        alc=ext=0;
        scanf("%d",&n);
        
        for(int i=1;i<=n;i++){
            int x; scanf("%d",&x);
            b[0][i]=b[1][n+1-i]=x;
            for(int t=0;t<=29;t++) a[t][i]=(x>>t & 1);
        }
        
        int *prex = pre[0], *sufx = suf[0];
        int *prex2 = pre2[0], *sufx2 = suf2[0];
        for(int t=0;t<=29;t++){
            prex[t]=1;
            while(prex[t]<=n && a[t][prex[t]]) prex[t]++;
            prex2[t]=prex[t]+1;
            while(prex2[t]<=n && a[t][prex2[t]]) prex2[t]++;
            
            sufx[t]=n;
            while(sufx[t]>=1 && a[t][sufx[t]]) sufx[t]--;
            sufx2[t]=sufx[t]-1;
            while(sufx2[t]>=1 && a[t][sufx2[t]]) sufx2[t]--;
        }
        
        for(int t=0;t<=29;t++){
            pre[1][t]=n+1-sufx[t];
            pre2[1][t]=n+1-sufx2[t];
            suf[1][t]=n+1-prex[t];
            suf2[1][t]=n+1-prex2[t];
        }
        
        
        PRE[0]=SUF[n+1]=MX;
        for(int i=1;i<=n;i++) PRE[i]=PRE[i-1] & b[0][i];
        for(int i=n;i>=1;i--) SUF[i]=SUF[i+1] & b[0][i];
        ext=PRE[n];
        
        for(int i=1;i<n;i++) alc=max(alc,PRE[i] | SUF[i+1]);
        
        // for(int i=2,x=b[0][2]; i<n; i++,x &= b[0][i]){
        //     alc=max(alc,(x & b[0][1]) | SUF[i+1]);
        //     alc=max(alc,x | (SUF[i+1] & b[0][1]));
        // }
        for(int i=n-1,x=b[0][n-1]; i>1; i--,x &= b[0][i]){
            alc=max(alc,(x & b[0][n]) | PRE[i-1]);
            alc=max(alc,x | (PRE[i-1] & b[0][n]));
        }
        
        for(int i=1;i<=n;i++){
            alc=max(alc,cal(0,1,i));
            // alc=max(alc,cal(0,i,n));
        }
        
        
        int cur=0,ans=0;
        for(int t=29;t>=0;t--){
            if(ext>>t & 1) ans |= (1<<t);
            else if(check(cur,t)) cur |= (1<<t),ans |= (1<<t);
        }
        
        printf("%d\n",ans+ext);
    }
}

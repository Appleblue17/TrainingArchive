#include <bits/stdc++.h>
using namespace std;
const int N=2200,M=11,mod=998244353;

int n,m,k,L,d;
int seq[M];
int exgcd(int a,int b,int& x,int& y){
	if(!b){
		x=1,y=0;
		return a;
	}
	int tmp=exgcd(b,a%b,y,x);
	y-=a/b*x;
	return tmp;
}

void gmod(int &x){
    x+=(x>>31) & mod;
}

struct mat{
    int P[M][M];
    
    mat(int x=0){
        memset(P,0,sizeof(P));
        for(int i=0;i<=m;i++) P[i][i]=x;
    }  
};
mat operator +(mat A,mat B){
    mat S;
    for(int i=0;i<=m;i++)
        for(int j=i;j<=m;j++)
            gmod(S.P[i][j]=A.P[i][j]+B.P[i][j]-mod);
    return S;
}
mat operator *(mat A,mat B){
    mat S;
    for(int i=0;i<=m;i++)
        for(int k=0;k<=m;k++)
            for(int j=i;j<=k;j++)
                gmod(S.P[i][k]+=1ll*A.P[i][j]*B.P[j][k]%mod-mod);
    return S;
}
mat ksm(mat A,int x){
    mat T(1);
    while(x){
        if(x & 1ll) T=T*A;
        A=A*A;
        x>>=1ll;
    }
    return T;
}

mat A[N];
int len[N],id;

mat F[N*4],tag[N*4];
int nlen[N],nid;

void build(int l,int r,int o){
    F[o]=mat(1); tag[o]=mat(1);
    if(l==r) return ;
    int mid=(l+r)>>1;
    build(l,mid,o<<1);
    build(mid+1,r,o<<1|1);
}
inline void pushdown(int o){
    tag[o<<1]=tag[o<<1]*tag[o];
    F[o<<1]=F[o<<1]*tag[o];
    tag[o<<1|1]=tag[o<<1|1]*tag[o];
    F[o<<1|1]=F[o<<1|1]*tag[o];
    tag[o]=mat(1);
}
void modify(int l,int r,int o,int L,int R,mat &X){
    if(L>R) return ;
    if(L<=l && r<=R){
        F[o]=F[o]*X;
        tag[o]=tag[o]*X;
        return ;
    }
    int mid=(l+r)>>1;
    pushdown(o);
    if(L<=mid) modify(l,mid,o<<1,L,R,X);
    if(R>mid) modify(mid+1,r,o<<1|1,L,R,X);
    F[o]=F[o<<1]*F[o<<1|1];
}
void search(int l,int r,int o){
    if(l==r){
        A[l]=F[o];
        return ;
    }
    pushdown(o);
    int mid=(l+r)>>1;
    search(l,mid,o<<1);
    search(mid+1,r,o<<1|1);
}

int v[N],vid;
void solve(int L,int d){
    if(L==1) return ;
    
    if(d*2>L){
        if(len[1]>1){
            for(int i=id;i>=1;i--){
                A[i+1]=A[i];
                len[i+1]=len[i];
            }
            len[1]=1; len[2]--;
            id++;
        }
        for(int i=2;i<=id+2-i;i++){
            swap(A[i],A[id+2-i]);
            swap(len[i],len[id+2-i]);
        }
        solve(L,L-d);
        return ;
    }
    
    vid=0;
    int sum=0;
    for(int i=1;i<=id;i++){
        v[++vid]=sum;
        sum=(sum+len[i])%d;
    }
    v[++vid]=sum;
    v[++vid]=d;
    sort(v+1,v+vid+1);
    vid=unique(v+1,v+vid+1)-v-1;
    
    nid=vid-1;
    for(int i=1;i<=nid;i++){
        nlen[i]=v[i+1]-v[i];
    }
    build(1,nid,1);
    
    sum=0;
    for(int i=1;i<=id;i++){
        int x=lower_bound(v+1,v+vid+1,sum)-v;
        int y=lower_bound(v+1,v+vid+1,(sum+len[i])%d)-v;
        
        if(sum+len[i]<d){
            modify(1,nid,1,x,y-1,A[i]);
        }
        else{
            modify(1,nid,1,x,nid,A[i]);
            
            int t=(sum+len[i])/d-sum/d-1;
            mat S=ksm(A[i],t);
            modify(1,nid,1,1,nid,S);
            
            modify(1,nid,1,1,y-1,A[i]);
        }
        sum=(sum+len[i])%d;
    }
    
    search(1,nid,1);
    swap(id,nid);
    swap(len,nlen);
    
    solve(d,d-L%d);
}

signed main(){
    cin>>n>>m>>k>>L;
    int x,y;
    exgcd(k,L,x,y);
    int d=(x%L+L)%L;
    
    for(int i=1;i<=m;i++) cin>>seq[i];
    
    for(int t=1;t<=n;t++){
        int l,v; cin>>l>>v;
        
        id++;
        len[id]=l;
        A[id]=mat(1);
        for(int i=1;i<=m;i++){
            if(v==seq[i]){
                A[id].P[i-1][i]=1;
            }
        }
    }
    solve(L,d);
    
    cout<<A[1].P[0][m];
}

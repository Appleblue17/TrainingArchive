#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=10;
int T,n;

int P[N][N],Q[N][N],R[N][N];
int A[N][N],B[N][N],C[N][N],D[N][N];

int perfect_square(int x){
    if(x<=0) return -1;
    int r=sqrt(x);
    while(r*r<x) r++;
    while(r*r>x) r--;
    if(r*r==x) return r;
    return -1;
}
int phi(int n){
    int x=n;
    for(int i=2;i*i<=x;i++){
        if(x%i) continue;
        n=n/i*(i-1);
        while(x%i==0) x/=i;
    }
    if(x>1) n=n/x*(x-1);
    return n;
}
int ksm(int a,int x,int p){
    int tot=1;
    while(x){
        if(x & 1ll) tot=tot*a%p;
        a=a*a%p;
        x>>=1ll;
    }
    return tot;
}
int gaussian(int a[N][N],int n,int m){
    int cur=0;
    int sgn=1;
    for(int t=0;t<m;t++){
        int x=cur;
        while(x<n && !a[x][t]) x++;
        if(x>=n) continue;
        
        if(x!=cur){
            for(int j=t;j<m;j++)
                swap(a[cur][j],a[x][j]);
            sgn*=-1;
        }
        if(a[cur][t]<0){
            for(int j=t;j<m;j++) a[cur][j]*=-1;
            sgn*=-1;
        }
        for(int i=cur+1;i<n;i++){
            
            if(a[i][t]<0){
                for(int j=t;j<m;j++) a[i][j]*=-1;
                sgn*=-1;
            }
            
            while(a[cur][t] && a[i][t]){
				int x=cur,y=i;
				if(a[x][t]<a[y][t]) swap(x,y);
				int d=a[x][t]/a[y][t];
				for(int j=t;j<m;j++) a[x][j]-=a[y][j]*d;
			}
            
            if(!a[cur][t]){
				for(int j=t;j<m;j++) swap(a[cur][j],a[i][j]);
				sgn*=-1;
			}
        }
        cur++;
    }
    
    int det=sgn;
    for(int i=0;i<n;i++) det*=a[i][i];
    return det;
}

signed main() {
    cin>>T;
    while(T--){
        scanf("%lld",&n);
        
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                A[i][j]=B[i][j]=C[i][j]=D[i][j]=0;
        
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                scanf("%lld",&P[i][j]);
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                P[i][j+n]=(i==j);
        
        int det=gaussian(P,n,n*2);
        
        int rt=perfect_square(det);
        if(rt==-1){
            puts("No");
            continue;
        }
        
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                Q[i][j]=P[i][j+n];
                Q[i][j+n]=(i==j);
            }
        }
        
        gaussian(Q,n,2*n);
        for(int i=n-1;i>=0;i--){
            for(int t=0;t<i;t++){
                if(Q[t][i]){
                    int w=Q[t][i];
                    for(int j=i;j<n*2;j++) Q[t][j]-=Q[i][j]*w;
                }
            }
        }
        
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                C[i][j]=P[i][j];
            }
        }
        
        for(int k=0;k<n;k++){
            B[k][k]=__gcd(rt,C[k][k]);
            A[k][k]=C[k][k]/B[k][k];
            rt/=B[k][k];
            int phi_b=phi(B[k][k]);
            
            int p=B[k][k];
            
            for(int i=k-1;i>=0;i--){
                B[i][k]=C[i][k]%p*ksm(A[i][i]%p,phi_b-1,p)%p;
                assert(B[i][k]*A[i][i]%p==C[i][k]%p);
                for(int t=0;t<=i;t++) C[t][k]-=A[t][i]*B[i][k];
            }
            
            for(int i=0;i<=k;i++){
                assert(C[i][k]%p==0);
                A[i][k]=C[i][k]/p;
            }
        }
        
        for(int i=0;i<n;i++){
            for(int k=0;k<n;k++){
                for(int j=0;j<n;j++){
                    D[i][k]+=Q[i][j+n]*A[j][k];
                }
            }
        }
        
        printf("Yes\n");
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++)
                printf("%lld ",D[i][j]);
            printf("\n");
        }
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++)
                printf("%lld ",B[i][j]);
            printf("\n");
        }
        
        for(int i=0;i<n;i++){
            for(int k=0;k<n;k++){
                for(int j=0;j<n;j++){
                    R[i][k]+=D[i][j]*B[j][k];
                }
            }
        }
    }
}

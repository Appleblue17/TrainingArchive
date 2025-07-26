#include <bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int cas,n;
char S[N],T[N];
int typ[N];

vector <int> A[N];
int p[3];

char P[N],Q[N];
void qry(){
    printf("? ");
    for(int i=n-1;i>=0;i--) putchar(P[i]);
    printf(" ");
    for(int i=n-1;i>=0;i--) putchar(Q[i]);
    printf("\n");
    fflush(stdout);
}
int another(int x,int y){
    return 3-x-y;
}

int main(){
    scanf("%d",&cas);
    while(cas--){
        scanf("%d",&n);
        for(int i=0;i<=n;i++) A[i].resize(3);
        
        for(int i=0;i<n;i++) P[i]='0';
        for(int i=0;i<n;i++) Q[i]='1';
        qry();
        scanf("\n%s",S);
        reverse(S,S+n+1);
        
        int c=0;
        for(int i=0;i<n;i++){
            int d;
            if(!c){
                if(S[i]=='0') typ[i]=2,d=0;
                if(S[i]=='1') typ[i]=1,d=0;
                if(S[i]=='2') typ[i]=3,d=1;
            }
            else{
                if(S[i]=='0') typ[i]=6,d=1;
                if(S[i]=='1') typ[i]=4,d=1;
                if(S[i]=='2') typ[i]=5,d=0;
            }
            c=d;
        }
        
        for(int i=0;i<n;i++){
            int x=typ[i];
            if(x==1 || x==3 || x==4 || x==5) P[i]=Q[i]='1';
            else P[i]=Q[i]='2';
        }
        
        qry();
        scanf("\n%s",T);
        reverse(T,T+n+1);
        
        c=T[n]-'0';
        for(int i=n-1;i>=0;i--){
            int d;
            int x=T[i]-'0';
            
            switch(typ[i]){
                case 1:
                    if(!c && x==2) A[i]={0,1,2},d=0;
                    if(c && x==0) A[i]={0,1,2},d=1;
                    if(c && x==2) A[i]={0,2,1},d=0;
                    if(c && x==1) A[i]={0,2,1},d=1;
                    break;
                case 2:
                    if(c && x==0) A[i]={1,0,2},d=0;
                    if(c && x==2) A[i]={1,0,2},d=1;
                    if(!c && x==0) A[i]={2,0,1},d=0;
                    if(c && x==1) A[i]={2,0,1},d=1;
                    break;
                case 3:
                    if(c && x==0) A[i]={1,2,0},d=0;
                    if(c && x==1) A[i]={1,2,0},d=1;
                    if(!c && x==0) A[i]={2,1,0},d=0;
                    if(c && x==2) A[i]={2,1,0},d=1;
                    break;
                case 4:
                    if(!c && x==1) A[i]={2,0,1},d=0;
                    if(!c && x==2) A[i]={2,0,1},d=1;
                    if(!c && x==0) A[i]={2,1,0},d=0;
                    if(c && x==2) A[i]={2,1,0},d=1;
                    break;
                case 5:
                    if(!c && x==2) A[i]={0,1,2},d=0;
                    if(c && x==0) A[i]={0,1,2},d=1;
                    if(!c && x==1) A[i]={1,0,2},d=0;
                    if(!c && x==0) A[i]={1,0,2},d=1;
                    break;
                case 6:
                    if(!c && x==1) A[i]={0,2,1},d=0;
                    if(c && x==0) A[i]={0,2,1},d=1;
                    if(!c && x==2) A[i]={1,2,0},d=0;
                    if(!c && x==0) A[i]={1,2,0},d=1;
                    break;
            }
            c=d;
        }
        
        printf("! ");
        for(int i=0;i<n;i++){
            for(int t=0;t<3;t++) p[A[i][t]]=t;
            for(int t=0;t<3;t++) printf("%d",p[t]);
            printf(" ");
        }
        printf("\n");
        fflush(stdout);
        
    }
    
}

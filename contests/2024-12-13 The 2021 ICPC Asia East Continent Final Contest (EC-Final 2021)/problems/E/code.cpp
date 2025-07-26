#include<bits/stdc++.h>
using namespace std;
const int N=55;

void YES(){
    puts("Pang");
}
void NO(){
    puts("Shou");
}

int trans(char c){
    if(c>='2' && c<='9') return c-'0';
    switch(c){
        case 'T': return 10;
        case 'J': return 11;
        case 'Q': return 12;
        case 'K': return 13;
        case 'A': return 14;
    }
}

int T,n,m;
char S[5];
int A[15],B[15],P;

int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);
        scanf("\n");
        memset(A,0,sizeof(A));
        memset(B,0,sizeof(B));
        for(int i=1;i<=n;i++){
            scanf("%s",S);
            int x=trans(S[0]);
            A[x]++;
        }
        scanf("\n");
        for(int i=1;i<=m;i++){
            scanf("%s",S);
            int x=trans(S[0]);
            B[x]++;
        }
        scanf("\n");
        scanf("%s",S);
        P=trans(S[0]);
        
        int A0=0,A1=0,B0=0,B1=0;
        int mxA0=0,mxB0=0;
        int mxA1=0,mxB1=0;
        for(int i=2;i<P;i++){
            if(A[i]){
                A0+=A[i];
                mxA0=max(mxA0,i);
            }
            if(B[i]){
                B0+=B[i];
                mxB0=max(mxB0,i);
            }
        }
        for(int i=P;i<=14;i++){
            if(A[i]){
                A1+=A[i];
                mxA1=max(mxA1,i);
            }
            if(B[i]){
                B1+=B[i];
                mxB1=max(mxB1,i);
            }
        }
        
        // cout<<A0<<" "<<A1<<" "<<B0<<" "<<B1<<endl;
        // cout<<mxA0<<" "<<mxB0<<" "<<mxA1<<" "<<mxB1<<endl;
        if(n==1) NO();
        else{
            if(A0==0) NO();
            else{
                if(B1==0){
                    if(B0>=2) YES();
                    else{
                        if(mxA0<mxB0) NO();
                        else YES();
                    }
                }
                else{
                    if(B0>=2) YES();
                    else if(B0==0) NO();
                    else if(B0==1){
                        if(A1==0) NO();
                        else{
                            if(A0==1) NO();
                            else{
                                if(mxA1>mxB1 && mxA0>=mxB0){
                                    if(A0==2 && A1==1) NO();
                                    else YES();
                                }
                                else NO();
                            }
                        }
                    }
                }
            }
        }
        
    }
    
}

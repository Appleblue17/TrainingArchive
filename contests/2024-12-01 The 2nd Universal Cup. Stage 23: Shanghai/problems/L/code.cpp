#include <bits/stdc++.h>
using namespace std;
const int N=1100;
int T_,n,m;
char A[N],B[N];

int s[N],slen,tmp[N],id;

vector < pair<int,int> > ANS;
void rep(int l,int r){
    ANS.push_back(make_pair(l,r));
    
    if(r>slen){
        puts("Out of length!");
        assert(0);
    }
    int tot=0;
    for(int i=l;i<=r;i++)
        tot=tot*3+s[i];
    id=0;
    do{
        tmp[++id]=tot & 1,tot>>=1;
    }while(tot);
    
    int del=id-(r-l+1);
    // cout<<id<<" "<<del<<endl;
    if(del>0)
        for(int i=slen;i>r;i--) s[i+del]=s[i];
    else
        for(int i=r+1;i<=slen;i++) s[i+del]=s[i];
    slen+=del;
    for(int i=0;i<id;i++) s[l+i]=tmp[id-i];
    
    // cout<<"  ";
    // for(int i=1;i<=slen;i++) cout<<s[i];
    // cout<<endl;
}
void prans(){
    printf("%d\n",ANS.size());
    for(pair<int,int> tmp: ANS) printf("%d %d\n",tmp.first,tmp.second);
}
void nosol(){
    printf("-1\n");
}
bool check(){
    if(slen!=m) return 0;
    for(int i=1;i<=m;i++) if(s[i]+'0'!=B[i]) return 0;
    return 1;
}


void sol1(int x,int l,int r){
    // 111000 => 10
    while(l>1){
        rep(x-1,x);
        l--,r+=2;
        x--;
    }
    
    rep(x+1,x+r);
}
void sol2(int x,int L,int R){
    // 10 => 111000
    int l=1,r=1;
    while(r<R){
        rep(x,x+1);
        rep(x,x+1);
        r++;
    }
    while(l<L){
        rep(x,x+1);
        rep(x,x+1);
        rep(x,x+1);
        x++;
        l++;
    }
}
void sol3(int x){
    // 10 => 1010
    rep(x,x+1);
    rep(x,x+1);
    rep(x,x+2);
    rep(x+1,x+2);
    rep(x,x+2);
}
void sol4(int x){
    // 1010 => 10
    rep(x,x+1);
    sol1(x+2,3,1);
}


int f[N],g[N],cnt;


int main(){
    // freopen("1.txt","r",stdin);
    scanf("%d",&T_);
    while(T_--){
        ANS.clear();
        cnt=0;
        
        scanf("\n%s",A+1);
        scanf("\n%s",B+1);
        n=strlen(A+1);
        m=strlen(B+1);
        
        slen=n;
        for(int i=1;i<=n;i++) s[i]=A[i]-'0';
        
        int stA=0,stB=0;
        while(stA+1<=n && A[stA+1]=='0') stA++;
        while(stB+1<=m && B[stB+1]=='0') stB++;
        
        if(stA<stB){
            nosol();
            continue;
        }
        
        
        if(stB==m || stA==n){
            if(stA!=n || stB!=m) nosol();
            else{
                rep(1,stA-stB+1);
                prans();
            }
            continue;
        }
        rep(1,stA-stB+1);
        
        if(stA+1==n || stB+1==m){
            // A: 00..01
            if(stA+1==n && stB+1==m) prans();
            else nosol();
            continue;
        }
        
        int cur=stA,nw=stB,num=0;
        while(cur<n){
            int x=cur;
            while(A[x+1]=='1') x++;
            int l=x-cur, y=x;
            while(A[y+1]=='0') y++;
            int r=y-x;
            
            // cout<<"   "<<cur<<" "<<l<<" "<<r<<endl;
            if(!r){
                if(l>1){
                    rep(nw+l-1,nw+l); // 11 => 100
                    l--,r+=2;
                }
                else{
                    rep(nw-1,nw+1);
                    num++;
                    break;
                }
            }
            sol1(nw+l,l,r);
            num++;
            cur+=l+r;
            nw+=2;
        }
        if(num==1){
            sol3(stB+1);
            num++;
        }
        
        
        
        
        cur=stB;
        while(cur<m){
            int x=cur;
            while(B[x+1]=='1') x++;
            int l=x-cur, y=x;
            while(B[y+1]=='0') y++;
            int r=y-x;
            
            if(!r){
                // puts("here");
                if(l>1){
                    int pos=stB+(num-1)*2;
                    sol2(pos+1,l-1,1);
                    rep(pos+l-1,pos+l);
                    num--;
                }
                else{
                    int pos=stB+(num-2)*2;
                    rep(pos+3,pos+4);
                    rep(pos+1,pos+3);
                    sol4(pos+1);
                    num--;
                }
                
                break;
            }
            f[++cnt]=l,g[cnt]=r;
            cur+=l+r;
        }
        
        // cout<<"num: "<<num<<endl;
        
        while(num<cnt){
            sol3(stB+1);
            num++;
        }
        while(num>cnt){
            sol4(stB+1);
            num--;
        }
        
        
        cur=stB;
        for(int i=1;i<=cnt;i++){
            sol2(cur+1,f[i],g[i]);
            cur+=f[i]+g[i];
        }
        
        // for(int i=1;i<=slen;i++) cout<<s[i];
        // cout<<endl;
        if(!check()){
            puts("WA");
            assert(0);
        }
        prans();
    }
    
}


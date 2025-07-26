#include<bits/stdc++.h>
using namespace std;
int a[6],b[6],c[6],b2[6];
int read_card(){
    char c = getchar();
    while(!((c >= '2' && c <= '9') || (c >= 'A' && c <= 'Z'))){
        c = getchar();
    }
    char s = getchar();
    int ret;
    if(s == 'C')ret=0;
    else if(s == 'D')ret=13;
    else if(s == 'H')ret=26;
    else if(s == 'S')ret=39;
    if(c == 'A')ret+=0;
    if(c >= '2' && c <= '9')ret += c-'1';
    if(c == 'T')ret+=9;
    if(c == 'J')ret+=10;
    if(c == 'Q')ret+=11;
    if(c == 'K')ret+=12;
    return ret;
}
bool check(){
    if(b2[1] == 0){//'A'
        if(b2[2]==9 && b2[3]==10 && b2[4]==11 && b2[5]==12){
            return 1;
        }
    }
    if(!(b2[1]+1==b2[2] && b2[2]+1==b2[3] && b2[3]+1==b2[4] && b2[4]+1==b2[5])){
        return 0;
    }
    else return 1;
}
void solve(){
    for(int i=1;i<=5;i++){
        a[i]=read_card();
        
    }
    for(int i=1;i<=5;i++){
        b[i]=a[i]%13;
        b2[i]=b[i];
        c[i]=a[i]/13;
    }
    sort(b2+1,b2+6);
    if(!(c[1]==c[2] && c[2]==c[3] && c[3]==c[4] && c[4]==c[5])){
        printf("check\n");
        return;
    }
    
    int mx = b2[5];
    if(!check()){
        printf("check\n");
        return;
    }
    if(b2[1]==0 && b2[5]==12){
       printf("allin\n");
       return; 
    }
    int len=0;
    for(int k=5;k>=3;k--){
        bool fl=0;
        for(int i=3;i<=5;i++){
            if(b[i]==b2[k]){
                len++;fl=1;
                break;
                
            }
        }
        if(!fl)break;
    }
    //printf("len=%d\n",len);
    if(b2[1]==0){//only A2345
        bool fl=0;
        for(int i=3;i<=5;i++){
            if(b[i]==b2[1]){
                fl=1;
                break;
                
            }
        }
        if(fl){
            printf("check\n");
            return;
        }
    }
    if(len==0){
        printf("allin\n");
        return;
    }
    
    int mn = b2[5]+5-len;
    if(mn <= 13){
        printf("check\n");
    }
    else printf("allin\n");
}
int main(){
    int T;
    cin >> T;
    while(T--){
        solve();
    }
}

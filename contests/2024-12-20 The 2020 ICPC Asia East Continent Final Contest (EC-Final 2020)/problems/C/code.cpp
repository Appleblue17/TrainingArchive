#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const int N=1e5+5,m=50;

int n;
int p[N],q[N];
int a[N];


ull f[55][64];
ull rnd(ull x){ //this is a xor-shift random generator
    x ^= x << 13;
    x ^= x >> 7;
    x ^= x << 17;
    return x;
}

bool check(ull seed){
    for(int i=1;i<=n;i++){
        seed=rnd(seed);
        if(seed%i+1!=a[i]) return 0;
    }
    return 1;
}

ull D[64];
bool B[64];
void ins(ull x,bool t){
    // cout<<"ins "<<x<<" "<<t<<endl;
    for(int i=63;i>=0;i--){
        if(!(x>>i & 1)) continue;
        if(!D[i]){
            D[i]=x; B[i]=t;
            return ;
        }
        else{
            x^=D[i],t^=B[i];
        }
    }
    // puts("fail");
}

ull g[N];
int id;

// void ck(ull x){
//     cout<<x<<": ";
//     for(int i=63;i>=0;i--){
//         bool tot=0;
//         for(int j=0;j<64;j++){
//             tot^=(D[i]>>j & 1ull) & (x>>j & 1ull);
//         }
//         putchar(tot+'0');
//     }
//     cout<<endl;
// }

int main(){
    // freopen("1.txt","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&p[i]),q[p[i]]=i;
    
    for(int i=n;i>=1;i--){
        int x=q[i];
        a[i]=x;
        swap(q[p[i]],q[p[x]]);
        swap(p[i],p[x]);
    }
    
    // for(int i=1;i<=n;i++) cout<<a[i]<<" ";
    for(int i=0;i<64;i++) f[0][i]=1ull<<i;
    
    for(int t=1;t<=50;t++){
        for(int i=0;i<64;i++) f[t][i]=rnd(f[t-1][i]);
    }
    
    for(int t=1;t<=50;t++){
        int x=t,c=0;
        while(x%2==0) x/=2,c++;
        if(!c) continue;
        int r=(a[t]-1)%(1<<c);
        
        for(int i=0;i<c;i++){
            ull mac=0;
            for(int j=0;j<64;j++){
                mac |= (f[t][j]>>i & 1ull) << j;
            }
            ins(mac,r>>i & 1);
        }
        
    }
    // for(int i=0;i<64;i++) cout<<D[i]<<" "<<B[i]<<endl;
    
    for(int i=0;i<64;i++){
        for(int j=i+1;j<64;j++){
            if(D[j]>>i & 1ull) D[j]^=D[i],B[j]^=B[i];
        }
    }
    ull sp=0;
    for(int i=0;i<64;i++) sp^=(ull)B[i]<<i;
    
    for(int i=63;i>=0;i--){
        if(!D[i]){
            ull mac=1ull<<i;
            for(int j=i+1;j<64;j++)
                mac |= (D[j]>>i & 1ull) << j;
            g[id++]=mac;
        }
    }
    
    // for(int i=63;i>=0;i--){
    //     for(int j=63;j>=0;j--){
    //         putchar((D[i]>>j & 1ull)+'0');
    //     }
    //     cout<<" "<<B[i]<<endl;
    // }
    
    // for(int i=0;i<id;i++) ck(g[i]);
    // return 0;
    // cout<<id<<" "<<sp<<endl;
    // for(int i=0;i<id;i++) cout<<g[i]<<" ";
    // cout<<endl;
    for(int mac=0;mac<(1<<id);mac++){
        ull seed=sp;
        for(int i=0;i<id;i++){
            if(mac>>i & 1) seed^=g[i];
        }
        if(check(seed)){
            cout<<seed;
            return 0;
        }
    }
    puts("NOT FOUND");
    assert(0);
}

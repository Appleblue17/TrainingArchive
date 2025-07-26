#include<bits/stdc++.h>
using namespace std;
#define vi vector <int>

const int N=1e5+5;
int n,id;
bool ans[N];
vector <int> ANS[N];

vi solve(int l,int r,vi V){
    int len=r-l+1;
    
    if(len==1) return V;
    if(len==2){
        // cout<<"! "<<l<<" "<<r<<" | ";
        // for(int x: V) cout<<x<<" ";
        // cout<<endl;
        // cout<<"[2] "<<id+1<<" "<<id+2<<endl;
        int sav=id;
        id++; ans[id]=0; ANS[id]=(vi){V[0],V[1]};
        id++; ans[id]=1; ANS[id]=(vi){V[0],V[1]};
        return (vi){sav+1,sav+2};
    }
    
    int mid=(l+r)>>1,lenl=mid-l+1,lenr=r-mid;
    vi L,R;
    for(int i=0;i<=mid-l;i++) L.push_back(V[i]);
    for(int i=mid-l+1;i<=r-l;i++) R.push_back(V[i]);
    
    vi NL = solve(l,mid,L);
    vi NR = solve(mid+1,r,R);
    
    // cout<<"! "<<l<<" "<<r<<" | ";
    // for(int x: V) cout<<x<<" ";
    // cout<<endl;
    // cout<<"L "; for(int x: NL) cout<<x<<" "; cout<<endl;
    // cout<<"R "; for(int x: NR) cout<<x<<" "; cout<<endl;
    // int sav=id;
    
    vi NV;
    for(int i=0;i<=r-l;i++){
        int sav=id;
        
        // cout<<"i="<<i<<": ";
        
        int num=r-l+1-i;
        for(int j=0;j<=num;j++){
            int k=num-j;
            if(j<=lenl && k<=lenr){
                id++; ans[id]=0;
                for(int t=lenl-j;t<lenl;t++) ANS[id].push_back(NL[t]);
                for(int t=lenr-k;t<lenr;t++) ANS[id].push_back(NR[t]);
                
                // cout<<id<<" ";
            }
        }
        
        id++; ans[id]=1;
        for(int t=sav+1;t<id;t++) ANS[id].push_back(t);
        NV.push_back(id);
        
        // cout<<"==> "<<id<<endl;
    }
    return NV;
}
int s[N];
int main(){
    // freopen("1.txt","w",stdout);
    cin>>n;
    id=n;
    
    vi P;
    for(int i=1;i<=n;i++) P.push_back(i);
    vi R = solve(1,n,P);
    
    int pos=n/2+1;
    id++; ans[id]=1; ANS[id]=(vi){R[pos-1]};
    
    cout<<id-n<<endl;
    for(int i=n+1;i<=id;i++){
        // cout<<i<<": ";
        if(!ans[i]) printf("AND ");
        else printf("OR ");
        
        assert(ANS[i].size());
        for(int x: ANS[i]) assert(x<i);
        
        printf("%d ",ANS[i].size());
        for(int x: ANS[i]) printf("%d ",x);
        printf("\n");
    }
    
    // for(int i=1;i<=n;i++) cin>>s[i];
    // int mx=0;
    // for(int i=n+1;i<=id;i++){
    //     if(!ans[i]){
    //         s[i]=1;
    //         // for(int x: ANS[i]) s[i]=max(s[i],s[x]+1);
    //         for(int x: ANS[i]) s[i]&=s[x];
    //     }
    //     else{
    //         s[i]=0;
    //         // for(int x: ANS[i]) s[i]=max(s[i],s[x]+1);
    //         for(int x: ANS[i]) s[i]|=s[x];
    //     }
    //     mx=max(mx,s[i]);
    // }
    // cout<<mx;
    // for(int x: R) cout<<s[x]<<" ";
    // cout<<endl;
    // cout<<s[id];
}

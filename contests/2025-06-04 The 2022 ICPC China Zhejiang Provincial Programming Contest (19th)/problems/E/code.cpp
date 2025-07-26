#include <bits/stdc++.h>
using namespace std;
// #define int long long
const int N=1100,M=11;
const double INF=1e15,eps=1e-6;
int n,H,S,K,T1,T2;
double p[N];
bool totem[N];
double f[N][M][M];


signed main(){
    cin>>n>>H>>S;
    for(int i=1;i<=n;i++){
        int x; cin>>x;
        // int x=1;
        p[i]=1.0*x/100;
    }
    cin>>K;
    for(int i=1;i<=K;i++){
        int x; cin>>x;
        totem[x]=1;
    }
    cin>>T1>>T2;
    
    for(int i=n;i>=1;i--){
        // cout<<i<<": "<<endl;
        
        if(totem[i] && S>0){
            // h=2
            f[i][2][S]=(1+p[i]*f[i+1][2][S]+(1-p[i])*min(T1,T2))/p[i];
            f[i][1][S]=f[i][2][S]+T1;
            
            bool flag=1;
            int cnt=0;
            while(flag && cnt<=100000){
                // h>2
                for(int h=3;h<=H;h++){
                    int cnt=0;
                    for(int mc=0;mc<=1;mc++){
                        if(mc){
                            f[i][h][S]=(1+p[i]*f[i+1][h][S]+(1-p[i])*min(T1,T2))/p[i];
                        }
                        else{
                            f[i][h][S]=1+p[i]*f[i+1][h][S]+(1-p[i])*f[i][h-1][S];
                        }
                        bool fl=(f[i][h][S]+min(T1,T2)<=f[i][h-1][S]);
                        if(fl==mc) break;
                    }
                }
                
                cnt++;
                flag=0;
                for(int h=H-1;h>=1;h--){
                    if(f[i][h+1][S]+T1<f[i][h][S]-eps){
                        f[i][h][S]=f[i][h+1][S]+T1;
                        flag=1;
                    }
                }
                for(int h=H;h>=1;h--){
                    for(int s=0;s<S;s++){
                        f[i][h][s]=f[i][h][S];
                    }
                }
            }
        }
        else{
            f[i][1][0]=INF;
            
            for(int mac_=0;mac_<(1<<S);mac_++){
                int mac=mac_<<1 | 1;
                for(int s=0;s<=S;s++){
                    if(mac>>s & 1){
                        f[i][2][s]=(1+p[i]*f[i+1][2][s]+(1-p[i])*T2)/p[i];
                    }
                    else{
                        f[i][2][s]=1+p[i]*f[i+1][2][s]+(1-p[i])*(f[i][2][s-1]+T1);
                    }
                }
                
                bool flag=1;
                for(int s=1;s<=S;s++){
                    bool fl=(f[i][2][s]+T2<=f[i][2][s-1]+T1);
                    if((mac>>s & 1)!=fl) flag=0;
                }
                
                if(flag) break;
            }
            for(int s=1;s<=S;s++) f[i][1][s]=f[i][2][s-1]+T1;
            
            // h>2
            for(int h=3;h<=H;h++){
                for(int s=0;s<=S;s++){
                    for(int mc=0;mc<=1;mc++){
                        if(mc){
                            f[i][h][s]=(1+p[i]*f[i+1][h][s]+(1-p[i])*T2)/p[i];
                        }
                        else{
                            f[i][h][s]=1+p[i]*f[i+1][h][s]+(1-p[i])*f[i][h-1][s];
                        }
                        bool fl=(f[i][h][s]+T2<=f[i][h-1][s]);
                        if(fl==mc) break;
                    }
                }
            }
        }
        // for(int h=1;h<=H;h++){
        //     for(int s=0;s<=S;s++){
        //         cout<<f[i][h][s]<<" ";
        //     }
        //     cout<<endl;
        // }
    }
    
    // for(int i=1;i<=n;i++){
    //     for(int h=1;h<=H;h++){
    //         for(int s=0;s<=S;s++){
    //             double A=f[i][h][s],B;
    //             if(totem[i]){
    //                 if(h==H) B=f[i][h][S];
    //                 else{
    //                     B=min(f[i][h][S],f[i][h+1][S]+T1);
    //                 }
    //             }
    //             else{
    //                 if(h==1){
    //                     if(s==0) B=INF;
    //                     else B=f[i][h+1][s-1]+T1;
    //                 }
    //                 else{
    //                     B=1+p[i]*f[i+1][h][s]+(1-p[i])*min(f[i][h-1][s],f[i][h][s]+T2);
    //                 }
    //             }
    //             if(fabs(A-B)>eps){
    //                 cout<<setprecision(10)<<fixed<<A<<" "<<B<<"  "<<i<<" "<<h<<" "<<s<<endl;   
    //             }
    //         }
    //     }
    // }
    
    cout<<setprecision(10)<<fixed<<f[1][H][S]<<endl;
}

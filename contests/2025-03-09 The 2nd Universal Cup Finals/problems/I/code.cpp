#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1000010;

int pre[N][2];
char s[N];
ll n, m;
ll solve()
{
    pre[0][0]=pre[0][1]=0;
    
    ll cnta=0,cntb=0,ra=0,rb=0;
    for(int i=1;i<=n;i++){
        if(s[i]=='A'){
            pre[i][0]=pre[i-1][0]+1;
            pre[i][1]=pre[i-1][1];
        }
        else{
            pre[i][0]=pre[i-1][0];
            pre[i][1]=pre[i-1][1]+1;
        }
    }
    if(pre[n][0]==0 || pre[n][1]==0){
        if(m != 1)printf("Yes\n%lld\n",m);
        else printf("Yes\n%lld\n",m+1);
        if(m != 1)return m;
        else return m+1;
    }
    cnta = (m-1)/pre[n][0];
    cntb = (m-1)/pre[n][1];
    for(ll i=1;i<=n;i++){
        if(pre[i][0] == (m-1)%pre[n][0]+1){
            ra = i;
            break;
        }
    }
    for(ll i=1;i<=n;i++){
        if(pre[i][1] == (m-1)%pre[n][1]+1){
            rb = i;
            break;
        }
    }
    __int128 A,B,C;
    A = (__int128)cnta*(__int128)n+(__int128)ra;
    B = (__int128)cntb*(__int128)n+(__int128)rb;
    
    C = min(A,B);
    ll k = C;
    //ll k = min(cnta*n+ra,cntb*n+rb);
    //cout << cntb*n+rb << endl;
    //printf("%lld %lld %lld %lld %lld\n",cnta,cntb,ra,rb,k);
    
    
    
    cnta = k/n*pre[n][0]+pre[k%n][0];
    cntb = k/n*pre[n][1]+pre[k%n][1];
    //printf("cnta=%lld,cntb=%lld\n",cnta,cntb);
    if(abs(cnta-cntb)>=2){
        printf("Yes\n%lld\n",k);
        return k;
    }
    for(ll j=1;j<=n*5;j++){
        
        char c = s[(k+j-1)%n+1];
        if(c == 'A')cnta++;
        else cntb++;
        if(abs(cnta-cntb)>=2){
            printf("Yes\n%lld\n",k+j);
            return k+j;
        }
    }
    printf("No\n");
    return -1;
}

ll solve2(){
    ll cnta=0,cntb=0,ra=0,rb=0;
    //int sb=0;
    //cout<<"??? "<<m<<endl;
    for(int j=1;j<=max(n*10,m*10);j++){
        //sb++;
        //cout<<j<<" "<<m<<" "<<(j<=m)<<endl;
        //printf("cnta=%lld,cntb=%lld,j=%lld,m=%lld\n",cnta,cntb,j,m);
        //cout << (j<=m) << endl;
        char c = s[(j-1)%n+1];
        if(c == 'A')cnta++;
        else cntb++;
        // printf("c=%c\n",c);
        //if(sb >= 1000){
         //   exit(0);
        //}
        if(abs(cnta-cntb)>=2 && (cnta >= m || cntb >= m)){
            //printf("Yes\n%lld\n",j);
            return j;
        }
    }
    return -1;
}

int main()
{
    //freopen("I.in","r",stdin);
    //freopen("I.out","w",stdout);
    int t;
    cin >> t;
    while (t--)
    {
        scanf("%lld%lld", &n, &m);
        scanf("%s", s+1);
        /*if(solve() != solve2()){
            cout << "wrong" << t << endl;
            cout << n << ' ' << m << endl;
            printf("s1 = %lld,s2 = %lld\n",solve(),solve2());
            printf("%s\n",s+1);
        }*/
        solve();
        //solve2();
    }
}

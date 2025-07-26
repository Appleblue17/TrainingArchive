#pragma GCC optimize(2)
#pragma GCC optimize(3)
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
typedef long long ll;
char s[20];
mt19937_64 rng(114);
ll rem[1100];
bool r[1100][1100];
vector<ll> p;

bool ip(ll x){
    for(ll i=2;i*i<=x;i++){
        if(x%i==0)return 0;
    }
    return 1;
}

ll X=123456789012345;
int query2(ll y){
    printf("? %lld\n",y);fflush(stdout);
    if(ip(X+y))return 1;
    else return 0;
}
int query(ll y){
    printf("? %lld\n",y);fflush(stdout);
    scanf("%s",s);
    if(s[0]=='P')return 1;
    else return 0;
}
__int128 x[N],y[N];
__int128 exgcd(long long dep,long long a,long long b){
	if(!b){
		x[dep]=1,y[dep]=0;
		return a;
	}
	long long g=exgcd(dep+1,b,a%b);
	x[dep]=y[dep+1];
	y[dep]=x[dep+1]-a/b*y[dep+1];
	return g;
}
ll cnt=0,tr=0;
void solve(){
    memset(r,0,sizeof(r));
    memset(rem,-1,sizeof(rem));
    
    __int128 A=0,B=0;
    while(1){
        tr++;
        //if(tr >= 100000)exit(-1);
        ll ra = llabs(rng())%(ll)(1e13);
        if(rem[2]!=-1){
            if(rem[2]==0)ra=ra*2+1;
            else ra=ra*2;
        }
        
        bool f=0;
        for(int i:p){
            if(rem[i]!=-1 && (ra%i+rem[i])%i==0){
                f=1;
                break;
            }
            if(rem[i]==-1){
                if(r[i][i-(ra-1)%i-1]==1){
                    f=1;
                    break;
                }
            }
            
            
        }
        if(f)continue;
        ll y = query(ra);
        cnt++;
        if(y==1){
            for(ll i=2;i<=100;i++){
                //x%p + y%p!=0,x%p != -y%p
                r[i][i-(ra-1)%i-1]=1;
                //printf("recorded r[%lld][%lld]=1\n",i,i-(x-1)%i-1);fflush(stdout);
                ll pos=-1;
                for(ll j=0;j<i;j++){
                    if(r[i][j]==0){
                        if(pos == -1){
                            pos = j;
                        }
                        else{
                            pos = -2;
                        }
                    }
                }
                if(pos >= 0){
                    //printf("rem[%lld] finalized as %lld\n",i,pos);fflush(stdout);
                    rem[i]=pos;
                }
            }
        }
        A=2,B=rem[2];
	for(long long i=3;i<=100;i++){
        if(rem[i]==-1)continue;
		__int128 g=exgcd(1,A,i),d=rem[i]-B;
        //assert(g != 0);
		//if(d%g) return puts("-1"),0;
		__int128 t=d/g*x[1];
		B=t*A+B;
		A=A/g*i;
        //assert(A != 0);
		B=(B%A+A)%A;
        //printf("i=%lld,A=%lld,B=%lld\n",i,(ll)A,(ll)B);
        if(A>2e18)break;
	}
        if(A>2e18)break;
    }
    /*__int128 A=2,B=rem[2];
	for(long long i=3;i<=100;i++){
        if(rem[i]==-1)continue;
		__int128 g=exgcd(1,A,i),d=rem[i]-B;
        //assert(g != 0);
		//if(d%g) return puts("-1"),0;
		__int128 t=d/g*x[1];
		B=t*A+B;
		A=A/g*i;
        //assert(A != 0);
		B=(B%A+A)%A;
        //printf("i=%lld,A=%lld,B=%lld\n",i,(ll)A,(ll)B);
        if(A>2e18)break;
	}*/
    //printf("cnt=%lld,tr=%lld\n",cnt,tr);
	printf("! %lld\n",(long long)B);fflush(stdout);
    scanf("%s",s);
    if(s[0] == 'B')exit(0);
}
int main(){
    p.push_back(2);p.push_back(3);p.push_back(5);p.push_back(7);
    p.push_back(11);p.push_back(13);p.push_back(17);p.push_back(19);
    p.push_back(23);p.push_back(29);p.push_back(31);p.push_back(37);
    p.push_back(41);p.push_back(43);p.push_back(47);p.push_back(53);
    //p.push_back(59);
    //freopen("f.out","w",stdout);
    int T;
    scanf("%d",&T);
    while(T--){
        solve();
    }
}

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N=1e4+10;
ll n,k;

struct Point{
    ll x,y;
    Point(ll x=0,ll y=0):x(x),y(y){}
};

typedef Point Vector;

Vector operator - (Point A, Point B){ return Vector(A.x-B.x,A.y-B.y);}

bool operator == (Point A, Point B){
    if(A.x == B.x && A.y == B.y)return true;
    else return false;
}

Point p[N],q[N];
vector<int> ans[60];
int anscnt,id[N];
signed main() {
    scanf("%lld%lld", &n,&k);
    ll x,y;
    for(int i=1;i<=n;i++){
        scanf("%lld%lld",&x,&y);
        p[i] = Point(x,y);
        q[i]=p[i];
    }
    srand(39101);
    random_shuffle(p+1,p+n+1);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(q[j]==p[i])id[i]=j;
        }
    }
    //for(int i=1;i<=n;i++){
    //    printf("p(%lld,%lld),id[%d]=%d\n",p[i].x,p[i].y,i,id[i]);
    //}
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            map<ll,int> ma;
            Vector d = p[i]-p[j];
            if(d.x==0){
                for(int o=1;o<=n;o++){
                    ma[p[o].x]++;
                    if(ma.size()>k)break;
                }
                if(ma.size()==k){
                    ma.clear();
                    anscnt=0;
                    for(int i=0;i<=59;i++)ans[i].clear();
                    for(int o=1;o<=n;o++){
                        if(!ma[p[o].x]){
                            ma[p[o].x]=++anscnt;
                        }
                        ans[ma[p[o].x]].push_back(o);
                    }
                    bool f=0;
                    for(int i=1;i<=anscnt;i++){
                        if(ans[i].size()==1){
                            f=1;
                            break;
                        }
                    }
                    if(f)continue;
                    for(int i=1;i<=anscnt;i++){
                        cout << ans[i].size() << ' ';
                        for(int o : ans[i]){
                            printf("%d ",id[o]);
                        }
                        putchar('\n');
                    }
                    return 0;
                }
            }
            else{
                for(int o=1;o<=n;o++){
                    //double x = p[o].y - p[o].x/d.x*d.y;
                    ll x = p[o].y*d.x - p[o].x*d.y;
                    //printf("dir = (%lld,%lld),p = (%lld,%lld),x=%lld\n",d.x,d.y,p[o].x,p[o].y,x);
                    ma[x]++;
                    if(ma.size()>k)break;
                }
                if(ma.size()==k){
                    ma.clear();
                    anscnt=0;
                    for(int i=0;i<=59;i++)ans[i].clear();
                    for(int o=1;o<=n;o++){
                        ll x = p[o].y*d.x - p[o].x*d.y;
                        if(!ma[x]){
                            ma[x]=++anscnt;
                        }
                        ans[ma[x]].push_back(o);
                    }
                    bool f=0;
                    for(int i=1;i<=anscnt;i++){
                        if(ans[i].size()==1){
                            f=1;
                            break;
                        }
                    }
                    if(f)continue;
                    for(int i=1;i<=anscnt;i++){
                        cout << ans[i].size() << ' ';
                        for(int o : ans[i]){
                            printf("%d ",id[o]);
                        }
                        putchar('\n');
                    }
                    return 0;
                }
            }
        }
    }
}

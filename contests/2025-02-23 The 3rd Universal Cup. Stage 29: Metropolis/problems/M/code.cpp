#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;

typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
#define double ld
#define fi first
#define se second
#define N 1000010
#define mapa make_pair
typedef unsigned long long ull;
typedef pair<ull,ull> puu;
//mt19937_64 rng(GetTickCount());
template <typename T>inline void read(T &x){
	x=0;char c=getchar();bool f=0;
	for(;c<'0'||c>'9';c=getchar()) f|=(c=='-');
	for(;c>='0'&&c<='9';c=getchar())
	x=(x<<1)+(x<<3)+(c^48);
	x=(f?-x:x);
}
const int mo=1e9+7;
using namespace std;

struct Point{
    ld x,y;
    Point(ld x=0,ld y=0):x(x),y(y){}
};
typedef Point Vector;

Vector operator + (Vector A,Vector B){
    return Vector(A.x+B.x,A.y+B.y);
}
Vector operator - (Point A,Point B){
    return Vector(A.x-B.x,A.y-B.y);
}
Vector operator * (Vector A,ld p ){
    return Vector(A.x*p,A.y*p);
}
Vector operator / (Vector A,ld p ){
    return Vector(A.x/p,A.y/p);
}
const ld eps = 1e-10;
int dcmp(ld x){
    if(fabs(x)<eps) return 0;
    else return x<0? -1:1;
}

bool operator ==(const Point &a, const Point &b){
    return dcmp(a.x-b.x)==0 && dcmp(a.y-b.y)==0;
}



ll t,n,m,X[N],Y[N],Z[N],ans,k;

vector<Point> a,b;
Point ra;Vector rv;
const ld pi = atan2(0,-1);
ld Cross(Vector A,Vector B){
    return A.x*B.y - A.y*B.x;
}
Point GetLineIntersection(Point P,Vector v, Point Q, Vector w){
    Vector u = P-Q;
    double t= Cross(w,u)/Cross(v,w);
    return P+v*t;
}
ld Dot(Vector A,Vector B){
    return A.x*B.x + A.y*B.y;
}
ld Length(Vector A){
    return sqrtl(Dot(A,A));
}
//void Perpendicular(Point A,Point B){
//
//}
bool fl;
Point CircumCircle(Point A,Point B,Point C){
    fl=0;
    Point m1 = (A+B)/2;
    Vector v1 = (A-B);
    swap(v1.x,v1.y);
    v1.y = -v1.y;

    Point m2 = (A+C )/2;
    Vector v2 = (C -A);
    swap(v2.x,v2.y);
    v2.y = -v2.y;

    if(v1.y*v2.x == v1.x * v2.y){
        fl=1;
        return Point(0,0);
    }

    return GetLineIntersection(m1,v1,m2,v2);
}

double DistanceToLine(Point P,Point A,Point B){
    Vector v1=B-A,v2 = P-A;
    return Cross(v1,v2)/Length(v1);
}

bool OnSegment(Point p,Point a1, Point a2){
    return dcmp(Cross(a1-p,a2-p))==0 && dcmp(Dot(a1-p,a2-p))<=0;
}

bool OnLineOutSegment(Point p,Point a1, Point a2){
    return dcmp(Cross(a1-p,a2-p))==0 && dcmp(Dot(a1-p,a2-p))>0;
}

void solve(){
	ans=0;
	scanf("%lld",&n);
    ll mx = -1e18,mn = 0;
	for(int i=1;i<=n;i++){
		scanf("%lld%lld%lld",&X[i],&Y[i],&Z[i]);
        mx = max(mx,Z[i]);
	}
    for(int i=1;i<=n;i++){
        if(Z[i]== mx || Z[i] == mn){
            b.push_back(Point(X[i],Y[i]));
        }
        else{
            a.push_back(Point(X[i],Y[i]));
        }
    }
    map<pii,int> ma;
    for(Point u:a){
        ma[mapa(u.x,u.y)]++;
    }
    vector<Point> m;
        Point x;
        for(auto it=ma.begin();it!=ma.end();it++){
            x.x = it->first.fi;
            x.y = it->first.se;
            m.push_back(x);
            //printf("m add %d,%d\n",(int)x.x,(int)x.y);
        }
    if(m.size()>=3){
        Point m1 = (m[0]+m[1])/2;
        Vector v1 = (m[1]-m[0]);
        swap(v1.x,v1.y);
        v1.y = -v1.y;

        Point m2 = (m[0]+m[2])/2;
        Vector v2 = (m[2]-m[0]);
        swap(v2.x,v2.y);
        v2.y = -v2.y;

        if(v1.y*v2.x == v1.x*v2.y){
            printf("not a penguin\n");
            return;
        }

        Point o = GetLineIntersection(m1,v1,m2,v2);
        //cout << o.x << 
        //printf("3. O(%Lf,%Lf)\n",o.x,o.y);
        ld l = Length(m[0]-o);
        
        for(int i=3;i<m.size();i++){
            //printf("l = %Lf, mi to O length = %Lf,dcmp = %d\n",l,Length(m[i]-o),dcmp(Length(m[i]-o)-l));
            if(0 != dcmp(Length(m[i]-o)-l)){
                printf("not a penguin\n");
                return;
            }

        }
        for(Point u:b){
            if(dcmp(Length(u-o)-l) == 1){
                printf("not a penguin\n");
                return;
            }
        }
        printf("probably\n");
        return;
    }
    else if(m.size()==2){
        Point m1 = (m[0]+m[1])/2;
        Vector v1 = (m[1]-m[0]);
        swap(v1.x,v1.y);
        v1.y = -v1.y;
        vector<ld> to_left,to_right;
        for(Point u:b){
            if(OnSegment(u,m[0],m[1]))continue;
            else if(OnLineOutSegment(u,m[0],m[1])){
                //printf("out segment\n");
                printf("not a penguin\n");
                return;
            }
            Point m3 = CircumCircle(m[0],m[1],u);
            //printf("2. u(%Lf,%Lf),m3 = (%Lf,%Lf)\n",u.x,u.y,m3.x,m3.y);
            if(fl){
                printf("not a penguin\n");
                return;
            }
            ld pos;
            if(m3.x == m1.x){
                if(m3.y == m1.y){
                    pos=0;
                }
                else{
                    pos = (m3.y-m1.y)/v1.y;
                }
            }
            else{
                pos = (m3.x-m1.x)/v1.x;
            }
            //printf("pos=%Lf\n",pos);
            if(dcmp(DistanceToLine(u,m[0],m[1]))>0 ){// on the left, ans <= pos
                
                to_left.push_back(pos);
            }
            else{
                to_right.push_back(pos);
            }
        }
        if(to_left.empty() || to_right.empty()){
            printf("probably\n");
            return;
        }
        sort(to_left.begin(),to_left.end());
        sort(to_right.begin(),to_right.end());
        if(dcmp(to_left[0] - to_right[to_right.size()-1])>=0){
            printf("probably\n");
        }
        else printf("not a penguin\n");
    }
    else if(m.size()==1){
        Point o = m[0];
        vector<ld> angles;
        for(Point u:b){
            Vector a2 = u-o;
            if(a2 == Point(0,0))continue;
            angles.push_back(atan2(a2.x,a2.y));
            angles.push_back(atan2(a2.x,a2.y)+2*pi);
            //printf("angles is %Lf\n",atan2(a2.x,a2.y));
        }
        if(angles.empty()){
            printf("probably\n");
            return;
        }
        sort(angles.begin(),angles.end());
        bool f=0;
        for(int i=0;i<angles.size()-1;i++){
            //printf("angles[%d]=%Lf\n",i,angles[i]);
            if(angles[i+1]-angles[i] >= pi+eps){
                f=1;
            }
        }
        if(f){
            printf("probably\n");
        }
        else printf("not a penguin\n");
    }
    else{
        printf("probably\n");
    }
}
int main(){
    //printf("%lf\n",atan2(0,1));
    //printf("%lf\n",atan2(1,0));
    //printf("%lf\n",atan2(0,-1));
    //printf("%lf\n",atan2(-1,0));
	//int t;
	//cin >> t;
	//for(int i=1;i<=t;i++){
		solve();
	//}
}


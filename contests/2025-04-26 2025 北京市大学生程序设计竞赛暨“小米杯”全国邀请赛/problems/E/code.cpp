#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const ld eps = 1e-10;
const int N=1e5+5,INF=1e9;
ll T,n;



ld A,B,C,a[N],d[N];

int sgn(double x) { return x < -eps ? -1 : x > eps; }

typedef struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}  // 构造函数, 初始值为 0

    // 重载运算符
    // 点 - 点 = 向量(向量AB = B - A)
    Point operator- (const Point &B) const { return Point(x - B.x, y - B.y); }
    
    // 点 + 点 = 点, 点 + 向量 = 向量, 向量 + 向量 = 向量
    Point operator+ (const Point &B) const { return Point(x + B.x, y + B.y); }
    
    // 向量 × 向量 (叉积)
    double operator^ (const Point &B) const { return x * B.y - y * B.x; }
    
    // 向量 · 向量 (点积)
    double operator* (const Point &B) const { return x * B.x + y * B.y; }
    
    // 点 * 数 = 点, 向量 * 数 = 向量
    Point operator* (const double &B) const { return Point(x * B, y * B); }
    
    // 点 / 数 = 点, 向量 / 数 = 向量
    Point operator/ (const double &B) const { return Point(x / B, y / B); }
    
    // 判断大小, 一般用于排序
    bool operator< (const Point &B) const { return x < B.x || (x == B.x && y < B.y); }
    
    // 判断相等, 点 == 点, 向量 == 向量, 一般用于判断和去重
    bool operator== (const Point &B) const { return sgn(x - B.x) == 0 && sgn(y - B.y) == 0; }
    
    // 判断不相等, 点 != 点, 向量 != 向量
    bool operator!= (const Point &B) const { return sgn(x - B.x) || sgn(y - B.y); }
} Vector;
Point p[N];
typedef Point Vector;

double operator* (Vector &A, Vector &B) { return A.x * B.x + A.y * B.y; }

Point projection(Point p,Point a,Point b)
{
	Vector v = b - a,u = p - a;
	return a + v * ((v*u) / (v*v));	//dot是两向量的点积
}

ld dist(Point p,ld a,ld b,ld c){
    return fabs(((a * p.x + b * p.y + c) / sqrt(a*a + b*b)));
}

ld euc(Point a,Point b){
    return sqrt(pow(a.x-b.x,2)+pow(a.y-b.y,2));
}

bool check(ld x){
    ld le=-1e9,ri=1e9;
    for(int i=1;i<=n;i++){
        if(sgn(x-d[i])<0)return false;
        ri = min(ri,a[i]+sqrt(x*x-d[i]*d[i]));
        le = max(le,a[i]-sqrt(x*x-d[i]*d[i]));
    }
    if(sgn(ri-le)>0){
        return 1;
    }
    else{
        return 0;
    }
}

void solve(){
    cin >> n;
    ld x,y;
    for(int i=1;i<=n;i++){
        scanf("%LF%LF",&x,&y);
        p[i]=Point(x,y);
    }
    scanf("%LF%LF%LF",&A,&B,&C);
    Point O,P;
    if(sgn(A)==0){
        O.y = -C/B;
        O.x=0;
    }
    else{
        O.x=-C/A;
        O.y=0;
    }
    P = O+Point(-B,A);
    //printf("O(%.5lf,%.5lf),P(%.5lf,%.5lf)\n",O.x,O.y,P.x,P.y);
    for(int i=1;i<=n;i++){
        d[i] = dist(p[i],A,B,C);
        Point H = projection(p[i],O,P);
        a[i] = euc(H,O);
        if(sgn((P-O)*(H-O))<0){
            a[i]=-a[i];
        }
        //printf("a[%d]=%.5LF,d[%d]=%.5LF\n",i,a[i],i,d[i]);
    }
    ld le=0,ri=1e9,mi=(le+ri)/2.0;
    while(sgn(ri-le)>0){
        if(check(mi)){
            ri = mi;
        }
        else{
            le = mi;
        }
        mi=(le+ri)/2.0;
    }
    printf("%.10LF\n",mi);
}

signed main(){
    cin >> T;
    while(T--){
        solve();
    }
}

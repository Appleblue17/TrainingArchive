#include<bits/stdc++.h>
using namespace std;
const int N=1000010;
struct Point{
    double x,y;
    Point(double x=0,double y=0):x(x),y(y){}
};
double pi = acos(-1);
typedef Point Vector;
Vector operator - (const Point& A,const Point& B){
    return Vector(A.x-B.x,A.y-B.y);
}
Vector operator + (const Point& A,const Point& B){
    return Vector(A.x+B.x,A.y+B.y);
}
double dist(Vector A){
    return sqrt(A.x*A.x+A.y*A.y);
}
Point solve2(Point A,Point B){
    
    Vector d = B-A;
    //printf("D length=%.9lf\n",dist(d));
    Point M = Point((A.x+B.x)/2.0,(A.y+B.y)/2.0);
    double dis = sqrt(d.x*d.x+d.y*d.y)/2.0;
    double h = sqrt(1-dis*dis);
    Vector H = Vector(d.y/2.0/dis*h,-d.x/2.0/dis*h);
    Point p = M+H;
    //printf("dist = %.9f,%.9f\n",dist(p-A),dist(p-B));
    return M+H;
}
Vector Rotate(Vector A,double rad){
    return Vector(A.x*cos(rad)-A.y*sin(rad),A.x*sin(rad)+A.y*cos(rad));
}
void solve(){
    int st=0,ed=0,dis=0;
    int f=0;
    scanf("%d%d",&st,&ed);
    Point s,s1,s2,t;
    if(abs(st-ed) > 180){
        dis = 360 - abs(st-ed);
        if(ed > st)f = -1;
        else f = 1;
    }
    else{
        dis = abs(st-ed);
        if(st < ed)f = 1;
        else f = -1;
    }
    //printf("st = %d,dis=%d,f=%d\n",st,dis,f);
    s.x = cos(pi*st/180.0);
    s.y = sin(pi*st/180.0);
    t.x = cos(pi*ed/180.0);
    t.y = sin(pi*ed/180.0);
    if(dis == 0){
        printf("0\n");
        printf("%.9f %.9f\n",s.x,s.y);
        return;
    }
    else if(dis <= 90){
        Point B;
        if(f == 1)B = solve2(s,t);
        else B = solve2(t,s);
        printf("2\n");
        printf("%.9f %.9f\n",s.x,s.y);
        printf("%.9f %.9f\n",B.x,B.y);
        printf("%.9f %.9f\n",t.x,t.y);
        return;
    }
    else if(dis <= 131){
        Vector av,bv;
        double le=0,ri=2,mi=(le+ri)/2;
        while(ri-le >= 1e-9){
            double M = pi-mi*2;
            if(f==1)av = Rotate(s,M);
            else av = Rotate(s,-M);
            if(f == 1)bv = Rotate(t,-M);
            else bv = Rotate(t,M);
            Point A = s+av,B=t+bv;
            double di = dist(A-B);
            //printf("mi=%.6lf,di=%.6lf\n",mi,di);
            //double a = mi*2+2*asin(1/4.0/cos(mi));
            //printf("a=%.9lf\n",a);
            //if(a-dis*pi/180.0>=0)ri = mi;
            if(di >= 1)ri = mi;
            else le = mi;
            mi = (le+ri)/2.0;
        }
        //printf("mi=%.9f\n",mi);
        mi = pi - mi*2;
        if(f==1)av = Rotate(s,mi);
        else av = Rotate(s,-mi);
        if(f == 1)bv = Rotate(t,-mi);
        else bv = Rotate(t,mi);
        //printf("av = %.9lf,%.9lf,bv = %.9lf,%.9lf\n",av.x,av.y,bv.x,bv.y);
        Point A = s+av,B=t+bv;
        //cout << dist(A-B) << endl;
        //cout << dist(A-s) << endl;
        //cout << dist(B-t) << endl;
        printf("3\n");
        printf("%.9f %.9f\n",s.x,s.y);
        printf("%.9f %.9f\n",A.x,A.y);
        printf("%.9f %.9f\n",B.x,B.y);
        printf("%.9f %.9f\n",t.x,t.y);
        return;
    }
    else{
        Vector v = Point(-s.y,s.x);
        if(f == -1){
            v = Point(s.y,-s.x);
        }
        Point s1 = s + v;
        Vector v2 = Point(-s.x,-s.y);
        Point s2 = s1 + v2;
        Point b;
        if(f == 1)b = solve2(s2,t);
        else b = solve2(t,s2);
        printf("4\n");
        printf("%.9f %.9f\n",s.x,s.y);
        printf("%.9f %.9f\n",s1.x,s1.y);
        printf("%.9f %.9f\n",s2.x,s2.y);
        printf("%.9f %.9f\n",b.x,b.y);
        printf("%.9f %.9f\n",t.x,t.y);
    }
}
int main(){
    int T=0;
    scanf("%d",&T);
    while(T--){
        solve();
    }
}


#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

struct Point {
  ll x, y;
  Point(ll x=0, ll y=0):x(x),y(y) { }
};



typedef Point Vector;

Vector operator - (const Point& A, const Point& B) {
  return Vector(A.x-B.x, A.y-B.y);
}

ll Cross(const Vector& A, const Vector& B) {
  return A.x*B.y - A.y*B.x;
}

const double eps = 1e-9;

int dcmp(double x) {
  if(fabs(x) < eps) return 0; else return x < 0 ? -1 : 1;
}

ll Dist2(const Point& A, const Point& B) {
  return (A.x-B.x)*(A.x-B.x) + (A.y-B.y)*(A.y-B.y);
}

bool operator < (const Point& p1, const Point& p2) {
  return p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y);
}

bool operator == (const Point& p1, const Point& p2) {
  return p1.x == p2.x && p1.y == p2.y;
}

bool cmp(Point a,Point b){
    if(a.x == b.x)return a.y < b.y;
    else return a.x < b.x;
}

// 点集凸包
// 如果不希望在凸包的边上有输入点，把两个 <= 改成 <
// 注意：输入点集会被修改
vector<Point> ConvexHull(vector<Point>& p) {
  // 预处理，删除重复点
  sort(p.begin(), p.end());
  p.erase(unique(p.begin(), p.end()), p.end());

  int n = p.size();
  int m = 0;
  vector<Point> ch(n+1);
  for(int i = 0; i < n; i++) {
    while(m > 1 && Cross(ch[m-1]-ch[m-2], p[i]-ch[m-2]) <= 0) m--;
    ch[m++] = p[i];
  }
  int k = m;
  for(int i = n-2; i >= 0; i--) {
    while(m > k && Cross(ch[m-1]-ch[m-2], p[i]-ch[m-2]) <= 0) m--;
    ch[m++] = p[i];
  }
  if(n > 1) m--;
  ch.resize(m);
  return ch;
}

ll Dot(Vector A, Vector B) { return A.x*B.x + A.y*B.y; }
double Length(Vector A) { return sqrt(Dot(A, A)); }

double DistanceToLine(Point P, Point A, Point B) {
  Vector v1 = B - A, v2 = P - A;
  return Cross(v1, v2) / Length(v1);
}

vector<Point> a;
Point n1,n2;
ll f[200010]; 
ll ans=0;
ll op=0;
void solve(){
    for(int i=0;i<a.size();i++){
        //printf("a[%d]=%d,%d\n",i,a[i].x,a[i].y);
        f[i]=0;
    }
    f[0]=1000000;
    for(int i=1;i<a.size();i++){
        f[i]=f[i-1]+1000000;
        int le=0,ri=i,mi=(le+ri)/2;
        while(le<ri){
            Point u = a[mi];
            Point D;
            D.x = max(u.x,a[i].x);
            D.y = max(u.y,a[i].y);
            if(dcmp(DistanceToLine(D,n1,n2))>0){
                le = mi+1;
            }
            else{
                ri = mi;
            }
            mi = (le+ri)/2;
        }
        if(mi == 0)f[i] = min(f[i],1000001ll);
        else f[i] = min(f[i],f[mi-1]+1000001);
        //printf("i=%d,mi=%d\n",i,mi);
    }
    //cout << f[a.size()-1] << endl;
    ans += f[a.size()-1]/1000000;
    op += f[a.size()-1]%1000000;
}

int main()
{
    //freopen("0in.txt","r",stdin);
    int n;
    scanf("%d", &n);
    vector<Point> p,d,c,c2;
    for(int i = 0; i < n; i++) {
        int x, y, w;
        scanf("%d%d", &x, &y);
        p.push_back(Point(x, y));
    }
    sort(p.begin(),p.end(),cmp);
    for(int i=0;i<n;i++){
        Point t;
        if(!d.empty())t = d[d.size()-1];
        else{
            d.push_back(p[i]);
            continue;
        }
        while(t.x <= p[i].x && t.y <= p[i].y){
            d.pop_back();
            if(!d.empty())t = d[d.size()-1];
            else break;
        }
        d.push_back(p[i]);
    }
    if(n == 1){
        printf("1\n0\n");
        return 0;
    }
    Point A = p[0];
    Point B = p[1];

    /*else if(n == 2){
        printf("%d\n",d.size());
        return;
    }*/
    for(int i=0;i<d.size();i++){
        //printf("d[%d]=%lld,%lld\n",i,d[i].x,d[i].y);
    }
    c = ConvexHull(p);
    if(c.size()<=2){
        Vector t = B-A;
        if(t.x == 0 || t.y == 0){
            printf("1\n0\n");
            return 0;
        }
        if((t.x < 0) ^ (t.y > 0)){
            printf("1\n0\n");
        }
        else{
            printf("%d\n0\n",n);
        }
        return 0;
    }
    bool F=0;
    for(int i=0;i<c.size();i++){
        //printf("c[%d]=%lld,%lld\n",i,c[i].x,c[i].y);
        Vector t = c[(i+1)%c.size()]-c[i];
        if(t.x < 0 && t.y > 0){
            if(!F){
                c2.push_back(c[i]);
                c2.push_back(c[(i+1)%c.size()]);
                F=1;
            }
            else{
                c2.push_back(c[(i+1)%c.size()]);
            }
        }
    }
    
    sort(c2.begin(),c2.end(),cmp);
    for(int i=0;i<c2.size();i++){
        //printf("c2[%d]=%lld,%lld\n",i,c2[i].x,c2[i].y);
    }
    //fflush(stdout);
    int j=1,sz=0;
    //assert(c2.size()>=2);
    ans = c2.size();
    for(int i=0;i<c2.size()-1;i++){
        Point u = d[j];
        Point D=d[j];
        sz=1;
        n1 = c2[i];
        n2 = c2[i+1];
        if(u == c2[i+1]){
            j++;
            continue;
        }
        a.clear();
        while(!(u == c2[i+1])){
            a.push_back(u);
            j++;
            u = d[j];
        }
        solve();
        j++;
    }
    printf("%d\n%d\n",ans,op);
}

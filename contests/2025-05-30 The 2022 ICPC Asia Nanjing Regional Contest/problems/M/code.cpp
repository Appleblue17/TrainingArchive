#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int T, n;
int a[N], b[N], sum[N];

struct Point{
    int x,y;
    Point(int x=0, int y=0):x(x),y(y){}
} p[N];

typedef Point Vector;

int Dot(const Vector &A,const Vector& B){
    return A.x*B.x +A.y*B.y;
}

int Cross(const Vector& A,const Vector& B){
    return A.x*B.y - A.y*B.x;
}

Vector operator- (const Point& A, const Point& B){
    return Vector(A.x-B.x,A.y-B.y);
}

int main(){
    int n;
    int ans=0;
    cin >> n;
    for(int i=1;i<=n;i++){
        int x,y;
        scanf("%d%d",&x,&y);
        p[i].x = x;
        p[i].y = y;
    }
    for(int i=1;i<=n;i++){
        p[i+n]=p[i];
    }
    p[n*2+1]=p[1];
    p[n*2+2]=p[2];
    int st=1;
    for(st=1;st<=n;st++){
        Vector a = p[st+1]-p[st];
        if(Dot(a,Vector(0,-1))!=0){
            break;
        }
    }
    for(int i=st;i<=n+st-1;i++){
        Vector a = p[i+1]-p[i];
        Vector b = p[i+2]-p[i+1];
        //printf("i=%d,a=(%d,%d),b=(%d,%d)\n",i,a.x,a.y,b.x,b.y);
        if(Dot(b,Vector(0,-1))==0){
            int j = i+2;
            Vector c = p[j+1]-p[j];
            while(Dot(c,Vector(0,-1))==0){
                j++;
                c = p[j+1]-p[j];
            }
            i = j-1;
            //printf("j=%d,c=(%d,%d)\n",j,c.x,c.y);
            if(Dot(a,Vector(0,-1))>0 && Dot(c,Vector(0,-1))<0 && Dot(b,Vector(1,0)) > 0){
                ans++;
                //printf("ans horizontal\n");
            }
            continue;
        }
        if(Dot(a,Vector(0,-1))>0 && Dot(b,Vector(0,-1))<0 && Cross(a,b)>0){
            ans++;
            //printf("ans=%d\n",ans);
        }
        
    }
    printf("%d\n",ans);
}

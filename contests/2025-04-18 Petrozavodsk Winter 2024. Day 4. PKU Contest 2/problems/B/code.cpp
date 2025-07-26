#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,Q;
struct Point{
    ll x,y;
    Point(ll a=0,ll b=0){
        x=a;y=b;
    }
} p[210000];
typedef Point Vector;

const long double eps = 1e-10;

int dcmp(long double x) { return fabs(x) < eps ? 0 : (x < 0 ? -1 : 1); }  

ll norm(Vector x) {return x.x*x.x+x.y*x.y;}

ll cross(Vector a,Vector b){
    return a.x*b.y - b.x*a.y;
}

ll dot(Vector a,Vector b){
    return a.x*b.x+a.y*b.y;
}

Vector operator -(Point a,Point b){
    return Point(a.x-b.x,a.y-b.y);
}

Vector operator *(Point a,ll p){
    return Point(a.x*p,a.y*p);
}

int GetLineDirection(Point p,Vector v,Point u){
    if(cross(v,u-p) < 0)return -1;
    else if(cross(v,u-p)==0)return 0;
    else return 1;
}
set<int> idx;

void solve_std(ll x,ll y){
    Vector P;
	P.x=x;P.y=y;
	int siz1=0,siz2=0;
	for(int i=1;i<=n;i++) siz1+=abs(cross(p[i+1]-P,p[i]-P));
	for(int i=2;i+1<=n;i++) siz2+=abs(cross(p[i+1]-p[1],p[i]-p[1]));
	// printf("%d %d\n",siz1,siz2);
	if(siz1==siz2)
	{
		int ans=0,j=1;
		for(int i=1;i<=n;i++)
		{
			while(i==j||cross(p[i]-P,p[j]-P)>0) j++;
			// printf("%d %d %d\n",i,j,cross(a[i]-P,a[j]-P));
			if(cross(p[i]-P,p[j]-P)==0) ans++;
		}
		printf("%d\n",ans/2);
	}
	else
	{
		int l=1,r=1;
		for(int i=2;i<=n;i++)
		{
			if(cross(P-p[l],P-p[i])>0 || (cross(P-p[l],P-p[i])==0&&norm(P-p[i])>norm(P-p[l]))) l=i;
			if(cross(P-p[r],P-p[i])<0 || (cross(P-p[r],P-p[i])==0&&norm(P-p[i])>norm(P-p[r]))) r=i;
		}
		swap(l,r);
		// printf("%d %d\n",l,r);
		int cl=l,cr=l-1+n,ans=0;
		if((r+1)%n==l%n) {}
		else
		{
			while(1)
			{
				if(cross(P-p[cl],P-p[cr])==0) ans++;
				// printf("* %d %d\n",cl,cr);
				if(cl%n==r%n&&cr%n==(r+1)%n) break;
				if(cl%n==r%n) cr--;
				else if(cr%n==(r+1)%n) cl++;
				else
				{
					if(cross(P-p[cl],P-p[cr])>0) cl++;
					else cr--;
				}
			}
		}
		printf("%d\n",ans);
	}
}

void bs_ddn(ll x1,ll y1,ll x2,ll y2,ll ax,ll ay){
    int le=ax,ri=ay;//,mi=(ax+((ay-ax+n)%n/2)-1)%n+1;
    int mi=(le+ri)/2;
    ll o = cross(Point(x2-x1,y2-y1),Point(x1,y1)-p[ax]);
    if(o==0){
        idx.insert(ax);
        return;
    }
    while(le <= ri){
        ll tw = cross(Point(x2-x1,y2-y1),Point(x1,y1)-p[mi]);
        if(tw==0){
            idx.insert(mi);
            return;
        }
        else if((o<0)==(tw<0)){
            le = mi+1;
        }
        else{
            ri = mi-1;
        }
        mi=(le+ri)/2;
    }
}

int GetConvexIntersection(ll x1,ll y1,ll x2,ll y2){
    idx.clear();
    Point ed = Point(x2,y2);
    Point st = Point(x1,y1);
    Vector v = ed - st;
    ll t = v.y;v.y = v.x;v.x=-t;
    ll orig=1;
    while(dot(v,p[orig+1]-p[orig])==0){
        orig++;
    }
    ll c1=orig;
    if(dot(p[c1+1]-p[c1],v)<0) v=v*(-1);
    for(int i=17;i>=0;i--){
        if(orig+n-1 >= c1+(1<<i)){
            ll tw = c1+(1<<i);
            if(dot(v,p[tw+1]-p[tw])>0&&dot(v,p[tw]-p[c1])>=0) c1+=(1<<i);
        }
    }
    c1 = c1%n+1;
    ll c2=c1;
    v= v*(-1);

    for(int i=17;i>=0;i--)
		{
		if(c2+(1<<i)<=c1+n-1)
		{
			int tw=c2+(1<<i);
			if(dot(v,p[tw+1]-p[tw])>0&&dot(v,p[tw]-p[c2])>=0) c2+=(1<<i);
		}
	}
	c2++;
    
    //printf("c=%d,%d\n",c1,c2);

    int ans=0;

    bs_ddn(x1,y1,x2,y2,c1+1,c2);
    bs_ddn(x1,y1,x2,y2,c2+1,c1+n);

    for(set<int>::iterator it=idx.begin();it!=idx.end();it++){
        
        if(GetLineDirection(Point(x1,y1),Point(x2-x1,y2-y1),p[*it])==0){
            //printf("%d passed, cross = %lld\n",*it,cross(Point(x2-x1,y2-y1),Point(x1,y1)-p[*it]));
            ans++;
        }
    }
    return ans;
}

int main(){
    scanf("%lld%lld",&n,&Q);
    for(int i=1;i<=n;i++){
        int x,y;
        scanf("%d%d",&x,&y);
        p[i+n] = p[i] = Point(x,y);
    }
    p[0]=p[n];
    
    //for(int i=1;i<=n;i++){
        //printf("q[%d].ang = %.5lf\n",i,q[i].ang);
    //}
    
    for(int i=1;i<=Q;i++){
        int typ,x1,y1,x2,y2;
        scanf("%d%d%d",&typ,&x1,&y1);
        if(typ == 1){
            solve_std(x1,y1);
        }
        else{
            scanf("%d%d",&x2,&y2);
            printf("%d\n",GetConvexIntersection(x1,y1,x2,y2));
        }
    }
}

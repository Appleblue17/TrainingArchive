#include<bits/stdc++.h>
using namespace std;
const int N=305;
int n;
const int inf=1e9;
char s[N];
int tim[N][10], pen[N][10];
int p[10];
struct node{
    int a[10], cnt, sum;
    inline bool operator <(const node &t)const{
        if(cnt!=t.cnt) return cnt>t.cnt;
        if(sum!=t.sum) return sum<t.sum;
        for(int i=0; i<10; ++i) if(a[i]!=t.a[i]){
            return a[i]<t.a[i];
        }
        return false;
    }
}b[N];
int mn[10], global_mn, global_mx;
int main(){
    scanf("%d", &n); getchar();
    for(int i=1; i<=n; ++i){
        scanf("%[^\n]", s+1); getchar();
        int len=strlen(s+1);
        int c=0;
        for(int l=1, r; l<=len; ){
            r=l;
            while(r+1<=len&&s[r+1]!=',') ++r;
            if(r-l+1==1){
                tim[i][c]=-1;
            }
            else{
                int c1=0, c2=0;
                while(s[l]!=' ') c1*=10, c1+=s[l]-'0', ++l;
                ++l;
                while(l<=r) c2*=10, c2+=s[l]-'0', ++l;
                tim[i][c]=c1; pen[i][c]=c2;
            }
            b[i].a[c]=tim[i][c];
            if(tim[i][c]!=-1) b[i].sum+=b[i].a[c]+pen[i][c]*20, b[i].cnt++;
            l=r+2;
            ++c;
        }
        sort(b[i].a, b[i].a+10, greater<int>());
    }
    global_mn=inf;
    for(int i=0; i<10; ++i) mn[i]=inf;
    for(int i=1; i<n; ++i){
        for(int j=0; j<10; ++j) if(tim[i][j]!=-1) {
            global_mx=max(global_mx, tim[i][j]);
            global_mn=min(global_mn, tim[i][j]);
            mn[j]=min(mn[j], tim[i][j]);
        }
    }
    sort(b+1, b+n);
    /*
    for(int i=1; i<n; ++i){
        for(int j=0; j<10; ++j) cout<<b[i].a[j]<<' ';
        cout<<endl;
        cout<<b[i].cnt<<' '<<b[i].sum<<endl;
    }
    */
    for(int i=0; i<10; ++i) p[i]=i;
    int mx_sc=0;
    do{
        int pre=0;
        for(int i=0; i<10; ++i) {
            if(tim[n][p[i]]==-1) b[n].a[p[i]]=-1;
            else pre+=tim[n][p[i]], b[n].a[p[i]]=pre;
        }
        b[n].sum=b[n].cnt=0;
        for(int i=0; i<10; ++i) {
            if(b[n].a[i]>300||b[n].a[i]==-1) {
                b[n].a[i]=-1;
            }
            else{
                b[n].cnt++;
                b[n].sum+=b[n].a[i]+pen[n][i]*20;
            }
        }
        // cout<<b[n].cnt<<' '<<b[n].sum<<endl;
        int cur_sc=0;
        //shou sha
        int curmn=inf, curmx=0;
        for(int i=0; i<10; ++i) if(b[n].a[i]!=-1){
            if(b[n].a[i]<=mn[i]) cur_sc+=800;
            curmn=min(curmn, b[n].a[i]);
            curmx=max(curmx, b[n].a[i]);
        }
        //quan ju shou sha
        if(curmn!=inf&&curmn<=global_mn) cur_sc+=700;
        //zui jia pin bo
        if(curmx!=0&&curmx>=global_mx) cur_sc+=500;
        //rank
        sort(b[n].a, b[n].a+10, greater<int>());
        int lp=1, rp=n-1, mid, ret=0;
        while(lp<=rp){
            mid=(lp+rp)>>1;
            if(b[mid]<b[n]){
                ret=mid; lp=mid+1;
            }
            else{
                rp=mid-1;
            }
        }
        ++ret;
        if(ret<=n/10) cur_sc+=1200;
        else if(ret<=3*(n/10)) cur_sc+=800;
        else if(ret<=6*(n/10)) cur_sc+=400;
        cur_sc+=5000/ret;
        mx_sc=max(mx_sc, cur_sc);
    }while(next_permutation(p, p+10));
    printf("%d\n", mx_sc);
}

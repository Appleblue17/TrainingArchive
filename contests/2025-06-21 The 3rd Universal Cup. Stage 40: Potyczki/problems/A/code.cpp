#include <bits/stdc++.h>
using namespace std;
const int N=5e5+5;
int T, n;
struct node{
    int id, l, r;
    bool operator <(const node &x)const{
        if(l==x.l) return r>x.r;
        return l<x.l;
    }
}a[N];
int ans[N];
int stk[N], top=0;
vector<int> vec[N];
int idx=0;
int p[N];
bool cmp(int x, int y){
    return vec[x].size()<vec[y].size();
}
void solve(){
    scanf("%d", &n);
    for(int i=1; i<=n; ++i) scanf("%d%d", &a[i].l, &a[i].r), a[i].id=i, ans[i]=1, --a[i].r;
    sort(a+1, a+n+1);
    top=0;
    for(int i=1; i<=n; ++i){
        if(top&&a[stk[top]].r>=a[i].r){
            ans[a[i].id]=0;
            top--;
            continue;
        }
        stk[++top]=i;
    }
    idx=0;
    for(int l=1, r=1; l<=top; l=r+1){
        r=l;
        while(r+1<=top&&a[stk[r+1]].l<=a[stk[r]].r) ++r;
        ++idx; vec[idx].clear(); p[idx]=idx;
        for(int i=l; i<=r; ++i) vec[idx].push_back(stk[i]);
    }
    sort(p+1, p+idx+1, cmp);
    for(int i=2; i<=idx; ++i){
        while(vec[p[i]].size()&&vec[p[i-1]].size()){
            ans[a[vec[p[i]].back()].id]=0;
            ans[a[vec[p[i-1]].back()].id]=0;
            vec[p[i]].pop_back();
            vec[p[i-1]].pop_back();
        }
    }
    int l=0, r=vec[p[idx]].size()-1;
    while(l<r){
        if(a[vec[p[idx]][l]].r<a[vec[p[idx]][r]].l){
            ans[a[vec[p[idx]][l]].id]=0;
            ans[a[vec[p[idx]][r]].id]=0;
            ++l; --r;
        }
        else break;
    }
    int c=1;
    while(l<=r){
        ans[a[vec[p[idx]][l]].id]=c;
        ans[a[vec[p[idx]][r]].id]=c;
        ++l; --r; c^=1;
    }
    for(int i=1; i<=n; ++i) putchar("NT"[ans[i]]);
    putchar('\n');
}
int main(){
    scanf("%d", &T);
    while(T--){
        solve();
    }
}
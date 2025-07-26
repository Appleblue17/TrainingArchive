#include<bits/stdc++.h>
using namespace std;
const int N = 1000010;
int t,n,m;
int a[N],b[N],id[N];
bool cmp(int x,int y){
    return a[x] < a[y];
}
void solve(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        scanf("%d%d",&a[i],&b[i]);
        id[i]=i;
    }
    sort(id+1,id+m+1,cmp);
    id[0]=0;
    a[0]=b[0]=0;
    for(int i=1;i<=m;i++){
        if(b[id[i]]-b[id[i-1]] == a[id[i]]-a[id[i-1]] || b[id[i]] < a[id[i]]-a[id[i-1]]){

        }
        else{
            printf("No\n");
            return;
        }
    }
    printf("Yes\n");
}
int main(){
    cin >> t;
    while(t--){
        solve();
    }
}

#pragma GCC optimize(3)
#include<bits/stdc++.h>
using namespace std;
const int N=4e5+5;

int n, m;
unordered_map<int, set<int> > h[2][2];
int ax[2][N], ay[2][N];
const int inf=1000000001;
inline bool check(int i, int o){
    int pa=inf;
    int x=ax[o][i], y=ay[o][i];
    if(h[o][0][x].upper_bound(y)!=h[o][0][x].end()){
        pa=*(h[o][0][x].upper_bound(y));
    }
    int pb=inf;
    if(h[o^1][0][x].upper_bound(y)!=h[o^1][0][x].end()){
        pb=*(h[o^1][0][x].upper_bound(y));
    }
    if(pb<pa) return true;
    
    pa=inf;
    if(h[o][1][y].upper_bound(x)!=h[o][1][y].end()){
        pa=*(h[o][1][y].upper_bound(x));
    }
    pb=inf;
    if(h[o^1][1][y].upper_bound(x)!=h[o^1][1][y].end()){
        pb=*(h[o^1][1][y].upper_bound(x));
    }
    if(pb<pa) return true;
    
    pa=-inf;
    if(h[o][1][y].lower_bound(x)!=h[o][1][y].begin()){
        pa=*(--h[o][1][y].lower_bound(x));
    }
    pb=-inf;
    if(h[o^1][1][y].lower_bound(x)!=h[o^1][1][y].begin()){
        pb=*(--h[o^1][1][y].lower_bound(x));
    }
    if(pb>pa) return true;
    
    pa=-inf;
    if(h[o][0][x].lower_bound(y)!=h[o][0][x].begin()){
        pa=*(--h[o][0][x].lower_bound(y));
    }
    pb=-inf;
    if(h[o^1][0][x].lower_bound(y)!=h[o^1][0][x].begin()){
        pb=*(--h[o^1][0][x].lower_bound(y));
    }
    if(pb>pa) return true;
    
    return false;
}
int main(){
    cin>>n>>m;
    for(int i=1; i<=n; ++i) {
        cin>>ax[0][i]>>ay[0][i];
        h[0][0][ax[0][i]].insert(ay[0][i]);
        h[0][1][ay[0][i]].insert(ax[0][i]);
    }
    for(int i=1; i<=m; ++i) {
        cin>>ax[1][i]>>ay[1][i];
        h[1][0][ax[1][i]].insert(ay[1][i]);
        h[1][1][ay[1][i]].insert(ax[1][i]);
    }
    for(int i=1; i<=n; ++i){
        printf("%d", check(i, 0));
    }
    putchar('\n');
    for(int i=1; i<=m; ++i){
        printf("%d", check(i, 1));
    }
    putchar('\n');
}

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double dou;
typedef pair<int,int> pii;
#define fi first
#define se second
#define mapa make_pair
typedef long double ld;
typedef unsigned long long ull;
#define ep emplace_back
template <typename T>inline void read(T &x){
	x=0;char c=getchar();bool f=0;
	for(;c<'0'||c>'9';c=getchar()) f|=(c=='-');
	for(;c>='0'&&c<='9';c=getchar())
	x=(x<<1)+(x<<3)+(c^48);
	x=(f?-x:x);
}
const int N=1e5+5;
int n, Q, m;
vector<int> g[N];
int f[N][20], dep[N], sz[N];
inline void dfs(int x, int fa){
    f[x][0]=fa; dep[x]=dep[fa]+1;
    for(int i=1; f[x][i-1]; ++i) f[x][i]=f[f[x][i-1]][i-1];
    sz[x]=1;
    for(auto y:g[x]) if(y^fa){
        dfs(y, x);
        sz[x]+=sz[y];
    }
}
inline int lca(int x, int y){
    if(dep[x]>dep[y]) swap(x, y);
    for(int i=19; i>=0; --i) if(dep[f[y][i]]>=dep[x]) y=f[y][i];
    if(x==y) return x;
    for(int i=19; i>=0; --i) if(f[y][i]^f[x][i]) x=f[x][i], y=f[y][i];
    return f[x][0];
}
inline int jmp(int x, int y){
    for(int i=19; i>=0; --i) if(dep[f[x][i]]>dep[y]) x=f[x][i];
    return x;
}
int occ[N];
int s[N];
inline bool check2(int l, int r){
    if(l==r) return true;
    for(int i=l+1; i<=r;){
        if(f[s[i]][0]!=s[l]){
            return false;
        }
        if(!check2(i, min(r, i+sz[s[i]]-1))) return false;
        i=i+sz[s[i]];
    }
    return true;
}
bool clr[N];
vector<int> bin;
inline bool check(int l, int r){
    if(l==r) return true;
    if(f[s[l+1]][0]==s[l]){
        if(!check2(l, min(l+sz[s[l]]-1, r))) return false;
        clr[s[l]]=1; bin.ep(s[l]);
        if(l+sz[s[l]]-1<r){
            s[l+sz[s[l]]-1]=s[l];
            return check(l+sz[s[l]]-1, r);
        }
        else return true;
    }
    else{
        if(sz[s[l]]==1){
            clr[s[l]]=1; bin.ep(s[l]);
        }
        if(!clr[s[l]]) return false;
        if(clr[s[l+1]]) return false;
        int z=lca(s[l], s[l+1]);
        if(f[s[l+1]][0]==z){
            if(!check2(l+1, min(r, l+1+sz[s[l+1]]-1))) return false;
            clr[s[l+1]]=1; clr[jmp(s[l], z)]=1;
            bin.ep(s[l+1]); bin.ep(jmp(s[l], z));
            if(l+1+sz[s[l+1]]-1<r){
                s[l+1+sz[s[l+1]]-1]=s[l+1];
                return check(l+1+sz[s[l+1]]-1, r);
            }
            else return true;
        }
        else return false;
    }
}
int main(){
	// freopen("D:\\nya\\acm\\C\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\C\\test.out","w",stdout);
	read(n); read(Q);
    for(int i=1, x, y; i<n; ++i){
        read(x); read(y);
        g[x].ep(y); g[y].ep(x);
    }
    dfs(1, 0);
    // int _=0;
    while(Q--){
        // ++_;
        read(m);
        int mx=0;
        for(int i=1; i<=m; ++i) read(s[i]), ++occ[s[i]], mx=max(mx, occ[s[i]]);
        // if(_==89){
        //     for(int i=1; i<=m; ++i) cout<<s[i]<<' ';
        //     cout<<endl;
        // }
        for(int i=1; i<=m; ++i) --occ[s[i]];
        // if(n<10){
            if(mx>1) printf("No\n");
            else if(check(1, m)) printf("Yes\n");
            else printf("No\n");
        // }
        for(auto t:bin) clr[t]=0;
        bin.clear();
    }
    return 0;
}


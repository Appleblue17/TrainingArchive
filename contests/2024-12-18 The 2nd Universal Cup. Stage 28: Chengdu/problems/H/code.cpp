#include <bits/stdc++.h>
using namespace std;
const int N=2e6+6;
int Test, n;
int s[N], cnt[N];
typedef pair<int, int> pii;
#define fi first
#define se second
#define mapa make_pair
int main(){
    cin>>Test;
    while(Test--){
        cin>>n;
        for(int i=1; i<=n*2; ++i) cin>>s[i], cnt[s[i]]++;
        bool flag=1;
        for(int i=1; i<=n; ++i) if(s[i]!=s[n*2+1-i]){
            flag=0; break;
        }
        if(flag){
            printf("Qingyu\n");
            for(int i=1; i<=n*2; ++i) cnt[i]=0;
            continue;
        }
        set<pii> s;
        for(int i=1; i<=n*2; ++i) if(cnt[i]!=0) s.insert(mapa(-cnt[i], i));
        int cur=0;
        while(true){
            if((*s.begin()).fi==-1){
                flag=0;
                break;
            }
            if(s.size()==1){
                flag=1;
                break;
            }
            cur^=1;
            if(cur){
                pii v=*s.begin(); s.erase(s.begin());
                if(v.fi!=-1) s.insert(mapa(v.fi+1, v.se));
            }
            else{
                set<pii>::iterator it=s.end(); --it;
                pii v=*it; s.erase(it);
                if(v.fi!=-1) s.insert(mapa(v.fi+1, v.se));
            }
        }
        if(flag){
            printf("Qingyu\n");
        }
        else{
            printf("Kevin\n");
        }
        for(int i=1; i<=n*2; ++i) cnt[i]=0;
    }
}

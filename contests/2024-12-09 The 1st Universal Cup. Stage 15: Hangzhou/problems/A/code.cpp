#include <bits/stdc++.h>
using namespace std;

int n;
int que(int x){
    cout<<"? "<<x<<endl;
    int res; cin>>res;
    return res;
}


int main() {
    cin>>n;
    
    int l=1,r=n;
    int lst=0;
    
    while(l<=r){
        
        if(!lst){
            lst=que(l);
            if(!lst){
                cout<<"! "<<l<<endl;
                return 0;
            }
            else l++;
        }
        
        int mid=(l+r)>>1;
        int tot=que(mid);
        if(tot==lst){
            cout<<"! "<<mid<<endl;
            return 0;
        }
        if(tot>lst) l=mid+1;
        else r=mid-1;
        lst=tot;
    }
    
    
    
}

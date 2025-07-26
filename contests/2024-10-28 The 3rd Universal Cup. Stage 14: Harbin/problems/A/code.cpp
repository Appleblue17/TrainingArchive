#include <bits/stdc++.h>
using namespace std;
const int N=220;
int k=20;

int L,R;
vector < pair<int,int> > ANS[N];
int cnt=1;

void add(int u,int v,int w){
    ANS[u].push_back(make_pair(v,w));
}

int mn=1e9;
int solve(int l,int r,int dep,bool flag){
    if(L<=l && r<=R){
    	mn=min(mn,dep);
    	return -dep;
	}
    int o=0;
    int mid=(l+r)>>1;
    if(flag) o=++cnt;
    if(L<=mid){
        int ls=solve(l,mid,dep+1,flag);
        if(flag) add(o,ls,0);
    }
    if(R>mid){
        int rs=solve(mid+1,r,dep+1,1);
        if(!flag) add(1,rs,1);
		else add(o,rs,1);
    }
    return o;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>L>>R;
    solve(0,(1<<k)-1,1,0);
    
    int del=cnt-(mn-1);
    cnt++;
    for(int i=1;i<=k-(mn-1);i++){
        int u=cnt,v=++cnt;
        add(u,v,0);
        add(u,v,1);
    }
    
    cout<<cnt<<endl;
    for(int i=1;i<=cnt;i++){
//    	cout<<i<<":  ";
        cout<<ANS[i].size()<<" ";
        for(pair<int,int> x: ANS[i]){
        	int val=x.first;
        	if(val<0) val=-val+del;
        	cout<<val<<" "<<x.second<<" ";
		}
        cout<<endl;
    }
}

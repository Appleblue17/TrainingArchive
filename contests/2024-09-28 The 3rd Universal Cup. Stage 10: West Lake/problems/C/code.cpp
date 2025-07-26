#include<bits/stdc++.h>
using namespace std;
// #define int long long
const int N=1100;
int n,a[N],b[N];

int stp;
int ask(){
	stp++;
    cout<<0<<" ";
    for(int i=1;i<=n;i++) cout<<b[i]<<" ";
    cout<<endl;
    int ret=0;
    cin>>ret;
//    for(int i=1;i<=n;i++) ret+=(a[i]==b[i]);
//    cout<<" ret: "<<ret<<endl;
    return ret;
}

mt19937 rng(time(NULL));

int ans[N];

vector <int> TMP[N],NTMP[N];

void solve(vector<int> pos, vector<int> val, int siz, int outside){
	if(siz==1){
		ans[pos[0]]=val[0];
		return ;
	}
	
	shuffle(pos.begin(),pos.end(),rng);
	shuffle(val.begin(),val.end(),rng);
	int mid=siz >> 1;
	//[0,mid-1]
	vector <int> lpos,rpos,lval,rval;
	for(int i=0;i<mid;i++) lpos.push_back(pos[i]);
	for(int i=mid;i<siz;i++) rpos.push_back(pos[i]);
	
	int st=0;
	if(!outside){
		while(!lval.size() && !rval.size()){
			shuffle(val.begin(),val.end(),rng);
			int x=val[0],y=val[1];
			for(int i=1;i<=n;i++) b[i]=val[0];
			for(int i: lpos) b[i]=x;
			for(int i: rpos) b[i]=y;
			int ret=ask();
			if(ret==2){
				lval.push_back(x);
				rval.push_back(y);
			}
			else if(ret==0){
				rval.push_back(x);
				lval.push_back(y);
			}
		}
		st=2;
	}
	int tmp=(outside)?outside:lval[0];
	
    int cnt=0;
    for(int t=st;t<siz;t++){
        cnt++;
        TMP[cnt].clear();
        TMP[cnt].push_back(val[t]);
    }
    
    
    while(cnt){
        int ncnt=0;
        for(int t=1;t<=cnt;t+=2){
            if(t==cnt){
                int x=TMP[t][0];
                for(int i=1;i<=n;i++) b[i]=val[0];
                for(int i: lpos) b[i]=x;
                for(int i: rpos) b[i]=tmp;
                
                int ret=ask();
                if(ret==1){
                    for(int z: TMP[t]) lval.push_back(z);
                }
                else{
                    for(int z: TMP[t]) rval.push_back(z);
                }
                break;
            }
            
            int x=TMP[t][0],y=TMP[t+1][0];
            for(int i=1;i<=n;i++) b[i]=val[0];
            for(int i: lpos) b[i]=x;
            for(int i: rpos) b[i]=y;
            int ret=ask();
            if(ret==2){
                for(int z: TMP[t]) lval.push_back(z);
                for(int z: TMP[t+1]) rval.push_back(z);
            }
            else if(ret==0){
                for(int z: TMP[t]) rval.push_back(z);
                for(int z: TMP[t+1]) lval.push_back(z);
            }
            else{
                ncnt++;
                NTMP[ncnt].clear();
                for(int z: TMP[t]) NTMP[ncnt].push_back(z);
                for(int z: TMP[t+1]) NTMP[ncnt].push_back(z);
            }
        }
        swap(TMP,NTMP);
        swap(cnt,ncnt);
    }
	
	solve(lpos,lval,mid,rval[0]);
	solve(rpos,rval,siz-mid,lval[0]);
}

signed main(){
//	ios::sync_with_stdio(false);
//  cin.tie(0);
	cin>>n;
//	for(int i=1;i<=n;i++) a[i]=i;
//	shuffle(a+2,a+n+1,rng);
//	for(int i=1;i<=n;i++) cout<<a[i]<<" ";
//	cout<<endl;
	
	vector <int> pos,val;
	for(int i=1;i<=n;i++) pos.push_back(i),val.push_back(i);
	solve(pos,val,n,0);
	
	cout<<1<<" ";
	for(int i=1;i<=n;i++) cout<<ans[i]<<" ";
	cout<<endl;
//    for(int i=1;i<=n;i++) assert(ans[i]==a[i]);
//    cout<<"step: "<<stp;
} 

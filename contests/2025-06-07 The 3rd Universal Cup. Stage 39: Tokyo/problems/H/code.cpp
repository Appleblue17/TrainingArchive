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
const int N=1e6+5;
int n, m;
int a[N];
int rs[N];
int main(){
	// freopen("D:\\nya\\acm\\A\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\A\\test.out","w",stdout);
	cin>>n;
	cout<<"? "<<n<<endl;
    int cnt=1;
	for(int i=0; i<n; ++i) cout<<i<<" 1"<<endl;
	cin>>m;
	for(int i=1, x; i<=m; ++i){
		cin>>x;
		a[x]=1; a[x+n]=1;
	}
	if(n==m){
		cout<<"! "<<n<<endl;
		for(int i=0; i<n; ++i) cout<<i<<endl;
		return 0;
	}
	vector<int> vec;
	int mx=1;
	for(int i=n*2-1; i>=0; --i){
		if(a[i]==0) rs[i]=0;
		else rs[i]=rs[i+1]+1;
	}
	for(int i=n-1; i>=0; --i){
		if(rs[i]>mx){
			mx=rs[i];
			vec.clear();
			vec.ep(i);
		}
		else if(rs[i]==mx){
			vec.ep(i);
		}
	}
	do{
        sort(vec.begin(), vec.end());
		if(vec.size()==1||cnt==20){
			cout<<"! "<<(int)vec.size()<<endl;
			for(auto t:vec) cout<<t<<endl;
			return 0;
		}
        ++cnt;
		cout<<"? "<<(int)vec.size()<<endl;
        vector<int> tag;
        for(int i=0; i<(int)vec.size(); ++i) tag.ep(0), tag.ep(0);
        vec.ep(vec[0]+n);
        for(int i=0; i+1<(int)vec.size(); ++i){
            int cur=vec[i+1]-vec[i];
            cout<<vec[i]<<' '<<cur<<endl;
        }
        vec.pop_back();
		int k;
		cin>>k;
		vector<int> vec2;
		for(int i=1, x; i<=k; ++i){
			cin>>x;
			vec2.ep(x);
            tag[x]=1;
            tag[x+vec.size()]=1;
		}
        if(k==vec.size()){
            continue;
        }
        rs[vec.size()*2]=0;
        for(int i=(int)vec.size()*2-1; i>=0; --i){
            if(tag[i]) rs[i]=rs[i+1]+1;
            else rs[i]=0;
        }
        int mx=1;
        vector<int> v3;
        for(auto t:vec2){
            if(rs[t]>mx){
                mx=rs[t];
                v3.clear(); v3.ep(vec[t]);
            }
            else if(rs[t]==mx){
                v3.ep(vec[t]);
            }
        }
        vec.swap(v3);
	}while(true);
	return 0;
}

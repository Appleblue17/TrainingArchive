#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e6+5;
int T, n;
char s[N];
#define success {printf("Yes\n"); return ;}
#define fail {printf("No\n"); return ;}
void solve(){
    scanf("%d", &n);
    scanf("%s", s+1);
    if(s[n]=='0'&&s[n-1]=='0') success
    if(s[n-1]=='1'&&s[n]=='1'){
        int bd=n-3;
        for(int l=1, r=1; l<=bd; ){
            while(l<=bd&&s[l]=='0') ++l, r=l;
            if(l>bd) break;
            while(r+1<=bd&&s[r+1]=='1') ++r;
            int l2=r+1;
			if(l2>bd) break;
            if(s[l2]=='1') break;
            int r2=l2;
            while(r2+1<=bd&&s[r2+1]=='0') ++r2;
            if(r2-l2+1>r-l+1) {
				for(int j=l; j<=l+2*(r-l); j+=2) s[j]='1', s[j+1]='0'; 
                l=r2+1; r=l;
                continue;
            }
			int l3=l+2*(r2-l2+1);
			for(int j=l; j<l3; j+=2) s[j]='1', s[j+1]='0';
			for(int j=l3; j<=r2; ++j) s[j]='1';
			l=l3;
            r=r2;
        }
        if(n>=4&&s[n-3]=='1') success
        if(n>=5&&s[n-2]=='1'&&s[n-4]=='1') success
        fail
    }
    if(s[n-1]=='1'&&s[n]=='0'){
        int bd=n-3;
        for(int l=1, r=1; l<=bd; ){
            while(l<=bd&&s[l]=='0') ++l, r=l;
            if(l>bd) break;
            while(r+1<=bd&&s[r+1]=='1') ++r;
            int l2=r+1;
			if(l2>bd) break;
            if(s[l2]=='1') break;
            int r2=l2;
            while(r2+1<=bd&&s[r2+1]=='0') ++r2;
            if(r2-l2+1>r-l+1) {
				for(int j=l; j<=l+2*(r-l); j+=2) s[j]='1', s[j+1]='0'; 
                l=r2+1; r=l;
                continue;
            }
			int l3=l+2*(r2-l2+1);
			for(int j=l; j<l3; j+=2) s[j]='1', s[j+1]='0';
			for(int j=l3; j<=r2; ++j) s[j]='1';
			l=l3;
            r=r2;
        }
        if(n>=4&&s[n-3]=='1') success
        if(n>=5&&s[n-2]=='1'&&s[n-4]=='1') success
        fail
    }
	if(s[n-1]=='0'&&s[n]=='1'){
		if(s[n-2]=='1'){
			int bd=n-3;
			for(int l=1, r=1; l<=bd; ){
				while(l<=bd&&s[l]=='0') ++l, r=l;
				if(l>bd) break;
				while(r+1<=bd&&s[r+1]=='1') ++r;
				int l2=r+1;
				if(l2>bd) break;
				if(s[l2]=='1') break;
				int r2=l2;
				while(r2+1<=bd&&s[r2+1]=='0') ++r2;
				if(r2-l2+1>r-l+1) {
					for(int j=l; j<=l+2*(r-l); j+=2) s[j]='1', s[j+1]='0'; 
                	l=r2+1; r=l;
					continue;
				}
				int l3=l+2*(r2-l2+1);
				for(int j=l; j<l3; j+=2) s[j]='1', s[j+1]='0';
				for(int j=l3; j<=r2; ++j) s[j]='1';
				l=l3;
				r=r2;
			}
			if(n>=4&&s[n-3]=='1') success
        	if(n>=5&&s[n-2]=='1'&&s[n-4]=='1') success
			fail
		}
		else{
			int bd=n-2;
			for(int l=1, r=1; l<=bd; ){
				while(l<=bd&&s[l]=='0') ++l, r=l;
				if(l>bd) break;
				while(r+1<=bd&&s[r+1]=='1') ++r;
				int l2=r+1;
				if(l2>bd) break;
				if(s[l2]=='1') break;
				int r2=l2;
				while(r2+1<=bd&&s[r2+1]=='0') ++r2;
				if(r2-l2+1>r-l+1) {
					for(int j=l; j<=l+2*(r-l); j+=2) s[j]='1', s[j+1]='0'; 
                	l=r2+1; r=l;
					continue;
				}
				int l3=l+2*(r2-l2+1);
				for(int j=l; j<l3; j+=2) s[j]='1', s[j+1]='0';
				for(int j=l3; j<=r2; ++j) s[j]='1';
				l=l3;
				r=r2;
			}
			if(s[n-2]=='1') success
			fail
		}
    }
}
int main(){
	// freopen("D:\\nya\\acm\\B\\test.in","r",stdin);
	// freopen("D:\\nya\\acm\\B\\test.out","w",stdout);
    scanf("%d", &T);
    while(T--){
        solve();
    }
}

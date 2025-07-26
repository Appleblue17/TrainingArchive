#include <bits/stdc++.h>
using namespace std;
const int N=55;

int T,n;
char c[N];
int d[N];

int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        
        for(int i=1;i<=n;i++){
            scanf("\n%c %d",&c[i],&d[i]);
        }
        printf("%d %c\n",2*n-1,c[1]);
        printf("Z %d\n",d[1]);
        for(int i=2;i<=n;i++){
            if(c[i-1]=='S' && c[i]=='W') putchar('R');
            if(c[i-1]=='S' && c[i]=='E') putchar('L');
            
            if(c[i-1]=='N' && c[i]=='W') putchar('L');
            if(c[i-1]=='N' && c[i]=='E') putchar('R');
            
            if(c[i-1]=='W' && c[i]=='N') putchar('R');
            if(c[i-1]=='W' && c[i]=='S') putchar('L');
            
            if(c[i-1]=='E' && c[i]=='N') putchar('L');
            if(c[i-1]=='E' && c[i]=='S') putchar('R');
            
			printf("\n");
            printf("Z %d\n",d[i]);
        }
        
    }
    
}

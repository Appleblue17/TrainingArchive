#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=21000;
char s[N];
int a[N],b[N],c[N],n;
void solve(){
    
    if(!(a[1]&1)){
        for(int i=n;i>=1;i--){
            b[i] = a[i]/2;
            a[i-1]+=10*(a[i]%2);
        }
        if(a[n]==1)n--;
        for(int i=n;i>=1;i--)printf("%c",b[i]+'0');
        putchar('\n');
        for(int i=n;i>=1;i--)printf("%c",b[i]+'0');
        putchar('\n');
        for(int i=n;i>=1;i--)printf("%c",b[i]+'0');
        putchar('\n');
        return;
    }
    if(a[n]!=1){
        int id=1;
        bool f=0;
        for(id=1;id<=n;id++){
            if(a[id]!=9){
                f=1;
                break;
            }
        }
        if(!f){
            for(int i=n;i>=1;i--){
                if((n-i)&1)printf("0");
                else printf("9");
            }
            putchar('\n');
            for(int i=n-1;i>=1;i--){
                if((n-1-i)&1)printf("0");
                else printf("9");
            }
            putchar('\n');
            for(int i=n-1;i>=1;i--){
                if((n-1-i)&1)printf("0");
                else printf("9");
            }
            putchar('\n');
            return;
        }
        
        if(a[id+1]&1){
            a[id+1]--;
            a[id]+=10;
        }
        int i9 = a[id];
        for(int i=n;i>=id+1;i--){
            b[i] = a[i]/2;
            a[i-1]+=10*(a[i]%2);
        }
        //b i9 c
        //b 0 !c
        //b !c
        if(i9<10){
            for(int i=id-1;i>=1;i--){
                if((id-i)&1)c[i] = 9-i9;
                else c[i] = i9;
            }
            for(int i=n;i>=id+1;i--)printf("%c",b[i]+'0');
            printf("%c",i9+'0');
            for(int i=id-1;i>=1;i--)printf("%c",c[i]+'0');
            putchar('\n');
            for(int i=n;i>=id+1;i--)printf("%c",b[i]+'0');
            if(id != n)printf("0");
            for(int i=id-1;i>=1;i--)printf("%c",9-c[i]+'0');
            putchar('\n');
            for(int i=n;i>=id+1;i--)printf("%c",b[i]+'0');
            for(int i=id-1;i>=1;i--)printf("%c",9-c[i]+'0');
            putchar('\n');
            return;
        }
        else{
            //b i9-9 c
            //b 9 !c
            //b !c
            // c start with 18-i9,alternate with i9-9
            for(int i=id-1;i>=1;i--){
                if((id-i)&1)c[i] = 18-i9;
                else c[i] = i9-9;
            }
            for(int i=n;i>=id+1;i--)printf("%c",b[i]+'0');
            printf("%c",i9-9+'0');
            for(int i=id-1;i>=1;i--)printf("%c",c[i]+'0');
            putchar('\n');
            for(int i=n;i>=id+1;i--)printf("%c",b[i]+'0');
            printf("9");
            for(int i=id-1;i>=1;i--)printf("%c",9-c[i]+'0');
            putchar('\n');
            for(int i=n;i>=id+1;i--)printf("%c",b[i]+'0');
            for(int i=id-1;i>=1;i--)printf("%c",9-c[i]+'0');
            putchar('\n');
            return;
        }
    }
    else{
        int rem=0;
        for(int i=1;i<=n;i+=2){
            rem += a[i]+a[i+1]*10;
        }
        rem = rem%11;
        //for(int i=1;i<=n;i++){
        //    rem = (rem*10+a[i])
        //}
        if(rem != 10 && a[n-1] >= 1){
            for(int i=n;i>=2;i--){
                if(a[i]<=a[i-1]){
                    b[i-1]=a[i];
                    a[i-1]-=a[i];
                }
                else{
                    b[i-1]=a[i]-1;
                    a[i-1] = (a[i]*10+a[i-1])%11;
                }
            }
            for(int i=n-1;i>=1;i--)printf("%c",b[i]+'0');
            putchar('\n');
            for(int i=n-1;i>=1;i--)printf("%c",b[i]+'0');
            printf("%c",rem+'0');
            putchar('\n');
            for(int i=n-1;i>=1;i--)printf("%c",b[i]+'0');
            putchar('\n');
        }
        else{
            a[n-1]+=10;
            a[n]=0;
            n--;
            //printf("nxt");
            solve();
        }
    }
}
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%s",s);
        n=strlen(s);
        for(int i=0;i<=n*2+10;i++)a[i]=0;
        for(int i=1;i<=n;i++){
            a[i]=s[n-i]-'0';
        }
        if(n == 1){
            if(a[1]==1){
                printf("0\n1\n-\n");
                continue;
            }
            if(a[1]==3){
                printf("0\n3\n-\n");
                continue;
            }
            if(a[1]==5){
                printf("0\n5\n-\n");
                continue;
            }
            if(a[1]==7){
                printf("0\n7\n-\n");
                continue;
            }
            if(a[1]==9){
                printf("0\n9\n-\n");
                continue;
            }
        }
        solve();
    }
}

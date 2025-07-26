#include <bits/stdc++.h>
using namespace std;
#define MP make_pair
#define Pii pair<int,int>
const int N=1e5+5,INF=1e9;

int cases,n;
int C[N],P[N],T[N],D[N];
Pii G[N],F[N],H[N];
int p[N];

int ans[N];
vector <string> ANS;

int id;
string team[N];
map <string,int> mp;
char C_[33],P_,D_[33];

vector <int> V[N][26];

Pii operator +(Pii x,Pii y){
    return MP(x.first+y.first,x.second+y.second);
}
Pii operator -(Pii x,Pii y){
    return MP(x.first-y.first,x.second-y.second);
}

void pr(Pii x){
    cout<<x.first<<","<<x.second<<" ";
}

int main(){
    scanf("%d",&cases);
    while(cases--){
        scanf("%d",&n);
        id=0;
        mp.clear();
        for(int i=1;i<=n;i++)
            for(int j=0;j<26;j++)
                V[i][j].clear();
        for(int i=1;i<=n;i++) ans[i]=0;
        ANS.clear();
        
        for(int i=1;i<=n;i++){
            scanf("\n%s %c %d %s",C_,&P_,&T[i],D_);
            string S(C_);
            if(!mp[S]) team[++id]=S,mp[S]=id;
            C[i]=mp[S];
            
            P[i]=P_-'A';
            D[i]=(D_[0]=='a');
            
            V[C[i]][P[i]].push_back(i);
        }
        
        int team_num=0;
        for(int t=1;t<=id;t++){
            Pii TOT=MP(0,0),MN=MP(0,0),MX=MP(0,0);
            bool fl=0;
            for(int j=0;j<26;j++){
                Pii tot=MP(0,0),mn=MP(0,0),mx=MP(0,0);
                int siz=V[t][j].size();
                if(!siz) continue;
                
                int ac_cnt=0;
                int first_ac_i,first_ac=INF;
                int second_ac_i,second_ac=INF;
                for(int k=0;k<siz;k++){
                    int x=V[t][j][k];
                    int t=T[x],d=D[x];
                    if(d){
                        ac_cnt++;
                        if(first_ac==INF) first_ac=t,first_ac_i=k;
                        else if(second_ac==INF) second_ac=t,second_ac_i=k;
                    }
                }
                int first_submit=T[V[t][j][0]];
                
                if(!ac_cnt){
                    mx=MP(1,-first_submit);
                }
                else if(ac_cnt==1){
                    tot=MP(1,-first_ac-20*first_ac_i);
                    mn=MP(0,0);
                    mx=MP(1,-first_submit);
                }
                else{
                    tot=MP(1,-first_ac-20*first_ac_i);
                    mn=MP(1,-second_ac-20*second_ac_i);
                    mx=MP(1,-first_submit);
                }
                
                TOT=TOT+tot;
                MN=min(MN,mn-tot);
                MX=max(MX,mx-tot);
                
                if(ac_cnt) fl=1;
            }
            team_num+=fl;
            
            F[t]=TOT+MN;
            G[t]=TOT;
            H[t]=TOT+MX;
        }
        if(!team_num){
            printf("%d\n",id);
            for(int t=1;t<=id;t++) printf("%s\n",team[t].c_str());
            continue;
        }
        
        for(int t=1;t<=id;t++) p[t]=t;
        sort(p+1,p+id+1,[&](int x,int y){return G[x]>G[y];});
        
        int gold=min(35,(team_num-1)/10+1);
        for(int i=1;i<=gold;i++) ans[p[i]]=1;
        
        if(G[p[gold+1]]<G[p[gold]]){
            Pii mn=MP(INF,INF);
            for(int t=1;t<=id;t++){
                if(G[t]>=G[p[gold]]){
                    if(team_num<=350 && team_num%10==1 && F[t]==MP(0,0)) continue;
                    mn=min(mn,F[t]);
                }
            }
            for(int t=1;t<=id;t++){
                if(G[t]==G[p[gold+1]] && G[t]>=mn) ans[t]=1;
            }
        }
        for(int t=1;t<=id;t++){
            if(H[t]>=G[p[gold]]) ans[t]=1;
        }
        
        if(team_num<=350 && team_num%10==0){
            Pii mn=MP(INF,INF);
            for(int t=1;t<=id;t++){
                if(G[t]==MP(0,0) && H[t]>MP(0,0)){
                    int mx=H[t].second;
                    for(int j=0;j<26;j++){
                        int siz=V[t][j].size();
                        if(siz) mx=max(mx,T[V[t][j][siz-1]]+20*(siz-1));
                    }
                    mn=min(mn,MP(1,-mx));
                    
                    if(H[t]>=G[p[gold+1]]) ans[t]=1;
                }
            }
            
            for(int t=1;t<=id;t++){
                if(G[t]>=G[p[gold+1]] && G[t]>=mn) ans[t]=1;
            }
        }
        
        for(int t=1;t<=id;t++){
            if(ans[t]) ANS.push_back(team[t]);
        }
        
        printf("%d\n",ANS.size());
        for(string str: ANS) printf("%s ",str.c_str());
        printf("\n");
    }
    
}

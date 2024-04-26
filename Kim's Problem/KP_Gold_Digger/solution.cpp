#include<bits/stdc++.h>
using namespace std;
using pii=pair<int,int>;
#define f first
#define s second

using ti3=tuple<int,int,int>;

pii dif[]={
{1,0},
{-1,0},
{0,1},
{0,-1}
};
string s[2005];
int P[1005],val[1005],dp[50005];
bool vis[2005][2005];

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int Q; cin>>Q;
    while(Q--){
        int R,C; cin>>R>>C;
        for(int i=1;i<=R;++i) cin>>s[i];

        queue<ti3> q;
        int n,W; cin>>n>>W;
        for(int i=1;i<=n;++i){
            int a,b; cin>>a>>b>>P[i];
            q.emplace(a,b,i);
            if(s[a][b-1]=='*') ++val[i];
            vis[a][b]=1;
        }
        while(q.size()){
            int a,b,id;
            tie(a,b,id)=q.front();
            q.pop();
            for(int i=0;i<4;++i){
                int a2=a+dif[i].f, b2=b+dif[i].s;
                if(a2>0&&a2<=R&&b2>0&&b2<=C){
                    if(s[a2][b2-1]=='#' || vis[a2][b2]) continue;
                    if(s[a2][b2-1]=='*') ++val[id];
                    vis[a2][b2]=1;
                    q.emplace(a2,b2,id);
                }
            }
        }

        for(int i=1;i<=n;++i){
            for(int j=W;j>=1;--j){
                dp[j]=max(dp[j],dp[j-1]);
                if(P[i]<=j) dp[j]=max(dp[j],dp[j-P[i]]+val[i]);
            }
        }
        cout << dp[W] << '\n';
        for(int i=1;i<=n;++i) val[i]=0;
        for(int i=1;i<=R;++i){
            for(int j=1;j<=C;++j){
                vis[i][j]=0;
            }
        }
        for(int i=1;i<=W;++i) dp[i]=0;
    }

}
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'

int dp[2][25][25];

int32_t main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int Q; cin>>Q;
    while(Q--){
        int n; cin>>n;
        memset(dp,0x3f,sizeof dp);
        dp[0][0][0]=0;
        int ans=INT_MAX;
        for(int i=1;i<=n;++i){
            int x; cin>>x;
            bool now=i&1,prev=!now;
            memset(dp[now],0x3f,sizeof dp[now]);
            for(int j=0;j<=20;++j){
                for(int k=0;k<=20;++k){
                    if(x==k) dp[now][j][x]=min(dp[now][j][x],dp[prev][j][k]),
                             dp[now][x][j]=min(dp[now][x][j],dp[prev][k][j]);
                    else dp[now][j][x]=min(dp[now][j][x],dp[prev][j][k]+1),
                         dp[now][x][j]=min(dp[now][x][j],dp[prev][k][j]+1);
                    if(i==n) ans=min({ans,dp[now][j][x],dp[now][x][j]});
                }
            }
        }
        cout<<ans<<endl;
    }

    return 0;
}

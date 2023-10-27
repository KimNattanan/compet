#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define pii pair<int,int>
#define f first
#define s second
#define pb push_back
#define ll long long

#define int ll

const int md=1e9+7;
const int inf=1e9+7;

int dp[1005][3],dp2[1005][2],dp3[1005][2];
int k[3];

int32_t main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n; cin>>n>>k[0]>>k[1]>>k[2];
    for(int i=1;i<=k[0];++i) dp[i][0]=dp2[i][0]=dp3[i][0]=1;
    for(int i=2;i<=n;++i){
        for(int j=1;j<=k[0]&&i-j>=1;++j){
            dp[i][0]=(dp[i][0]+dp[i-j][2])%md;
            dp2[i][0]=(dp2[i][0]+dp2[i-j][1])%md;
        }
        for(int j=1;j<=k[1]&&i-j>=1;++j){
            dp[i][1]=(dp[i][1]+dp[i-j][0])%md;
            dp3[i][1]=(dp3[i][1]+dp3[i-j][0])%md;
        }
        for(int j=1;j<=k[2]&&i-j>=1;++j){
            dp[i][2]=(dp[i][2]+dp[i-j][0]+dp[i-j][1])%md;
            dp2[i][1]=(dp2[i][1]+dp2[i-j][0])%md;
        }
    }
    cout<<(dp[n][0]+dp[n][1]+dp[n][2]-(dp2[n][0]+dp2[n][1]+dp3[n][1])%md+md)%md;

    return 0;
}
/**

40 20 20 20

*/

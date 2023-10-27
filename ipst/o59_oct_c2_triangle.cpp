#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define ll long long
#define pii pair<int,int>
#define f first
#define s second
#define pb push_back

#define int ll

const int inf=1e9;
const int md=1e9+7;

int dp[105][105];

int32_t main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n,K; cin>>n>>K;
    for(int i=0;i<=100;++i) dp[i][0]=dp[0][i]=1;
    for(int i=1;i<=100;++i){
        for(int j=1;j<=100;++j){
            dp[i][j]=(dp[i-1][j]+dp[i][j-1]-dp[i-1][j-1]+md)%md;
            for(int k=max(1ll,i-K);k<i;++k){
                dp[i][j]=(dp[i][j]+dp[k-1][j-1])%md;
            }
            for(int k=max(1ll,j-K);k<j;++k){
                dp[i][j]=(dp[i][j]+dp[i-1][k-1])%md;
            }
        }
    }
    cout<<(dp[n][n]-1+md)%md<<endl;

    return 0;
}
/**

*/

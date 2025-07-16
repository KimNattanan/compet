#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll=long long;
using pii=pair<int,int>;
#define f first
#define s second
#define pb push_back

const int md=1e9+7;
const int inf=1e9+7;

ll dp[2][205][1005];
int a[205];

int32_t main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n,K; cin>>n>>K;
    for(int i=1;i<=n;++i) cin>>a[i];
    sort(a+1,a+1+n);
    dp[1][0][0]=dp[1][1][0]=1;
    for(int i=1;i<n;++i){
        bool now=i&1,nxt=!now;
        memset(dp[nxt],0,sizeof dp[nxt]);
        for(int j=0;j<=i;++j){
            for(int k=0,v=k+j*(a[i+1]-a[i]);v<=K;++k,++v){
                dp[nxt][j][v]=(dp[nxt][j][v]+dp[now][j][k])%md;
                if(j>0) dp[nxt][j-1][v]=(dp[nxt][j-1][v]+((j*dp[now][j][k])%md))%md;
                dp[nxt][j][v]=(dp[nxt][j][v]+((j*dp[now][j][k])%md))%md;
                dp[nxt][j+1][v]=(dp[nxt][j+1][v]+dp[now][j][k])%md;
            }
        }
    }
    ll ans=0;
    for(int k=0;k<=K;++k) ans=(ans+dp[n&1][0][k])%md;
    cout<<ans<<endl;

    return 0;
}

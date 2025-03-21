/*
	HA_Examination
*/
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const ll md=1e9+7;

ll dp[5050][5050];

int main(){
	ios::sync_with_stdio(false); cin.tie(0);

	int n,m,k; cin>>n>>m>>k;
	dp[0][0]=1;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=k;++j) dp[i][j]=dp[i-1][j-1];
		for(int j=0;j<=k;++j) dp[i][0]=(dp[i][0]+1LL*(m-1)*dp[i-1][j])%md;
	}
	ll ans=0;
	for(int i=0;i<=k;++i) ans=(ans+dp[n][i])%md;
	cout<<ans;

    return 0;
}

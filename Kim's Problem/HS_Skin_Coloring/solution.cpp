/*
	Examination2
*/
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const ll md=1e9+7;

ll dp[1000005][2];

int main(){
	ios::sync_with_stdio(false); cin.tie(0);

	int Q; cin>>Q;
	while(Q--){
		int n,m,k; cin>>n>>m>>k;
		dp[0][0]=1;
		for(int i=1;i<=n;++i){
			dp[i][0]=((dp[i-1][0]+dp[i-1][1])*(m-1))%md;
			dp[i][1]=(dp[i-1][0]+dp[i-1][1])%md;
			if(i>k) dp[i][1]=(dp[i][1]-dp[i-k-1][0]+md)%md;
		}
		cout<<(dp[n][0]+dp[n][1])%md<<'\n';
	}

	return 0;
}
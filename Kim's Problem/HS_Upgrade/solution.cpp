/*
	HS_Upgrade
*/
#include<bits/stdc++.h>
using namespace std;
#define eb emplace_back
using ll=long long;

ll dp[2][1<<16];
int msk[1005][1005];

int main(){
	ios::sync_with_stdio(false); cin.tie(0);

    int r,c,k; cin>>r>>c>>k;
	int K=1<<k;
	memset(dp,0x3f,sizeof dp);
	for(int i=1;i<=r;++i){
		for(int j=1;j<=c;++j){
			string s; cin>>s;
			for(auto &e:s) msk[i][j]|=1<<e-'a';
		}
	}
	for(int i=1;i<=r;++i){
		for(int j=1;j<=c;++j){
			int w; cin>>w;
			dp[(i+j)&1][msk[i][j]]=min(dp[(i+j)&1][msk[i][j]], (ll)w);
		}
	}
	for(int i=K-1;i>0;--i){
		for(int j=1;j<K;j<<=1){
			if(i&j) dp[0][i^j]=min(dp[0][i^j],dp[0][i]),
					dp[1][i^j]=min(dp[1][i^j],dp[1][i]);
		}
	}
	for(int i=1;i<K;++i){
		for(int j=(i-1)&i;j>0;j=(j-1)&i){
			dp[0][i]=min(dp[0][i],dp[0][j]+dp[0][i^j]);
			dp[1][i]=min(dp[1][i],dp[1][j]+dp[1][i^j]);
		}
	}
	cout<<dp[0][K-1]+dp[1][K-1];

	return 0;
}

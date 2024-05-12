/*
	HS_Parabola
*/
#include<bits/stdc++.h>
using namespace std;

const int MXH=1000;

int a[100005],dp[2][MXH+5][MXH+5];

int main(){
	ios::sync_with_stdio(false); cin.tie(0);

    int n,Q; cin>>n>>Q;
	for(int i=1;i<=n;++i) cin>>a[i];

	for(int i=0;i<MXH+5;++i) for(int j=0;j<MXH+5;++j) dp[0][i][j]=dp[1][i][j]=-1e9;
    for(int i=1;i<=n;++i){
		dp[0][a[i]][MXH]=1;
		for(int j=a[i]+1;j<=MXH;++j){
			dp[1][a[i]][j-a[i]]=max(dp[1][a[i]][j-a[i]], dp[1][j][j-a[i]]+1);
			if(dp[0][j][1]>1) dp[1][a[i]][j-a[i]]=max(dp[1][a[i]][j-a[i]], dp[0][j][1]+1);
		}
		for(int j=2;j<=MXH;++j) dp[1][a[i]][j]=max(dp[1][a[i]][j], dp[1][a[i]][j-1]);
		for(int j=1;j<a[i];++j) dp[0][a[i]][a[i]-j]=max(dp[0][a[i]][a[i]-j], dp[0][j][a[i]-j]+1);
		for(int j=MXH-1;j>0;--j) dp[0][a[i]][j]=max(dp[0][a[i]][j], dp[0][a[i]][j+1]);
    }
	
	while(Q--){
		int x; cin>>x;
		cout<<max(0,dp[1][x][MXH])<<'\n';
	}

	return 0;
}

#include<bits/stdc++.h>
using namespace std;

int a[1005],dp[1005][2010];

int main(){
	ios::sync_with_stdio(false); cin.tie(0);

    int n,Q; cin>>n>>Q;
	for(int i=1;i<=n;++i) cin>>a[i];

    for(int i=1;i<=n;++i){
        for(int j=1000;j>0;--j){
            if(j!=a[i]&&dp[j][j-a[i]+1000]) dp[a[i]][j-a[i]+1000]=max(dp[a[i]][j-a[i]+1000],dp[j][j-a[i]+1000]+1);
        }
        dp[a[i]][0]=max(dp[a[i]][0],1);
        for(int j=1;j<2010;++j) dp[a[i]][j]=max(dp[a[i]][j],dp[a[i]][j-1]);
    }
    while(Q--){
        int x; cin>>x;
        cout<<dp[x][2009]<<endl;
    }

	return 0;
}

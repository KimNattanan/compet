#include<bits/stdc++.h>
using namespace std;

const int off=1005;
int a[205], ans[1005], n,Q, dp[205][2010];
bitset<1005> used;
int play(int u,int d,bool ch){ // idx, dif, ch == is first stick
	if(dp[u][d+off] != -1) return dp[u][d+off];
	int mx=0;
	for(int v=u-1;v>=1;--v){
		if(a[v]-a[u]<=d && a[v]!=a[u] && (!ch||a[v]-a[u]>0)) mx=max(mx,play(v, a[v]-a[u], 0));
	}
	if(mx==0 && d>=0) return dp[u][d+off]=0;
	return dp[u][d+off]=mx+1;
}
int main(){
	ios::sync_with_stdio(false); cin.tie(0);
	cin>>n>>Q;
	memset(dp,-1,sizeof dp);
	for(int i=1;i<=n;++i) cin >> a[i];
	for(int i=1;i<=n;++i) ans[a[i]] = max(ans[a[i]], play(i,1000,1) );
	while(Q--){
		int x; cin>>x;
		cout << ans[x] << '\n';
	}
}

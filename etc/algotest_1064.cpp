#include<bits/stdc++.h>
using namespace std;
using ll=long long;
#define eb emplace_back

int main(){
	ios::sync_with_stdio(false); cin.tie(0);

	int n,m; cin>>n>>m;
	vector<vector<ll>> a(max(n,m)+5,vector<ll>(min(n,m)+5));
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			if(n>m) cin>>a[i][j], a[i][j]+=a[i-1][j]+a[i][j-1]-a[i-1][j-1];
			else cin>>a[j][i], a[j][i]+=a[j-1][i]+a[j][i-1]-a[j-1][i-1];
		}
	}
	if(n<=m) swap(n,m);
	ll L,R; cin>>L>>R;
	--L;
	ll ans=0;
	for(int j=1;j<=m;++j){
		for(int k=0;k<j;++k){
			int iR=0,iL=0;
			for(int i=1;i<=n;++i){
				while(iL<i && a[i][j]-a[i][k]-a[iL][j]+a[iL][k]>L) ++iL;
				while(iR<i && a[i][j]-a[i][k]-a[iR][j]+a[iR][k]>R) ++iR;
				ans+=iL-iR;
			}
		}
	}
	cout<<ans;

	return 0;
}

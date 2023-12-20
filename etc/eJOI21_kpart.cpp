#include<bits/stdc++.h>
using namespace std;
#define eb emplace_back
 
const int MX=50000;
 
int a[1005],qs[1005];
int dp[MX+5];
 
void solve(){
	int n; cin>>n;
	bool z=0;
	for(int i=1;i<=n;++i){
		cin>>a[i];
		qs[i]=a[i]+qs[i-1];
		if(a[i]>MX) z=1;
	}
	if(z){
		cout<<0<<endl;
		return;
	}
	for(int i=0;i<=MX;++i) dp[i]=0;
	vector<bool> ok(n+5,1);
	for(int i=1;i<=n;++i){
		for(int j=MX-a[i];j>=1;--j) if(dp[j]) dp[j+a[i]]=max(dp[j+a[i]],dp[j]);
		dp[a[i]]=i;
		for(int j=1,k=i;j<i;++j,--k){
			if((qs[i]-qs[j-1])&1) ok[k]=0;
			else if(dp[qs[i]-qs[j-1]>>1]<j) ok[k]=0;
		}
	}
	vector<int> ans;
	for(int i=2;i<=n;++i){
		if(ok[i]) ans.eb(i);
	}
	cout<<ans.size()<<" ";
	for(auto &e:ans) cout<<e<<" ";
	cout<<endl;
 
}
 
int main(){
	ios::sync_with_stdio(false); cin.tie(0);
	
	int Q(1);
	cin>>Q;
	while(Q--){
		solve();
	}
 
	return 0;
}

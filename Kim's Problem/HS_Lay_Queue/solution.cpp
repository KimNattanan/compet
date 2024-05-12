/*
	HS_Lay_Queue
*/
#include<bits/stdc++.h>
using namespace std;
#define eb emplace_back

int a[100005], dp[500005], dpL[500005], dpR[500005];

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int Q; cin>>Q;
	while(Q--){
		int n; cin>>n;
		for(int i=1;i<=n;++i) cin>>a[i];
		int cnt=0;
		for(int i=1;i<=n;++i){
			int id=lower_bound(dp,dp+cnt,a[i]-i)-dp;
			if(id==cnt) ++cnt;
			dp[id]=a[i]-i;
			dpL[i]=cnt;
		}
		cnt=0;
		for(int i=n;i>=1;--i){
			int id=lower_bound(dp,dp+cnt,a[i]-(n-i))-dp;
			if(id==cnt) ++cnt;
			dp[id]=a[i]-(n-i);
			dpR[i]=cnt;
		}
		int ans=max(dpL[n], dpR[1]);
		for(int i=1;i<n;++i) ans=max(ans,dpL[i]+dpR[i+1]);
		cout<<ans<<'\n';
	}

    return 0;
}

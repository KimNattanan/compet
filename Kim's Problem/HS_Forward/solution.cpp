/*
	HS_Forward
*/
#include<bits/stdc++.h>
using namespace std;
#define eb emplace_back
using ll=long long;

vector<int> adj[5005],nds;
ll dp[5005],dp2[5005];
int a[5005],b[5005];

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

	int Q; cin>>Q;
	while(Q--){
		int n,m; cin>>n>>m;
		for(int i=1;i<=n;++i) cin>>a[i];
		for(int i=1;i<=n;++i) cin>>b[i];
		for(int i=1;i<=n;++i) adj[i].clear();
		for(int i=0;i<m;++i){
			int u,v; cin>>u>>v;
			if(b[u]==b[v]) continue;
			if(b[u]<b[v]) swap(u,v);
			adj[u].eb(v);
		}
		nds.resize(n);
		iota(nds.begin(),nds.end(),1);
		sort(nds.begin(),nds.end(),[&](const int &l,const int &r){
			return b[l]<b[r];
		});
		for(int i=1;i<=n;++i) dp2[i]=0;
		for(auto &u:nds){
			dp[0]=0;
			for(int w=1;w<=b[u];++w) dp[w]=-1e18;
			for(auto &v:adj[u]){
				for(int i=b[u];i>=b[v];--i){
					dp[i]=max(dp[i],dp[i-b[v]]+dp2[v]);
				}
			}
			ll mx=0;
			for(int i=0;i<b[u];++i) mx=max(mx,dp[i]+1);
			dp2[u]=mx;
		}
		ll ans=0;
		for(int i=1;i<=n;++i) ans+=dp2[i]*a[i];
		cout<<ans<<'\n';
	}

    return 0;
}
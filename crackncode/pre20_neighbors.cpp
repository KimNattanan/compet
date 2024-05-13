#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using db=double;
using ld=long double;
using pii=pair<int,int>;
#define f first
#define s second
#define eb emplace_back
#define sz(x) (int)(x).size()
 
bool a[100005];
vector<pii> adj[100005];
int ans[100005], dp[100005][3];
 
void dfs(int u,int p){
	if(a[u]) dp[u][0]=u, dp[u][1]=0, dp[u][2]=-1e9;
	else dp[u][0]=-1, dp[u][1]=dp[u][2]=-1e9;
	for(auto &[v,w]:adj[u]){
		if(v==p) continue;
		dfs(v,u);
		if(a[u] || dp[v][0]==-1) continue;
		if(dp[u][1]<dp[v][1]+w) dp[u][2]=dp[u][1], dp[u][1]=dp[v][1]+w, dp[u][0]=v;
		else if(dp[u][2]<dp[v][1]+w) dp[u][2]=dp[v][1]+w;
	}
}
void dfs2(int u,int p,int mx){
	ans[u] = a[u] ? 0 : max(mx,dp[u][1]);
	for(auto &[v,w]:adj[u]){
		if(v==p) continue;
		if(a[u]) dfs2(v,u,w);
		else if(v==dp[u][0]) dfs2(v,u,max(mx,dp[u][2])+w);
		else dfs2(v,u,max(mx,dp[u][1])+w);
	}
}
 
int main(){
	ios::sync_with_stdio(false); cin.tie(0);
 
	int n,Q; cin>>n>>Q;
	for(int i=0;i<n;++i) cin>>a[i];
	for(int i=1;i<n;++i){
		int u,v,w; cin>>u>>v>>w;
		adj[u].eb(v,w), adj[v].eb(u,w);
	}
	dfs(0,0);
	dfs2(0,0,-1e9);
	while(Q--){
		int x; cin>>x;
		cout<<ans[x]<<'\n';
	}
 
	return 0;
}

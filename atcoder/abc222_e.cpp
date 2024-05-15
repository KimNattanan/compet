#include<bits/stdc++.h>
using namespace std;
using ll=long long;
#define eb emplace_back
const ll md=998244353;

int a[105],tour[1005],id1,big[1005],head[1005],p[1005],qs[1005],dp[100005];
vector<int> adj[1005];
int dfs(int u,int p){
	::p[u]=p;
	int sz=1, mx=0;
	for(auto &v:adj[u]){
		if(v==p) continue;
		int szv=dfs(v,u);
		if(szv>mx) big[u]=v, mx=szv;
		sz+=szv;
	}
	return sz;
}
void decomp(int u,int h){
	head[u]=h;
	tour[u]=++id1;
	if(big[u]) decomp(big[u],h);
	for(auto &v:adj[u]){
		if(v!=p[u]&&v!=big[u]) decomp(v,v);
	}
}
void add_hld(int u,int v){
	while(head[u]!=head[v]){
		if(tour[u]>tour[v]) swap(u,v);
		++qs[tour[head[v]]], --qs[tour[v]+1];
		v=p[head[v]];
	}
	if(u==v) return;
	if(tour[u]>tour[v]) swap(u,v);
	++qs[tour[u]+1], --qs[tour[v]+1];
}

int main(){
	ios::sync_with_stdio(false); cin.tie(0);

	int n,m,k; cin>>n>>m>>k;
	for(int i=1;i<=m;++i) cin>>a[i];
	for(int i=1;i<n;++i){
		int u,v; cin>>u>>v;
		adj[u].eb(v), adj[v].eb(u);
	}
	dfs(1,1);
	decomp(1,1);
	for(int i=1;i<m;++i) add_hld(a[i],a[i+1]);
	for(int i=1;i<=n;++i) qs[i]+=qs[i-1];
	for(int i=2;i<=n;++i) k+=qs[i];
	if(k&1 || k<0) cout<<0, exit(0);
	k>>=1;
	dp[0]=1;
	for(int i=2;i<=n;++i){
		for(int j=k;j>=qs[i];--j) dp[j]=(dp[j]+dp[j-qs[i]])%md;
	}
	cout<<dp[k];

	return 0;
}

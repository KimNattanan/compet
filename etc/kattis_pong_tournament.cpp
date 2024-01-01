#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define eb emplace_back
using pii=pair<int,int>;
#define f first
#define s second

bool adj[2005][2005],flag[2005];
int deg[2005],topo[2005],id;
pii dp[2005];
bool cmp(const int &l,const int &r){
	return topo[l]<topo[r];
}

int main(){
	ios::sync_with_stdio(false); cin.tie(0);
	
	int n,k; cin>>n>>k;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j) cin>>adj[i][j];
	}
	vector<int> vec1(k),vec2;
	for(auto &e:vec1){
		cin>>e;
		++e;
		flag[e]=1;
	}
	for(int i=1;i<=n;++i){
		if(!flag[i]) vec2.eb(i);
	}


	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			if(flag[i]==flag[j]&&adj[i][j]) ++deg[j];
		}
	}
	queue<int> q;
	for(int i=1;i<=n;++i){
		if(!deg[i]) q.emplace(i);
	}
	while(q.size()){
		int u=q.front(); q.pop();
		topo[u]=++id;
		for(int v=1;v<=n;++v){
			if(flag[u]==flag[v]&&adj[u][v]&&--deg[v]==0) q.emplace(v);
		}
	}
	for(auto &e:vec1){
		if(deg[e]){
			cout<<"impossible"<<endl;
			return 0;
		}
	}


	sort(vec1.begin(),vec1.end(),cmp);
	sort(vec2.begin(),vec2.end(),cmp);
	int ans=0;
	for(int i=0;i<n-k;++i){
		int mn=1e9,mx=-1;
		for(auto &e:vec1){
			if(adj[vec2[i]][e]) mn=min(mn,topo[e]);
			if(adj[e][vec2[i]]) mx=max(mx,topo[e]);
		}
		if(mn<=mx) continue;
		else dp[i]=pii(1,mx);
		for(int j=0;j<i;++j){
			if(dp[j].f==0||mn<=dp[j].s) continue;
			if(dp[j].f+1<dp[i].f) continue;
			if(dp[j].f+1==dp[i].f&&dp[j].s>dp[i].s) continue;
			dp[i]=pii(dp[j].f+1,max(mx,dp[j].s));
		}
		ans=max(ans,dp[i].f);
	}
	ans=n-ans-k;
	if(ans<k) cout<<ans<<endl;
	else cout<<"impossible"<<endl;
	
	return 0;
}

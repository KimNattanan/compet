/*
	HS_Abyss-Point_sub_2
*/
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using pii=pair<int,int>;
#define f first
#define s second
#define eb emplace_back

ll a[100005];
vector<int> adj[100005];

ll dfs_mx(int u,int p){
	ll mx=a[u];
	for(auto &v:adj[u]){
		if(v!=p) mx=max(mx,dfs_mx(v,u));
	}
	return mx;
}
int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n,k; cin>>n>>k;
	for(int i=1;i<=n;++i) cin>>a[i];
	vector<pii> edge(n-1);
	ll ans1=0;
	for(auto &e:edge){
		cin>>e.f>>e.s;
		adj[e.f].eb(e.s), adj[e.s].eb(e.f);
		ans1+=a[e.f]+a[e.s]+min(a[e.f],a[e.s]);
	}
	ll ans2=ans1;
	for(auto &e:edge){
		ll mx1=dfs_mx(e.f,e.s);
		ll mx2=dfs_mx(e.s,e.f);
		ll val=(mx1+mx2+min(mx1,mx2))-(a[e.f]+a[e.s]+min(a[e.f],a[e.s]));
		ans2=max(ans2, ans1+val);
	}
	cout<<ans1<<'\n'<<ans2;

    return 0;
}
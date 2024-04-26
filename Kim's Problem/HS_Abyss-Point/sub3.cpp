/*
	HS_Abyss-Point_sub_3
*/
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using pii=pair<int,int>;
#define f first
#define s second
#define eb emplace_back

int p[100005],mx[100005],n,rt=1;
ll a[100005],ans;
vector<int> adj[100005];

void dfs(int u,int p){
	::p[u]=p;
	mx[u]=u;
	for(auto &v:adj[u]){
		if(v==p) continue;
		dfs(v,u);
		if(a[mx[v]]>a[mx[u]]) mx[u]=mx[v];
	}
}
void play(vector<pii> &edge){
	for(int i=1;i<=n;++i) adj[i].clear();
	for(auto &e:edge) adj[e.f].eb(e.s), adj[e.s].eb(e.f);
	dfs(rt,rt);
	int id=-1;
	ll val=0;
	for(int i=0;i<n-1;++i){
		pii &e=edge[i];
		if(e.s==p[e.f]) swap(e.f,e.s);
		ll w1=a[e.f]+a[e.s]+min(a[e.f],a[e.s]);
		ll w2=2*a[mx[e.s]]+a[rt];
		if(val<w2-w1) val=w2-w1, id=i;
	}
	if(id!=-1){
		ans+=val;
		edge[id]={rt,mx[edge[id].s]};
	}
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int k; cin>>n>>k;
	for(int i=1;i<=n;++i){
		cin>>a[i];
		if(a[i]>a[rt]) rt=i;
	}
	vector<pii> edge(n-1);
	for(auto &e:edge){
		cin>>e.f>>e.s;
		ans+=a[e.f]+a[e.s]+min(a[e.f],a[e.s]);
	}
	cout<<ans<<'\n';
	while(k--){
		play(edge);
		cout<<ans<<'\n';
	}

    return 0;
}
#include<bits/stdc++.h>
using namespace std;
#define eb emplace_back
using ll=long long;
using pii=pair<int,int>;
#define f first
#define s second

vector<int> adj[200005];
int a[200005],p[200005],mn[200005];
int fSet(int u){
	if(p[u]==u) return u;
	return p[u]=fSet(p[u]);
}
bool uSet(int u,int v){
	int U=fSet(u), V=fSet(v);
	if(U==V) return 0;
	p[U]=V;
	mn[V]=min(mn[U],mn[V]);
	return 1;
}

int main(){
	ios::sync_with_stdio(false); cin.tie(0);

	int n,m,Q; cin>>n>>m>>Q;
	int mn=1,mx=1;
	for(int i=1;i<=n;++i){
		cin>>a[i];
		p[i]=i;
		::mn[i]=a[i];
		if(a[i]<a[mn]) mn=i;
		if(a[i]>a[mx]) mx=i;
	}
	vector<pii> edge,edge2;
	for(int i=0;i<m;++i){
		int u,v; cin>>u>>v;
		edge.eb(u,v);
	}
	sort(edge.begin(),edge.end(),[&](const pii &l,const pii &r){
		return a[l.f]+a[l.s]<a[r.f]+a[r.s];
	});

	stack<ll> ans;
	ll cur=1LL*a[mn]*(n-1)+a[mx]-a[mn];
	ans.emplace(cur);
	for(auto &[u,v]:edge){
		if(fSet(u)==fSet(v)) continue;
		uSet(u,v);
		edge2.eb(u,v);
	}
	for(int i=1;i<=n;++i) p[i]=i, ::mn[i]=a[i];
	for(auto &[u,v]:edge2){
		if(u==mn||v==mn) uSet(u,v);
	}
	using A=tuple<ll,int,int>;
	priority_queue<A,vector<A>,greater<A>> pq;
	for(auto &[u,v]:edge2){
		if(u!=mn&&v!=mn) pq.emplace(a[u]-a[v]-a[mn]-max(::mn[fSet(u)],::mn[fSet(v)]),u,v);
	}
	while(pq.size()){
		auto [w,u,v]=pq.top(); pq.pop();
		int U=fSet(u),V=fSet(v);
		if(U==V) continue;
		if(max(::mn[U],::mn[V])!=a[u]+a[v]-a[mn]-w) pq.emplace(a[u]+a[v]-a[mn]-max(::mn[U],::mn[V]),u,v);
		else{
			cur+=w;
			ans.emplace(cur);
			uSet(u,v);
		}
	}

	cout<<cur<<'\n';
	while(Q--){
		if(ans.size()>1) ans.pop();
		cout<<ans.top()<<'\n';
	}

	return 0;
}

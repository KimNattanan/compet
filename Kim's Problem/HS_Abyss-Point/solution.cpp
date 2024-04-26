/*
	HS_Abyss-Point
*/
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using pii=pair<int,int>;
#define f first
#define s second

ll a[100005],mx[100005];
int p[100005];

int fSet(int u){
	if(p[u]==u) return u;
	return p[u]=fSet(p[u]);
}
void uSet(int u,int v){
	int U=fSet(u), V=fSet(v);
	p[U]=V;
	mx[V]=max(mx[U],mx[V]);
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n,k; cin>>n>>k;
	for(int i=1;i<=n;++i) cin>>a[i];
	vector<pii> edge(n-1);
	for(auto &e:edge) cin>>e.f>>e.s;
	
	stack<ll> ans;
	int mx=1;
	ll cur=0;
	for(int i=1;i<=n;++i){
		if(a[i]>a[mx]) mx=i;
		cur+=a[i];
	}
	cur+=cur+a[mx]*(n-3); // best = connect all to mx = 2*(sum-mx) + (n-1)*mx
	ans.emplace(cur);

	priority_queue<pair<ll,pii>> pq;
	for(int i=1;i<=n;++i){
		p[i]=i;
		::mx[i]=a[i];
	}
	for(auto &e:edge){
		if(e.f==mx||e.s==mx) uSet(e.f,e.s); // already connected to mx
	}
	for(auto &e:edge){
		if(e.f==mx||e.s==mx) continue;
		// w1 = a[u] + a[v] + min(a[u], a[v])
		// w2 = a[mx] + 2*min(max_in_tree_U, max_in_tree_V)
		// cost = w1-w2
		pq.emplace(a[e.f]+a[e.s]+min(a[e.f],a[e.s])-a[mx]-2*min(::mx[fSet(e.f)],::mx[fSet(e.s)]), e);
	}
	while(pq.size()){
		ll w=pq.top().f;
		pii e=pq.top().s;
		pq.pop();
		int U=fSet(e.f), V=fSet(e.s);
		if(U==V) continue;
		ll w1=a[e.f]+a[e.s]+min(a[e.f],a[e.s]);
		ll w2=a[mx]+2*min(::mx[U],::mx[V]);
		if(w1-w2 != w) pq.emplace(w1-w2, e);
		else{
			cur+=w;
			ans.emplace(cur);
			uSet(U,V);
		}
	}
	cout<<ans.top()<<'\n';
	while(k--){
		if(ans.size()>1) ans.pop();
		cout<<ans.top()<<'\n';
	}

    return 0;
}
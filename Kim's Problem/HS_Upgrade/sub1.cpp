/*
	HS_Sponge_off
*/
#include<bits/stdc++.h>
using namespace std;
#define eb emplace_back
using pii=pair<int,int>;
#define f first
#define s second
using ll=long long;

using A=pair<ll,int>;

vector<pii> adj[100005];
ll d[2][100005];
priority_queue<A,vector<A>,greater<A>> pq;

int main(){
	ios::sync_with_stdio(false); cin.tie(0);

    int n,m,H,S; cin>>n>>m>>H>>S;
	for(int i=0;i<m;++i){
		int u,v,w; cin>>u>>v>>w;
		adj[u].eb(v,w), adj[v].eb(u,w);
	}

	for(int i=1;i<=n;++i) d[0][i]=d[1][i]=1e18;
	pq.emplace(0,H);
	d[0][H]=0;
	while(!pq.empty()){
		ll w=pq.top().f;
		int u=pq.top().s;
		pq.pop();
		for(auto &vw:adj[u]){
			if(d[0][vw.f]>w+vw.s){
				d[0][vw.f]=w+vw.s;
				pq.emplace(d[0][vw.f],vw.f);
			}
		}
	}

	int Q; cin>>Q;
	while(Q--){
		int x; cin>>x;
		cout<<d[0][x]<<'\n';
	}

	return 0;
}

#include "roadreverse.h"
#include<bits/stdc++.h>
using namespace std;
#define eb emplace_back
#define sz(x) (int)(x).size()

vector<int> adj[100005];
int deg[100005],group[100005],order[100005];
struct A{
	int mn1,mn2;
	A():mn1(1e9),mn2(1e9){}
	void upd(int x){
		mn2=min(mn2,x);
		if(mn1>mn2) swap(mn1,mn2);
	}
	void upd(A x){
		upd(x.mn1);
		upd(x.mn2);
	}
}mn[100005][15];

void find_topo(vector<int> &topo){
	queue<int> q;
	q.emplace(0);
	while(q.size()){
		int u=q.front(); q.pop();
		topo.eb(u);
		for(auto &v:adj[u]){
			if(--deg[v]==0) q.emplace(v);
		}
	}
}

int count_roads(int N, int M, int K,
		std::vector<std::vector<int>> S,
		std::vector<std::pair<int,int>> R)
{
	int ans=0;
	for(int i=0;i<K;++i){
		for(int j=0;j<sz(S[i]);++j){
			group[S[i][j]]=i;
			order[S[i][j]]=j;
		}
	}
	for(auto &[u,v]:R) adj[u].eb(v), ++deg[v];
	for(auto &e:S){
		adj[0].eb(e[0]), ++deg[e[0]];
		for(int i=1;i<sz(e);++i) adj[e[i-1]].eb(e[i]), ++deg[e[i]];
	}
	vector<int> topo;
	find_topo(topo);

	for(int i=N-1;i>=0;--i){
		for(auto &v:adj[topo[i]]){
			mn[topo[i]][group[v]].upd(order[v]);
			for(int k=0;k<K;++k) mn[topo[i]][k].upd(mn[v][k]);
		}
	}
	for(int i=0;i<N;++i){
		for(auto &v:adj[i]){
			A &x=mn[i][group[v]];
			if(x.mn1!=order[v]) ans+=x.mn1>order[v];
			else ans+=x.mn2>order[v];
		}
	}

	return ans;
}

#include "september.h"
#include<bits/stdc++.h>
using namespace std;
#define eb emplace_back

vector<int> adj[100005];
bitset<100005> vis;
queue<int> q;

int solve(int N, int M, std::vector<int> F, std::vector<std::vector<int>> S) {
	vis.reset();
	for(int i=0;i<N;++i) adj[i].clear();
	for(int i=1;i<N;++i) adj[F[i]].eb(i);
	int ans=0;
	for(int i=0;i<S[0].size();++i){
		for(int j=0;j<S.size();++j){
			if(!vis[S[j][i]]){
				q.emplace(S[j][i]);
				vis[S[j][i]]=1;
				while(!q.empty()){
					int u=q.front(); q.pop();
					for(auto &v:adj[u]) if(!vis[v]) vis[v]=1, q.emplace(v);
				}
			}
		}
		if(vis.count()==i+1) ++ans;
	}
	return ans;
}

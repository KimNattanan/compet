#include "tree.h"
#include<bits/stdc++.h>
using namespace std;

int deg[500005];
priority_queue<int> pq;

std::vector<int> compute(int N, std::vector<int> F) {
	deg[0]=1;
	for(int i=1;i<F.size();++i) ++deg[F[i]];
	for(int i=1;i<N;++i) if(!deg[i]) pq.emplace(i);
	vector<int> ans;
	while(!pq.empty()){
		int u=pq.top(); pq.pop();
		ans.emplace_back(u);
		if(--deg[F[u]]==0) pq.emplace(F[u]);
	}
	return ans;
}

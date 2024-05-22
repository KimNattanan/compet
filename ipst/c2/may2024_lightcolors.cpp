#include "lightcolors.h"
#include<bits/stdc++.h>
using namespace std;
using pii=pair<int,int>;
using ll=long long;
#define f first
#define s second
#define eb emplace_back

vector<int> adj[100005],ans;
int deg[100005];

std::vector<int> lightcolors(int N, int M,
			     std::vector<int> A, std::vector<int> B)
{
  ans.assign(N,0);
  for(int i=0;i<M;++i) adj[A[i]].eb(B[i]), adj[B[i]].eb(A[i]);
  deque<int> dq;
  dq.eb(0);
  while(!dq.empty()){
    int u=dq.front(); dq.pop_front();
    if(ans[u]) continue;
    bitset<4> bit;
    for(auto &v:adj[u]) bit[ans[v]]=1;
    ans[u]=1;
    while(bit[ans[u]]) ++ans[u];
    for(auto &v:adj[u]){
      if(ans[v]) continue;
      ++deg[v];
      if(deg[v]==2) dq.emplace_front(v);
      else dq.eb(v);
    }
  }
  return ans;
}

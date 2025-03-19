#include<bits/stdc++.h>
using namespace std;
#define eb emplace_back

vector<int> adj[905];
int mt[905];
bitset<905> used;
void add_edge(int u,int v){
  adj[u].eb(v), adj[v].eb(u);
}
int bpm(int n){
  function<bool(int)> kuhn=[&](int u){
    used[u]=true;
    for(auto &v:adj[u]) if(mt[v]==-1 || !used[mt[v]] && kuhn(mt[v])){
      mt[v]=u;
      return true;
    }
    return false;
  };
  for(int i=0;i<n;++i) mt[i]=-1;
  for(int i=0;i<n;++i) used.reset(), kuhn(i);
  int cnt=0;
  for(int i=0;i<n;++i) if(mt[i]!=-1) ++cnt;
  return cnt>>1;
}

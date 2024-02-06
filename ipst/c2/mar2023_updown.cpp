#include "updown.h"
#include<bits/stdc++.h>
using namespace std;
#define eb emplace_back
using ll=long long;

int N;

vector<int> adj[2000005];
int group[2000005],id,cnt[2000005];
int flag[1000005];
// map<pair<int,int>,int> mp;
unordered_map<ll,int> mp;

void dfs(int u,int g){
  int u0=u;
  if(u>=N) u0-=N;
  group[u]=g;
  if(flag[u0]!=g) flag[u0]=g,++cnt[g];
  for(auto &v:adj[u]){
    if(!group[v]) dfs(v,g);
  }
}

ll h(int x,int y){
  return 10000000LL*x+y;
}

std::vector<int> updown(int N, int M, std::vector<int> U, std::vector<int> V) {
  ::N=N;
  for(int i=0;i<M;++i){
    if(U[i]>V[i]) swap(U[i],V[i]);
    adj[U[i]].eb(V[i]+N);
    adj[V[i]+N].eb(U[i]);
  }
  for(int i=0;i<N;++i){
    if(!group[i]) dfs(i,++id);
    if(!group[i+N]) dfs(i+N,++id);
  }
  for(int i=0;i<N;++i){
    int g1=group[i],g2=group[i+N];
    if(g1!=g2) ++mp[h(min(g1,g2),max(g1,g2))];
  }
  vector<int> ans(N);
  for(int i=0;i<N;++i){
    int g1=group[i],g2=group[i+N];
    if(g1==g2) ans[i]=cnt[g1]-1;
    else ans[i]=cnt[g1]+cnt[g2]-mp[h(min(g1,g2),max(g1,g2))]-1;
  }
  return ans;
}

#include<bits/stdc++.h>
using namespace std;
#define eb emplace_back

vector<int> adj[100005];
bool vis[100005];
int sz[100005],lv[100005],cp[100005];

int dfs_sz(int u,int p){
  sz[u]=1;
  for(auto &v:adj[u]) if(v!=p && !vis[v]) sz[u]+=dfs_sz(v,u);
  return sz[u];
}
int centroid(int u,int p,int n){
  for(auto &v:adj[u]) if(v!=p && !vis[v] && sz[v]>n) return centroid(v,u,n);
  return u;
}
void decomp(int u,int p=-1){
  int c = centroid(u,u,dfs_sz(u,u)>>1);
  vis[c] = 1;
  cp[c] = p;
  lv[c] = (p==-1 ? 0 : lv[p]+1);

  //...

  for(auto &v:adj[c]) if(!vis[v]) decomp(v,c);
}
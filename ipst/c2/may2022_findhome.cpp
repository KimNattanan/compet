#include "findhome.h"
#include<bits/stdc++.h>
using namespace std;
#define eb emplace_back

vector<int> adj[305];
bitset<305> used, vis; 
int N, d[305];
queue<int> q;

void bfs(int u0){
  d[u0]=0;
  q.emplace(u0);
  while(q.size()){
    int u=q.front(); q.pop();
    for(auto &v:adj[u]){
      if(used[v] && d[v]>d[u]+1){
        d[v]=d[u]+1;
        q.emplace(v);
      }
    }
  }
}
int count(int v0){
  vis[v0]=1;
  q.emplace(v0);
  int cnt=1;
  while(q.size()){
    int u=q.front(); q.pop();
    for(auto &v:adj[u]){
      if(used[v] && d[v]==d[u]+1 && !vis[v]){
        vis[v]=1;
        q.emplace(v);
        ++cnt;
      }
    }
  }
  return cnt;
}
void find_new(vector<int> &vec,int v0){
  vis[v0]=1;
  q.emplace(v0);
  vec.clear();
  vec.eb(v0);
  while(q.size()){
    int u=q.front(); q.pop();
    for(auto &v:adj[u]){
      if(used[v] && d[v]==d[u]+1 && !vis[v]){
        vis[v]=1;
        q.emplace(v);
        vec.eb(v);
      }
    }
  }
}
void play(vector<int> &vec){
  int n=vec.size();
  if(n==1) return;
  used.reset();
  for(auto &e:vec) used[e]=1;
  for(auto &u0:vec){
    for(auto &e:vec) d[e]=1e9;
    bfs(u0);
    int mx=0;
    for(auto &v0:adj[u0]){
      for(auto &e:vec) vis[e]=0;
      mx=max(mx,count(v0));
    }
    if(mx>(n>>1)) continue;
    int res=check(u0);
    if(res==u0){
      vec.clear();
      vec.eb(u0);
      return;
    }
    for(auto &e:vec) vis[e]=0;
    find_new(vec,res);
    play(vec);
    break;
  }
}

int find_home(int N, int M, std::vector<std::pair<int,int>> R)
{
  ::N=N;
  for(auto &[u,v]:R) adj[u].eb(v), adj[v].eb(u);
  vector<int> vec(N);
  iota(vec.begin(),vec.end(),0);
  play(vec);
  return vec[0];
}

#include<bits/stdc++.h>
using namespace std;
#define eb emplace_back

template<class F>
struct dinic{
  struct E{
    int to;
    F flow,cap;
    E(int to,F cap):to(to),flow(0),cap(cap){}
    F getCap(){ return cap-flow; }
  };
  const F FINF=numeric_limits<F>::max()/2;

  int n;
  vector<vector<int>> adj;
  vector<E> e;
  queue<int> q;
  vector<int> lv,ptr;

  void init(int n){
    this->n = n;
    adj.assign(n,{});
    e.clear();
  }
  void addEdge(int u,int v,F cap){
    adj[u].eb(e.size()), e.eb(v,cap);
    adj[v].eb(e.size()), e.eb(u,0);
  }
  bool bfs(int s,int t){
    lv.assign(n,-1);
    lv[s]=0;
    q.emplace(s);
    while(!q.empty()){
      int u=q.front(); q.pop();
      for(auto &id:adj[u]){
        if(!e[id].getCap() || lv[e[id].to]!=-1) continue;
        lv[e[id].to] = lv[u]+1;
        q.emplace(e[id].to);
      }
    }
    return lv[t]!=-1;
  }
  F dfs(int u,int t,F f){
    if(!f || u==t) return f;
    for(auto &p=ptr[u];p<adj[u].size();++p){
      int id = adj[u][p];
      if(lv[e[id].to] != lv[u]+1) continue;
      F aug = dfs(e[id].to,t,min(f,e[id].getCap()));
      if(!aug) continue;
      e[id].flow += aug;
      e[id^1].flow -= aug;
      return aug;
    }
    return 0;
  }
  F flow(int s,int t){
    F f=0;
    while(bfs(s,t)){
      ptr.assign(n,0);
      while(F aug=dfs(s,t,FINF)) f += aug;
    }
    return f;
  }
};

#include<bits/stdc++.h>
using namespace std;
#define eb emplace_back

template<class F,class C>
struct mincostFlow{
  struct E{
    int to;
    F flow,cap;
    C cost;
    E(int to,F cap,C cost):to(to),flow(0),cap(cap),cost(cost){}
    F getCap(){ return cap-flow; }
  };
  using P = pair<C,F>;
  const C CINF=numeric_limits<C>::max()/2;

  int n;
  vector<vector<int>> adj;
  vector<E> e;
  priority_queue<P,vector<P>,greater<P>> pq;
  vector<C> d;
  vector<int> path;

  void init(int n){
    this->n = n;
    adj.assign(n,{});
    e.clear();
  }
  void addEdge(int u,int v,F cap,C cost){
    adj[u].eb(e.size()), e.eb(v,cap,cost);
    adj[v].eb(e.size()), e.eb(u,0,-cost);
  }
  bool dijk(int s,int t){
    d.assign(n,CINF), path.assign(n,-1);
    d[s]=0;
    pq.emplace(0,s);
    while(!pq.empty()){
      auto [w,u]=pq.top(); pq.pop();
      if(d[u]!=w) continue;
      for(auto &id:adj[u]){
        if(e[id].getCap()<=0 || w+e[id].cost >= d[e[id].to]) continue;
        d[e[id].to] = w+e[id].cost;
        path[e[id].to] = id;
        pq.emplace(d[e[id].to], e[id].to);
      }
    }
    return d[t] < CINF;
  }
  pair<F,C> flow(int s,int t,F K){ // required flow <= K
    F f=0;
    C c=0;
    while(f<K && dijk(s,t)){
      F aug=K-f;
      for(int u=t;u!=s;u=e[path[u]^1].to) aug = min(aug, e[path[u]].getCap()); // bottleneck
      for(int u=t;u!=s;u=e[path[u]^1].to) e[path[u]].flow += aug,
                                          e[path[u]^1].flow -= aug; // push flow
      f += aug, c += aug*d[t];
    }
    return {f,c};
  }
};

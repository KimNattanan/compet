#include "avoid.h"
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using pii=pair<int,int>;
#define f first
#define s second
#define eb emplace_back
#define sz(x) (int)x.size()
#define add(x,y) (((x+y)%md+md)%md)
#define Add(x,y) (x=add(x,y))
#define mul(x,y) (((add(x,0)*add(y,0))%md+md)%md)
#define Mul(x,y) (x=mul(x,y))
template<class T> T chmn(T &x,T y){ return x=min(x,y); }
template<class T> T chmx(T &x,T y){ return x=max(x,y); }
const int inf=1e9;
const ll linf=1e18;
const ll md=1e9+7;

struct Aho{
  struct node{
    node *adj[26],*suf;
    int id;
    bool ok;
    node(int id):id(id),suf(nullptr),ok(1){ for(auto &e:adj) e=nullptr; }
  };
  using pnode=node*;
  vector<pnode> nds;
  queue<pair<pnode,int>> q;

  Aho():nds({new node(0)}){}
  
  pnode insert(string s){
    pnode t=nds[0];
    for(auto &e:s){
      int i = e-'a';
      if(t->adj[i]) t=t->adj[i];
      else nds.eb(t=t->adj[i]=new node(sz(nds)));
    }
    return t;
  }
  pnode find_suf(pnode t,int i){
    while(t!=nds[0] && !t->adj[i]) t=t->suf;
    if(t->adj[i]) return t->adj[i];
    return nds[0];
  }
  void build(){
    nds[0]->suf=nds[0];
    for(int i=0;i<26;++i) if(nds[0]->adj[i]) q.emplace(nds[0],i);
    while(!q.empty()){
      auto [u,i]=q.front(); q.pop();
      if(u==nds[0]) u->adj[i]->suf = u;
      else u->adj[i]->suf = find_suf(u->suf,i);
      u->adj[i]->ok &= u->ok & u->adj[i]->suf->ok;
      for(int j=0;j<26;++j) if(u->adj[i]->adj[j]) q.emplace(u->adj[i], j);
    }
  }
};

struct M{
  vector<vector<ll>> a;
  M(int n=0):a(vector<vector<ll>>(n,vector<ll>(n,0))){}
  void init(int n){ a.assign(n,vector<ll>(n,0)); }
  friend M operator*(M lhs,M rhs){
    M m(sz(lhs.a));
    for(int i=0;i<sz(lhs.a);++i){
      for(int j=0;j<sz(lhs.a);++j){
        for(int k=0;k<sz(lhs.a);++k){
          Add(m.a[i][j],mul(lhs.a[i][k],rhs.a[k][j]));
        }
      }
    }
    return m;
  }
};

Aho aho;
M dp[31];

int count_strings(int N, int A, std::vector<std::string> K, int L) {
  for(auto &e:K) aho.insert(e)->ok=0;
  aho.build();
  dp[0].init(sz(aho.nds));
  for(int i=0;i<sz(aho.nds);++i){
    for(int j=0;j<A;++j){
      auto v=aho.find_suf(aho.nds[i],j);
      Add(dp[0].a[i][v->id],v->ok);
    }
  }
  for(int i=0;i<30;++i) dp[i+1]=dp[i]*dp[i];
  
  M ans(sz(aho.nds));
  ans.a[0][0]=1;
  for(int i=0;i<30;++i) if(L>>i&1) ans = ans*dp[i];
  ll res=0;
  for(int i=0;i<sz(aho.nds);++i) Add(res,ans.a[0][i]);
  return res;
}

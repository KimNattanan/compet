#include "village.h"
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
#define f first
#define s second
#define eb emplace_back

int U[200005],V[200005];
ll W[200005],a[100005];
multiset<pair<ll,int>> ms[100005];
map<int,ll> mid[200005];

void init_village(int N, int M, int Q, std::vector<int> U, std::vector<int> V, std::vector<int> W) {
  for(int i=0;i<M;++i){
    ::U[i]=U[i], ::V[i]=V[i], ::W[i]=W[i];
    ll w=W[i]+1>>1;
    ms[U[i]].emplace(mid[i][U[i]]=w,i);
    ms[V[i]].emplace(mid[i][V[i]]=w,i);
  }
}

std::vector<std::vector<int>> move_in(int K, std::vector<int> X, std::vector<int> Y) {
  std::vector<std::vector<int>> ret;
  for(int i=0;i<K;++i){
    vector<int> edge;
    a[X[i]]+=Y[i];
    while(!ms[X[i]].empty() && ms[X[i]].begin()->f<=a[X[i]]){
      auto [w,id]=*ms[X[i]].begin();
      assert(ms[U[id]].erase(pair<ll,int>{mid[id][U[id]],id})==1);
      assert(ms[V[id]].erase(pair<ll,int>{mid[id][V[id]],id})==1);
      if(a[U[id]]+a[V[id]]>=W[id]) edge.eb(id);
      else{
        ll w=W[id]-a[U[id]]-a[V[id]]+1>>1;
        ms[U[id]].emplace(mid[id][U[id]]=a[U[id]]+w,id);
        ms[V[id]].emplace(mid[id][V[id]]=a[V[id]]+w,id);
      }
    }
    ret.eb(edge);
  }
  return ret;
}

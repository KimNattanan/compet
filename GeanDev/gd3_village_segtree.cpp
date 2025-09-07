#include "village.h"
#include<bits/stdc++.h>
using namespace std;
using pii=pair<int,int>;
using i3=array<int,3>;
using ll=long long;
#define f first
#define s second
#define eb emplace_back

struct segment{
  vector<pii> vec;
  vector<ll> t,lz;
  void build(int i,int il,int ir){
    if(il==ir) return void(t[i]=vec[il].s);
    int mid=il+ir>>1;
    build(i<<1,il,mid), build(i<<1|1,mid+1,ir);
    t[i]=min(t[i<<1],t[i<<1|1]);
  }
  void build(){
    if(vec.empty()) return;
    t.assign((int)vec.size()<<2,1e18);
    lz.assign(t.size(),0);
    build(1,0,(int)vec.size()-1);
  }
  void flush(int i,int il,int ir){
    if(il!=ir) lz[i<<1]+=lz[i], lz[i<<1|1]+=lz[i];
    t[i]+=lz[i];
    lz[i]=0;
  }
  void upd2(int i,int il,int ir,vector<int> &edge){
    flush(i,il,ir);
    if(il==ir) return edge.eb(vec[il].f),void(t[i]=1e18);
    int mid=il+ir>>1;
    flush(i<<1,il,mid);
    if(t[i<<1]<=0) upd2(i<<1,il,mid,edge);
    flush(i<<1|1,mid+1,ir);
    if(t[i<<1|1]<=0) upd2(i<<1|1,mid+1,ir,edge);
    t[i]=min(t[i<<1],t[i<<1|1]);
  }
  void upd(int i,int il,int ir,int l,int r,ll v,vector<int> &edge){
    flush(i,il,ir);
    if(il>r||ir<l) return;
    if(l<=il&&ir<=r){
      lz[i]+=v;
      flush(i,il,ir);
      if(t[i]<=0) upd2(i,il,ir,edge);
      return;
    }
    int mid=il+ir>>1;
    upd(i<<1,il,mid,l,r,v,edge), upd(i<<1|1,mid+1,ir,l,r,v,edge);
    t[i]=min(t[i<<1],t[i<<1|1]);
  }
  void upd(int l,int r,ll v,vector<int> &edge){
    if(vec.empty()) return;
    upd(1,0,(int)vec.size()-1,l,r,v,edge);
  }
}t[100005];

vector<i3> adj[100005];
map<pii,vector<int>> mp;

void init_village(int N, int M, int Q, std::vector<int> U, std::vector<int> V, std::vector<int> W) {
  int id=0;
  for(int i=0;i<M;++i) mp[minmax(U[i],V[i])].eb(i);
  for(auto [uv,vec]:mp){
    auto [u,v]=uv;
    if(adj[u].size()>adj[v].size()) swap(u,v);
    int l=t[v].vec.size();
    for(auto e:vec) t[v].vec.eb(e,W[e]);
    int r=t[v].vec.size()-1;
    adj[u].eb(i3{v,l,r});
  }
  for(int i=0;i<N;++i) t[i].build();
}

std::vector<std::vector<int>> move_in(int K, std::vector<int> X, std::vector<int> Y) {
  std::vector<std::vector<int>> ret;
  for(int i=0;i<K;++i){
    int &x=X[i], &y=Y[i];
    vector<int> edge;
    t[x].upd(0,t[x].vec.size(),-y,edge);
    for(auto &[v,l,r]:adj[x]) t[v].upd(l,r,-y,edge);
    ret.eb(edge);
  }
  return ret;
}

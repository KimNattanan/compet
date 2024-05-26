#include "orgdelivery.h"
#include<bits/stdc++.h>
using namespace std;
using pii=pair<int,int>;
using ll=long long;
#define f first
#define s second
#define eb emplace_back

const ll inf=1e18;

vector<ll> ans,V,comp;
vector<pii> query[100005];
vector<int> adj[100005],W;
int sz[100005],big[100005],id[100005];
ll d[100005];

struct segment{
  ll mn[1<<18];
  bool lz[1<<18];
  int l0,r0;
  void build(int i,int il,int ir){
    mn[i]=inf;
    if(il==ir) return;
    int mid=il+ir>>1;
    build(i<<1,il,mid), build(i<<1|1,mid+1,ir);
  }
  void build(int l,int r){ l0=l, r0=r, build(1,l,r); }
  void flush(int i,int il,int ir){
    if(!lz[i]) return;
    if(il!=ir) lz[i<<1]=lz[i<<1|1]=1;
    mn[i]=1e18;
    lz[i]=0;
  }
  void upd(int i,int il,int ir,int id,ll v){
    flush(i,il,ir);
    mn[i]=min(mn[i],v);
    if(il==ir) return;
    int mid=il+ir>>1;
    if(id<=mid) upd(i<<1,il,mid,id,v);
    else upd(i<<1|1,mid+1,ir,id,v);
  }
  void upd(int id,ll v){ upd(1,l0,r0,id,v); }
  ll qr(int i,int il,int ir,int l,int r){
    flush(i,il,ir);
    if(il>r||ir<l) return inf;
    if(l<=il&&ir<=r) return mn[i];
    int mid=il+ir>>1;
    return min(qr(i<<1,il,mid,l,r), qr(i<<1|1,mid+1,ir,l,r));
  }
  ll qr(int l,int r){ return qr(1,l0,r0,l,r); }
  void clear(){ lz[1]=1; }
}t1,t2;

void dfs1(int u,ll w){
  d[u]=w;
  sz[u]=1;
  big[u]=-1;
  int mx=0;
  for(auto &v:adj[u]){
    dfs1(v,w+W[v]);
    sz[u]+=sz[v];
    if(sz[v]>mx) mx=sz[v], big[u]=v;
  }
}
void add(int u){
  t1.upd(id[u],d[u]-V[u]);
  t2.upd(id[u],d[u]+V[u]);
  for(auto &v:adj[u]) add(v);
}
void dfs2(int u){
  for(auto &v:adj[u]){
    if(v==big[u]) continue;
    dfs2(v);
    t1.clear(), t2.clear();
  }
  if(big[u]!=-1) dfs2(big[u]);
  for(auto &v:adj[u]) if(v!=big[u]) add(v);
  t1.upd(id[u],d[u]-V[u]);
  t2.upd(id[u],d[u]+V[u]);
  for(auto &[i,a]:query[u]){
    ans[i]=min(t1.qr(1,id[a])+V[a],t2.qr(id[a],comp.size())-V[a])-d[u];
  }
}

std::vector<long long> mincost(int N, std::vector<int> P,
			       std::vector<long long> V, std::vector<int> W,
			       int Q,
			       std::vector<int> A, std::vector<int> B)
{
  ::V=V, ::W=W;
  ans.resize(Q);
  comp.eb(V[0]);
  for(int i=0;i<Q;++i) query[B[i]].eb(i,A[i]);
  for(int i=1;i<N;++i) adj[P[i]].eb(i), comp.eb(V[i]);
  sort(comp.begin(),comp.end());
  comp.erase(unique(comp.begin(),comp.end()),comp.end());
  for(int i=0;i<N;++i) id[i]=lower_bound(comp.begin(),comp.end(),V[i])-comp.begin()+1;
  t1.build(1,comp.size()), t2.build(1,comp.size());
  dfs1(0,0), dfs2(0);
  return ans;
}

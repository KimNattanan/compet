#include "onepath.h"
#include<bits/stdc++.h>
using namespace std;
using pii=pair<int,int>;
#define f first
#define s second
#define eb emplace_back

vector<int> adj2[100005];

struct segment{
  vector<segment> child;
  int l,r,mid;
  bool val,lazy,lz2;
  segment(int l_=0,int r_=0):l(l_),r(r_),mid(l+(r-l>>1)),lazy(0),lz2(0){}
  void build(){
    if(l==r) return void(val=0);
    child.eb(l,mid),child.eb(mid+1,r);
    child[0].build(),child[1].build();
    val=child[0].val|child[1].val;
  }
  void flush(){
    if(lazy){
      if(l!=r) child[0].lazy=child[1].lazy=1;
      val=1;
      lazy=0;
      lz2=1;
    }
  }
  void upd(int l0,int r0){
    flush();
    if(lz2) return;
    if(l0<=l&&r<=r0){
      lazy=1;
      flush();
      return;
    }
    if(l>r0||r<l0) return;
    child[0].upd(l0,r0),child[1].upd(l0,r0);
    val=1;
  }
  bool qr(int l0,int r0){
    flush();
    if(l0<=l&&r<=r0) return val;
    if(l>r0||r<l0) return 0;
    if(lz2) return 1;
    return child[0].qr(l0,r0)|child[1].qr(l0,r0);
  }
}t;
namespace HLD{
  int heavy[200005],head[200005],p0[200005],tour[200005],id1;
  int dfs(int u,int p){
    p0[u]=p;
    int sz=1;
    pii best(0,0);
    for(auto &v:adj2[u]){
      if(v!=p){
        int sz2=dfs(v,u);
        best=max(best,pii(sz2,v));
        sz+=sz2;
      }
    }
    heavy[u]=best.s;
    return sz;
  }
  void decomp(int u,int p){
    tour[u]=++id1;
    head[u]=p;
    if(heavy[u]) decomp(heavy[u],p);
    for(auto &v:adj2[u]){
      if(v!=p0[u]&&v!=heavy[u]) decomp(v,v);
    }
  }
  void init(){
    dfs(1,1);
    id1=0;
    decomp(1,1);
    t=segment(1,id1);
    t.build();
  }
}
void hld_upd(int u,int v){
  using namespace HLD;
  while(head[u]!=head[v]){
    if(tour[head[u]]>tour[head[v]]) swap(u,v);
    t.upd(tour[head[v]],tour[v]);
    v=p0[head[v]];
  }
  if(u==v) return;
  if(tour[u]>tour[v]) swap(u,v);
  t.upd(tour[u]+1,tour[v]);
}
bool hld_qr(int u,int v){
  using namespace HLD;
  while(head[u]!=head[v]){
    if(tour[head[u]]>tour[head[v]]) swap(u,v);
    if(t.qr(tour[head[v]],tour[v])) return 1;
    v=p0[head[v]];
  }
  if(u==v) return 0;
  if(tour[u]>tour[v]) swap(u,v);
  return t.qr(tour[u]+1,tour[v]);
}



bool is_dangerous(int u, int v) {
  ++u,++v;
  if(u==v) return 1;
  return hld_qr(u,v)==0;
}

void build_road(int u, int v) {
  ++u,++v;
  hld_upd(u,v);
}

struct DSU{
    vector<int> p;
    void init(int n){
           p=vector<int>(n);
           for(int i=0;i<n;++i) p[i]=i;
    }
    int fSet(int u){return p[u]=(p[u]==u?u:fSet(p[u]));}
    bool uSet(int u,int v){
            int U=fSet(u),V=fSet(v);
            if(U==V) return 0;
            p[U]=V;
            return 1;
    }
}dsu;

void initialize(int N, int M, int Q, std::vector<std::pair<int,int>> R) {
  dsu.init(N+5);
  vector<pii> vec;
  for(auto &e:R){
        ++e.f,++e.s;
        if(dsu.uSet(e.f,e.s)) adj2[e.f].eb(e.s),adj2[e.s].eb(e.f);
        else vec.eb(e.f,e.s);
  }
  HLD::init();
  for(auto &e:vec) hld_upd(e.f,e.s);
  
  return;
}
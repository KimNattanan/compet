#include "marbletracks.h"
#include<bits/stdc++.h>
using namespace std;
using i4=array<int,4>;
#define eb emplace_back
#define sz(x) (int)x.size()

struct fenwick{
  vector<int> bit;
  int sum;
  void init(int n){ bit.assign(n+1,0); sum=0; }
  void upd(int i,int x){ for(++i;i<sz(bit);i+=i&-i) bit[i]+=x; sum+=x; }
  int qr(int i){
    int ret=0;
    for(i=min(sz(bit)-1,i+1);i>0;i-=i&-i) ret+=bit[i];
    return ret;
  }
}fw;

vector<int> adj[100005], a, ans, ds[100005],ds_;
int deg[100005], d[100005], sz[100005], big[100005], tmp[100005];
bitset<100005> vis,done;
vector<i4> qrs[100005],qrs_;


void solve_tree(int rt){
  function<void(int)> dfs1=[&](int u){
    sz[u] = 1;
    big[u] = -1;
    for(auto &v:adj[u]){
      ds[rt].eb(d[v]=d[u]+1);
      dfs1(v);
      sz[u] += sz[v];
      if(big[u]==-1 || sz[v]>sz[big[u]]) big[u]=v;
    }
  };
  function<void(int,int)> add_tree=[&](int u,int x){
    fw.upd(d[u],x);
    for(auto &v:adj[u]) add_tree(v,x);
  };
  function<void(int)> dfs2=[&](int u){
    if(big[u]!=-1){
      for(auto &v:adj[u]) if(v!=big[u]) dfs2(v), add_tree(v,-1);
      dfs2(big[u]);
      for(auto &v:adj[u]) if(v!=big[u]) add_tree(v,1);
    }
    fw.upd(d[u],1);
    for(auto &[i,_,l,r]:qrs[u]) ans[i] = fw.qr(d[u]+r) - fw.qr(d[u]+l-1);
  };

  dfs1(rt);
  for(auto &v:adj[rt]) dfs2(v), add_tree(v,-1);
}

void solve_cycle(int l,int r){
  if(l==r){
    int u=a[l];
    sort(ds[u].begin(),ds[u].end());
    sort(qrs[u].begin(),qrs[u].end(),[&](const i4 &l,const i4 &r){
      return d[l[1]]+l[3] < d[r[1]]+r[3];
    });
    for(int il=0,ir=0;il!=sz(ds[u])||ir!=sz(qrs[u]);){
      if(il==sz(ds[u])){
        if(qrs[u][ir][3]-qrs[u][ir][2]+1>=sz(a)) ans[qrs[u][ir][0]] += fw.sum;
        else{
          int ql = (d[qrs[u][ir][1]]+qrs[u][ir][2]-1+sz(a))%sz(a);
          int qr = (d[qrs[u][ir][1]]+qrs[u][ir][3])%sz(a);
          ans[qrs[u][ir][0]] += fw.qr(qr)-fw.qr(ql) + (ql>=qr ? fw.sum : 0);
        }
        ++ir;
      }
      else if(ir==sz(qrs[u])) fw.upd(ds[u][il++]%sz(a),1);
      else if(ds[u][il] <= d[qrs[u][ir][1]]+qrs[u][ir][3]) fw.upd(ds[u][il++]%sz(a),1);
      else{
        if(qrs[u][ir][3]-qrs[u][ir][2]+1>=sz(a)) ans[qrs[u][ir][0]] += fw.sum;
        else{
          int ql = (d[qrs[u][ir][1]]+qrs[u][ir][2]-1+sz(a))%sz(a);
          int qr = (d[qrs[u][ir][1]]+qrs[u][ir][3])%sz(a);
          ans[qrs[u][ir][0]] += fw.qr(qr)-fw.qr(ql) + (ql>=qr ? fw.sum : 0);
        }
        ++ir;
      }
    }
    for(int il=0;il!=sz(ds[u]);++il) fw.upd(ds[u][il]%sz(a),-1);
    return;
  }
  int mid=l+r>>1;
  solve_cycle(l,mid), solve_cycle(mid+1,r);
  int ul=a[l], ur=a[mid+1];
  
  // l -> r
  for(int il=0,ir=0;il!=sz(ds[ul])||ir!=sz(qrs[ur]);){
    if(il==sz(ds[ul])){
      if(qrs[ur][ir][3]-qrs[ur][ir][2]+1>=sz(a)) ans[qrs[ur][ir][0]] += fw.sum;
      else{
        int ql = (d[qrs[ur][ir][1]]+qrs[ur][ir][2]-1+sz(a))%sz(a);
        int qr = (d[qrs[ur][ir][1]]+qrs[ur][ir][3])%sz(a);
        ans[qrs[ur][ir][0]] += fw.qr(qr)-fw.qr(ql) + (ql>=qr ? fw.sum : 0);
      }
      ++ir;
    }
    else if(ir==sz(qrs[ur])) fw.upd(ds[ul][il++]%sz(a),1);
    else if(ds[ul][il] <= d[qrs[ur][ir][1]]+qrs[ur][ir][3]) fw.upd(ds[ul][il++]%sz(a),1);
    else{
      if(qrs[ur][ir][3]-qrs[ur][ir][2]+1>=sz(a)) ans[qrs[ur][ir][0]] += fw.sum;
      else{
        int ql = (d[qrs[ur][ir][1]]+qrs[ur][ir][2]-1+sz(a))%sz(a);
        int qr = (d[qrs[ur][ir][1]]+qrs[ur][ir][3])%sz(a);
        ans[qrs[ur][ir][0]] += fw.qr(qr)-fw.qr(ql) + (ql>=qr ? fw.sum : 0);
      }
      ++ir;
    }
  }
  for(int il=0;il!=sz(ds[ul]);++il) fw.upd(ds[ul][il]%sz(a),-1);
  
  // r -> l
  for(int il=0,ir=0;il!=sz(qrs[ul])||ir!=sz(ds[ur]);){
    if(il==sz(qrs[ul])) fw.upd(ds[ur][ir++]%sz(a),1);
    else if(ir==sz(ds[ur])){
      if(qrs[ul][il][3]-qrs[ul][il][2]+1>=sz(a)) ans[qrs[ul][il][0]] += fw.sum;
      else{
        int ql = (d[qrs[ul][il][1]]+qrs[ul][il][2]-1+sz(a))%sz(a);
        int qr = (d[qrs[ul][il][1]]+qrs[ul][il][3])%sz(a);
        ans[qrs[ul][il][0]] += fw.qr(qr)-fw.qr(ql) + (ql>=qr ? fw.sum : 0);
      }
      ++il;
    }
    else if(ds[ur][ir] <= d[qrs[ul][il][1]]+qrs[ul][il][3]-sz(a)) fw.upd(ds[ur][ir++]%sz(a),1);
    else{
      if(qrs[ul][il][3]-qrs[ul][il][2]+1>=sz(a)) ans[qrs[ul][il][0]] += fw.sum;
      else{
        int ql = (d[qrs[ul][il][1]]+qrs[ul][il][2]-1+sz(a))%sz(a);
        int qr = (d[qrs[ul][il][1]]+qrs[ul][il][3])%sz(a);
        ans[qrs[ul][il][0]] += fw.qr(qr)-fw.qr(ql) + (ql>=qr ? fw.sum : 0);
      }
      ++il;
    }
  }
  for(int ir=0;ir!=sz(ds[ur]);++ir) fw.upd(ds[ur][ir]%sz(a),-1);
  
  ds_.clear();
  for(int il=0,ir=0;sz(ds_)!=sz(ds[ul])+sz(ds[ur]);){
    if(il==sz(ds[ul])) ds_.eb(ds[ur][ir++]);
    else if(ir==sz(ds[ur])) ds_.eb(ds[ul][il++]);
    else if(ds[ul][il]<ds[ur][ir]) ds_.eb(ds[ul][il++]);
    else ds_.eb(ds[ur][ir++]);
  }
  swap(ds[ul],ds_);
  qrs_.clear();
  for(int il=0,ir=0;sz(qrs_)!=sz(qrs[ul])+sz(qrs[ur]);){
    if(il==sz(qrs[ul])) qrs_.eb(qrs[ur][ir++]);
    else if(ir==sz(qrs[ur])) qrs_.eb(qrs[ul][il++]);
    else if(d[qrs[ul][il][1]]+qrs[ul][il][3] < d[qrs[ur][ir][1]]+qrs[ur][ir][3]) qrs_.eb(qrs[ul][il++]);
    else qrs_.eb(qrs[ur][ir++]);
  }
  swap(qrs[ul],qrs_);
}

std::vector<int> observe(int N, int Q, std::vector<int> v, std::vector<std::tuple<int, int, int>> queries) {
  
  for(int i=0;i<N;++i) ++deg[v[i]];
  queue<int> q;
  for(int i=0;i<N;++i) if(!deg[i]) q.emplace(i);
  while(!q.empty()){
    int u=q.front(); q.pop();
    vis[u]=1;
    if(--deg[v[u]]==0) q.emplace(v[u]);
  }


  function<void(int,int)> dfs_cycle=[&](int u,int rt){
    d[u]=sz(a);
    a.eb(u);
    if(v[u]!=rt) dfs_cycle(v[u],rt);
  };
  ans.assign(sz(queries),0), fw.init(N+5);
  for(int i=0;i<sz(queries);++i){
    auto &[u,l,r] = queries[i];
    qrs[u].eb(i4{i,u,l,r});
  }
  for(int i=0;i<N;++i) if(vis[i]) adj[v[i]].eb(i);
  for(int i=0;i<N;++i){
    if(vis[i]||done[i]) continue;
    a.clear();
    dfs_cycle(i,i);
    int m=sz(a);
    for(auto &e:a){
      d[e]=(m-d[e])%m;
      solve_tree(e);
      for(auto &[i,u,l,r]:qrs[e]) ans[i] += min(m,r-l+1);
      done[e]=1;
    }
    for(int i=1;i<sz(a);++i) swap(a[i-1],a[i]);
    solve_cycle(0,m-1);
  }

  return ans;
}

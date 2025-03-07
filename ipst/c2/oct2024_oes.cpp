#include "OES.h"
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
#define eb emplace_back
#define sz(x) (int)x.size()

const int md = 1e9+7;

vector<pair<int,ll>> adj[1000005];
int nx[1000005],ny[1000005],nxv,nyv;
ll x[1000005],y[1000005],x2[1000005],y2[1000005],xv,yv,x2v,y2v,ans;

void dfs(int u,int p){
  if(sz(adj[u])==1) return void(++nx[u]);
  for(auto &[v,vw]:adj[u]) if(v!=p){
    dfs(v,u);
    if(vw&1){
      nxv = ny[v];
      nyv = nx[v];
      xv = (y[v]+vw*ny[v])%md;
      yv = (x[v]+vw*nx[v])%md;
      x2v = (y2[v]+(ny[v]*((vw*vw)%md))%md+(vw*y[v]<<1)%md)%md;
      y2v = (x2[v]+(nx[v]*((vw*vw)%md))%md+(vw*x[v]<<1)%md)%md;
    }
    else{
      nxv = nx[v];
      nyv = ny[v];
      xv = (x[v]+vw*nx[v])%md;
      yv = (y[v]+vw*ny[v])%md;
      x2v = (x2[v]+(nx[v]*((vw*vw)%md))%md+(vw*x[v]<<1)%md)%md;
      y2v = (y2[v]+(ny[v]*((vw*vw)%md))%md+(vw*y[v]<<1)%md)%md;
    }
    if(nx[u]&&nxv) ans = (ans+((x[u]*xv<<1)%md+(x2[u]*nxv)%md+(x2v*nx[u])%md)%md)%md;
    if(ny[u]&&nyv) ans = (ans+((y[u]*yv<<1)%md+(y2[u]*nyv)%md+(y2v*ny[u])%md)%md)%md;
    if(nx[u]&&nyv) ans = (md+ans-((x[u]*yv<<1)%md+(x2[u]*nyv)%md+(y2v*nx[u])%md)%md)%md;
    if(ny[u]&&nxv) ans = (md+ans-((y[u]*xv<<1)%md+(y2[u]*nxv)%md+(x2v*ny[u])%md)%md)%md;
    nx[u] += nxv;
    ny[u] += nyv;
    x[u] = (x[u]+xv)%md;
    y[u] = (y[u]+yv)%md;
    x2[u] = (x2[u]+x2v)%md;
    y2[u] = (y2[u]+y2v)%md;
  }
}

int machinepower(int N, std::vector<int> U, std::vector<int> V, std::vector<int> L) {
  if(N==2){
    if(L[0]&1) return ((-1LL*L[0]*L[0])%md+md)%md;
    return (1LL*L[0]*L[0])%md;
  }
  for(int i=0;i<N-1;++i) adj[U[i]].eb(V[i],L[i]), adj[V[i]].eb(U[i],L[i]);
  for(int i=0;i<N;++i) if(sz(adj[i])>1){
    dfs(i,i);
    break;
  }
  return ans;
}

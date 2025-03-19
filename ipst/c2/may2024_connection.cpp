#include "connection.h"
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using pii=pair<int,int>;
#define f first
#define s second
#define eb emplace_back
#define sz(x) (int)x.size()
#define add(x,y) ((x+y)%md)
#define Add(x,y) (x=add(x,y))
#define mul(x,y) ((x*y)%md)
#define Mul(x,y) (x=mul(x,y))
template<class T> T chmn(T &x,T y){ return x=min(x,y); }
template<class T> T chmx(T &x,T y){ return x=max(x,y); }
const int inf=1e9;
const ll linf=1e18;
const ll md=1e9+7;

vector<int> adj[1000005];
bitset<1000005> isMax;

struct BCC{
  int disc[1000005],low[1000005],id;
  bitset<1000005> ap;
  stack<int> st;
  vector<vector<int>> comp;
  void tarj(int u,int p){
    disc[u]=low[u]=++id;
    st.emplace(u);
    for(auto &v:adj[u]) if(v!=p){
      if(!disc[v]){
        tarj(v,u);
        if(low[v]>=disc[u]){
          ap[u] = (p!=-1 || low[v]!=disc[u]);
          comp.eb(vector<int>{u});
          while(comp.back().back()!=v) comp.back().eb(st.top()), st.pop();
        }
        else chmn(low[u],low[v]);
      }
      else low[u]=min(low[u],disc[v]);
    }
  }
  void init(){
    tarj(0,-1);
  }
}bcc;

int recommended_stations(int N, int M, std::vector<int> H, std::vector<int> U, std::vector<int> V) {
  for(int i=0;i<M;++i) adj[U[i]].eb(V[i]), adj[V[i]].eb(U[i]);
  bcc.init();
  for(auto &c:bcc.comp){
    pii mx(-1,0);
    for(auto &u:c) chmx(mx,{H[u],u});
    isMax[mx.s]=1;
  }
  int ans=0;
  for(int i=0;i<N;++i) ans+=!isMax[i];
  return ans;
}

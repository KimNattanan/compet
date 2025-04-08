#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using pii=pair<int,int>;
#define f first
#define s second
#define eb emplace_back
#define sz(x) (int)x.size()
#define add(x,y) ((((x)+(y))%md+md)%md)
#define Add(x,y) (x=add(x,y))
#define mul(x,y) ((((x)*(y))%md+md)%md)
#define Mul(x,y) (x=mul(x,y))
template<class T> T chmn(T &x,T y){ return x=min(x,y); }
template<class T> T chmx(T &x,T y){ return x=max(x,y); }
const int inf=1e9;
const ll linf=1e18;
// const ll md=1e9+7;
const ll md=119<<23|1;


vector<int> adj[200005];

struct Stt{
  int P[1<<19],L[1<<19],R[1<<19],n,rt;
  bitset<1<<19> T; // 0: path cluster,  1: point cluster
  int hld(int u){
    int su=1,mx=0;
    for(auto &v:adj[u]){
      int sv=hld(v);
      su+=sv;
      if(mx<sv) mx=sv, swap(v,adj[u][0]);
    }
    return su;
  }
  void build(int u){
    n=hld(u);
    rt=compress(u);
  }
  int node(int u,int l,int r,bool t=false){
    if(u==-1) u=++n;
    if(l!=-1) P[l]=u;
    if(r!=-1) P[r]=u;
    P[u]=-1, L[u]=l, R[u]=r, T[u]=t;
    return u;
  }
  int compress(int u){
    vector<int> chs{add_node(u)};
    while(!adj[u].empty()) chs.eb(add_node(u=adj[u][0]));
    return merge(chs);
  }
  int add_node(int u){
    int v=rake(u);
    return node(u,v,-1);
  }
  int rake(int u){
    vector<int> chs;
    for(int i=1;i<sz(adj[u]);++i) chs.eb(add_edge(adj[u][i]));
    if(chs.empty()) return -1;
    return merge(chs, true);
  }
  int add_edge(int u){
    int v=compress(u);
    u=node(-1,v,-1,true);
    return u;
  }
  int merge(vector<int> &chs,bool t=false){
    if(sz(chs)==1) return chs[0];
    vector<int> chl,chr;
    for(int i=0;i<sz(chs)>>1;++i) chl.eb(chs[i]);
    for(int i=sz(chs)>>1;i<sz(chs);++i) chr.eb(chs[i]);
    int l=merge(chl), r=merge(chr);
    int u=node(-1,l,r,t);
    return u;
  }
}stt;

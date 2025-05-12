#include "skytrain.h"
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
const ll md=1e9+7;
// const ll md=119<<23|1;

vector<pii> adj[100005];
ll w[200005],d[200005];

using A=pair<ll,int>;
priority_queue<A,vector<A>,greater<A>> pq;
void dijk(){
  while(!pq.empty()){
    auto [x,u]=pq.top(); pq.pop();
    if(d[u]!=x) continue;
    for(auto &[v,vi]:adj[u]) if(d[v]>x+w[vi]) pq.emplace(d[v]=x+w[vi], v);
  }
}

long long min_total_cost(int N, int M, std::vector<int> A, std::vector<int> B, std::vector<int> W, long long K, int X, int Y) {
  for(int i=0;i<M;++i) adj[A[i]].eb(B[i],i), adj[B[i]].eb(A[i],i);
  ll ans = (1<<30)-1;
  for(int i=29;i>=0;--i){
    ans ^= 1<<i;
    for(int j=0;j<M;++j){
      w[j] = 0;
      for(int k=29;k>=0;--k) if((1<<k&W[j]) && !(1<<k&ans)){
        w[j] = ((1<<k)-1&W[j]) + ((1<<k)-((1<<k)-1&ans));
        int w2 = (W[j]|((1<<k)-1))+1;
        if((w2&ans)==w2) chmn(w[j], ll(w2-W[j]));
        break;
      }
    }
    fill(d,d+N,linf);
    pq.emplace(d[X]=0, X);
    dijk();
    if(d[Y]>K) ans ^= 1<<i;
  }
  return ans;
}

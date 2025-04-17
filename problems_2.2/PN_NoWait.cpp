#include<bits/stdc++.h>
using namespace std;
using ll=long long;
#define eb emplace_back

int V[500005],deg[500005];
ll val[500005],dp[500005];
queue<int> q;
vector<int> topo;
priority_queue<ll> pq;

void compress(int rt){
  int u=V[rt];
  V[rt]=rt, deg[rt]=-1;
  while(u!=rt){
    int nxt=V[u];
    V[u]=rt, deg[u]=-1, val[rt]+=val[u];
    u=nxt;
  }
}

void solve(){
  int n; cin>>n;
  for(int i=1;i<=n;++i) cin>>V[i]>>val[i], ++deg[V[i]];
  int k; cin>>k;

  /// find topo order
  for(int i=1;i<=n;++i) if(deg[i]==0) q.emplace(i);
  while(q.size()){
    int u=q.front(); q.pop();
    topo.eb(u);
    if(--deg[V[u]]==0) q.emplace(V[u]);
  }
  
  /// compress cycle
  for(int i=1;i<=n;++i) if(deg[i]==1) compress(i), topo.eb(i);
  for(int i=1;i<=n;++i) if(deg[i]==0 && deg[V[i]]==-1) V[i]=V[V[i]];

  /// calc dp in topo order
  for(auto &u:topo){
    dp[u] += val[u];
    if(V[u]!=u && dp[u] > dp[V[u]]) pq.emplace(dp[V[u]]), dp[V[u]]=dp[u];
    else pq.emplace(dp[u]);
  }
  ++k;
  ll ans=0;
  while(k-- && !pq.empty()) ans+=pq.top(), pq.pop();
  cout<<ans<<'\n';
  
  /// clear
  for(int i=1;i<=n;++i) dp[i]=deg[i]=0;
  topo.clear();
  while(!pq.empty()) pq.pop();
}

int main(){
  ios::sync_with_stdio(false); cin.tie(0);

  int Q(1);
  cin>>Q;
  while(Q--) solve();
}

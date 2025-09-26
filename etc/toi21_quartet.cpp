#include<bits/stdc++.h>
using namespace std;
using ll=long long;
#define eb emplace_back
#define sz(x) (int)x.size()
#define add(x,y) ((((x)+(y))%md+md)%md)
#define Add(x,y) (x=add(x,y))
#define mul(x,y) ((((x)*(y))%md+md)%md)
#define Mul(x,y) (x=mul(x,y))
const ll md=1e9+7;

vector<int> adj[200005];
ll dp[200005][5];

void dfs(int u,int p){
  dp[u][0] = (adj[u].size()==1);
  for(auto &v:adj[u]) if(v!=p){
    dfs(v,u);
    for(int i=3;i>=0;--i) Add(dp[u][i], (i ? mul(dp[u][i-1], dp[v][0]) : dp[v][0]));
  }
}

int main(){
  ios::sync_with_stdio(false); cin.tie(0);

  int n,m; cin>>n>>m;
  for(int i=n+m-1;i>0;--i){
    int u,v; cin>>u>>v;
    adj[u].eb(v), adj[v].eb(u);
  }
  dfs(n+1,0);
  ll ans = 0;
  for(int i=n+1;i<=n+m;++i){
    Add(ans, dp[i][3]);
    Add(ans, mul(dp[i][2], n-dp[i][0]));
  }
  cout << ans;
}
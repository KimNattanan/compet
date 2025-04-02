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

vector<pii> adj[105];
ll W[105],dp[105][55],dp_[105][55],K,a[105],b[105],d[105];


void dfs2(int u,int rt){
  for(int k0=2;k0<=K;++k0){
    dp_[u][k0]=linf;
    for(int k1=1;k1<k0;++k1){
      chmn(dp_[u][k0], dp[rt][k0-k1]+dp[u][k1]-b[u]+a[u]*d[rt]);
    }
  }
  for(auto &[v,d]:adj[u]) dfs2(v,rt);
  for(int k=2;k<=K;++k){
    chmn(dp[rt][k], dp_[u][k]);
  }
}
void dfs(int u){
  a[u]=W[u];
  b[u]=W[u]*d[u];
  for(auto &[v,dv]:adj[u]){
    d[v]=d[u]+dv;
    dfs(v);
    a[u]+=a[v], b[u]+=b[v];
  }
  for(int k=1;k<=K;++k) dp[u][k]=b[u]-a[u]*d[u];
  for(auto &[v,d]:adj[u]) dfs2(v,u);
}

void solve(){
  int n; cin>>n>>K;
  ++K;
  for(int i=1;i<=n;++i){
    int p,d; cin>>W[i]>>p>>d;
    adj[p].eb(i,d);
  }
  dfs(0);
  cout<<dp[0][K];
}

int main(){
  ios::sync_with_stdio(false); cin.tie(0);

  int Q(1);
  // cin>>Q;
  while(Q--) solve();  

}
/*



*/

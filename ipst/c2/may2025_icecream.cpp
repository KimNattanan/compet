#include "icecream.h"
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using pii=pair<int,int>;
#define f first
#define s second
#define eb emplace_back
#define sz(x) (int)x.size()
// #define add(x,y) ((((x)+(y))%md+md)%md)
#define add(x,y) (((x)+(y))%md)
#define Add(x,y) (x=add(x,y))
// #define mul(x,y) ((((x)*(y))%md+md)%md)
#define mul(x,y) (((x)*(y))%md)
#define Mul(x,y) (x=mul(x,y))
template<class T> T chmn(T &x,T y){ return x=min(x,y); }
template<class T> T chmx(T &x,T y){ return x=max(x,y); }
const int inf=1e9;
const ll linf=1e18;
const ll md=1e9+7;

using i3=array<int,3>;

ll Pow(ll a,ll b){
  ll res=1;
  for(;b>0;b>>=1,Mul(a,a)) if(b&1) Mul(res,a);
  return res;
}

int n,rt;
vector<int> P,adj[5005];
ll C[5005][5005],f[5005]={1},fi[5005]={1},dp[5005][5],dp2[5005][5005],tmp[5005];
int sz[5005];

void dfs(int u){
  dp[u][0]=dp[u][1]=dp[u][3]=1;
  sz[u]=0;
  for(auto &v:adj[u]){
    dfs(v);
    sz[u]+=sz[v];
    Mul(dp[u][0],mul(dp[v][0],C[sz[u]][sz[v]]));
    Mul(dp[u][1],dp[v][0]);
    Mul(dp[u][3],fi[sz[v]]);
  }
  ++sz[u];
  dp[u][2] = Pow(dp[u][0],md-2);
}

ll g(int p,int u){
  return mul(mul(dp[p][1],dp[u][2]),mul(f[sz[p]-sz[u]-1],mul(f[sz[u]],dp[p][3])));
}

void dfs2(int u){
  for(auto &v:adj[u]){
    ll y = g(u,v);
    for(int i=0;i<n;++i){
      tmp[i] = mul(dp2[u][i],C[n-sz[v]-1-i][sz[u]-sz[v]-1]);
      if(i!=0) Add(tmp[i],tmp[i-1]);
    }
    for(int i=0;i<n;++i){
      dp2[v][i] = (i==0 ? 0 : tmp[i-1]);
      Mul(dp2[v][i],y);
    }
    dfs2(v);
  }
}

void initialize(int N, int Q, std::vector<int> _P) {
  n=N;
  ::P=_P;
  for(int i=0;i<=N;++i){
    C[i][0]=1;
    for(int j=1;j<=i;++j) C[i][j] = add(C[i-1][j],C[i-1][j-1]);
  }
  for(int i=1;i<=N;++i) fi[i] = Pow(f[i]=mul(f[i-1],i), md-2);
  for(int i=0;i<n;++i){
    if(P[i]==-1) rt=i;
    else adj[P[i]].eb(i);
  }
  dfs(rt);
  dp2[rt][0] = 1;
  dfs2(rt);
}

ll calc(int u,int pos,int l2,int r2){
  chmn(r2,pos-1);
  if(l2>r2) return 0;
  int p=P[u];
  return mul(mul(add(tmp[r2], l2==0 ? 0 : md-tmp[l2-1]), g(p,u)), mul(dp[u][0],C[n-pos-1][sz[u]-1]));
}

long long count_perm(int x, int l1, int r1, int l2, int r2) {
  ll ans=0;
  for(int i=0;i<n;++i){
    if(i>=l2 && i<=r2) tmp[i] = mul(dp2[P[x]][i],C[n-sz[x]-1-i][sz[P[x]]-sz[x]-1]);
    else tmp[i]=0;
    if(i!=0) Add(tmp[i],tmp[i-1]);
  }
  for(int i=l1;i<=r1;++i) Add(ans, calc(x,i,l2,r2));
  return ans;
}
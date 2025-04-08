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


vector<int> adj[100005];

struct Stt{
  int P[400005],L[400005],R[400005],n,rt;
  int T[400005];
  /*
    T:{
      0: node
      1: add_edge
      2: rake
      3: add_node
      4: compress
    }
  */
  int hld(int u,int p){
    int su=1,mx=0;
    for(auto &v:adj[u]) if(v!=p){
      int sv=hld(v,u);
      su+=sv;
      if(mx<sv) mx=sv, swap(v,adj[u][0]);
    }
    for(auto &v:adj[u]) if(v==p){
      swap(v,adj[u].back());
      adj[u].pop_back();
      break;
    }
    return su;
  }
  void build(int u){
    n=hld(u,u);
    for(int i=n<<2;i>=0;--i) P[i]=L[i]=R[i]=-1;
    rt=compress(u);
  }
  int node(int u,int l,int r,int t){
    if(u==-1) u=++n;
    if(l!=-1) P[l]=u;
    if(r!=-1) P[r]=u;
    P[u]=-1, L[u]=l, R[u]=r, T[u]=t;
    return u;
  }
  int compress(int u){
    vector<int> chs{add_node(u)};
    while(!adj[u].empty()) chs.eb(add_node(u=adj[u][0]));
    return merge(chs,4);
  }
  int add_node(int u){
    int v=rake(u);
    return node(u,v,-1,v==-1 ? 0 : 3);
  }
  int rake(int u){
    vector<int> chs;
    for(int i=1;i<sz(adj[u]);++i) chs.eb(add_edge(adj[u][i]));
    if(chs.empty()) return -1;
    return merge(chs, 2);
  }
  int add_edge(int u){
    int v=compress(u);
    u=node(-1,v,-1,1);
    return u;
  }
  int merge(vector<int> &chs,int t){
    if(sz(chs)==1) return chs[0];
    vector<int> chl,chr;
    for(int i=0;i<sz(chs)>>1;++i) chl.eb(chs[i]);
    for(int i=sz(chs)>>1;i<sz(chs);++i) chr.eb(chs[i]);
    int l=merge(chl,t), r=merge(chr,t);
    int u=node(-1,l,r,t);
    return u;
  }
}stt;

ll a[100005],dp[400005][4];

void calc(int u){
  int l=stt.L[u], r=stt.R[u];
  if(stt.T[u]==0){
    dp[u][0]=dp[u][2]=dp[u][3]=max(0ll,a[u]), dp[u][1]=a[u], void();
  }
  else if(stt.T[u]==1){
    dp[u][0]=dp[l][0];
    dp[u][1]=0;
    dp[u][2]=dp[u][3]=dp[l][2];
  }
  else if(stt.T[u]==2){
    dp[u][0]=max(dp[l][0],dp[r][0]);
    dp[u][1]=0;
    dp[u][2]=max(dp[l][2],dp[r][2]);
    dp[u][3]=max({dp[l][3],dp[r][3],dp[l][2]+dp[r][2]});
  }
  else if(stt.T[u]==3){
    dp[u][0]=max(dp[l][0],dp[l][3]+a[u]);
    dp[u][1]=a[u];
    dp[u][2]=dp[u][3]=max(0ll,dp[l][2]+a[u]);
  }
  else{
    dp[u][0]=max({dp[l][0],dp[r][0],dp[l][3]+dp[r][2]});
    dp[u][1]=dp[l][1]+dp[r][1];
    dp[u][2]=max(dp[l][2],dp[l][1]+dp[r][2]);
    dp[u][3]=max(dp[r][3],dp[r][1]+dp[l][3]);
  }
}
void dfs(int u){
  if(stt.L[u]!=-1) dfs(stt.L[u]);
  if(stt.R[u]!=-1) dfs(stt.R[u]);
  calc(u);
}

int main(){
  ios::sync_with_stdio(false); cin.tie(0);

  int n,Q; cin>>n>>Q;
  for(int i=1;i<=n;++i) cin>>a[i];
  for(int i=1;i<n;++i){
    int u,v; cin>>u>>v;
    adj[u].eb(v), adj[v].eb(u);
  }
  stt.build(1);
  dfs(stt.rt);
  cout<<dp[stt.rt][0]<<'\n';
  while(Q--){
    int x,y; cin>>x>>y;
    a[x]=y;
    for(;x!=-1;x=stt.P[x]) calc(x);
    cout<<dp[stt.rt][0]<<'\n';
  }

}
/*
10 5
16 18 4 -21 9 8 -22 -15 -1 1
1 8
6 7
9 3
5 1
2 8
7 10
3 8
4 5
10 8
1 -7
10 20
8 -1
10 13
7 -7
*/

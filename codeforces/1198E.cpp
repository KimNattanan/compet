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

struct Dinic{
  struct E{
    int to;
    ll flow,cap;
    E(int to,ll cap):to(to),cap(cap),flow(0){}
    ll getCap(){ return cap-flow; }
  };
  int n;
  vector<E> e;
  vector<vector<int>> adj;
  ll U;
  vector<int> lv,pt;
  queue<int> q;
  set<pii> s;
  void init(int n){
    this->n=n;
    e.clear();
    adj.assign(n,{});
    U=0;
    s.clear();
  }
  void addEdge(int u,int v,ll cap){
    if(s.find({u,v})!=s.end()) return;
    s.emplace(u,v);
    adj[u].eb(sz(e)), e.eb(v,cap);
    adj[v].eb(sz(e)), e.eb(u,0);
    chmx(U,cap);
  }
  bool bfs(int s,int t,ll L){
    lv.assign(n,-1);
    q.emplace(s);
    lv[s]=0;
    while(!q.empty()){
      int u=q.front(); q.pop();
      for(auto &id:adj[u]){
        if(lv[e[id].to]==-1 && e[id].getCap()>=L){
          q.emplace(e[id].to);
          lv[e[id].to]=lv[u]+1;
        }
      }
    }
    return lv[t]!=-1;
  }
  ll dfs(int u,int t,ll f){
    if(u==t || !f) return f;
    for(int &i=pt[u];i<sz(adj[u]);++i){
      int id=adj[u][i];
      if(lv[e[id].to]!=lv[u]+1) continue;
      ll aug=dfs(e[id].to,t,min(f,e[id].getCap()));
      if(!aug) continue;
      e[id].flow+=aug;
      e[id^1].flow-=aug;
      return aug;
    }
    return 0;
  }
  ll flow(int s,int t){
    ll f=0;
    for(ll L=1LL<<63-__builtin_clzll(U);L>0;L>>=1){
      while(bfs(s,t,L)){
        pt.assign(n,0);
        while(ll aug=dfs(s,t,LLONG_MAX)) f+=aug;
      }
    }
    return f;
  }
}mf;

int pt[55][4];
vector<int> v1,v2;

void solve(){
  int n,m; cin>>n>>m;
  for(int i=0;i<m;++i){
    cin>>pt[i][0]>>pt[i][1]>>pt[i][2]>>pt[i][3];
    v1.eb(pt[i][0]), v1.eb(pt[i][2]+1);
    v2.eb(pt[i][1]), v2.eb(pt[i][3]+1);
  }
  sort(v1.begin(),v1.end());
  sort(v2.begin(),v2.end());
  int s=sz(v1)+sz(v2), t=s+1;
  mf.init(t+5);
  for(int i=0;i<m;++i){
    pt[i][0] = lower_bound(v1.begin(),v1.end(),pt[i][0])-v1.begin();
    pt[i][2] = lower_bound(v1.begin(),v1.end(),pt[i][2]+1)-v1.begin();
    pt[i][1] = lower_bound(v2.begin(),v2.end(),pt[i][1])-v2.begin();
    pt[i][3] = lower_bound(v2.begin(),v2.end(),pt[i][3]+1)-v2.begin();
    for(int j=pt[i][0];j<pt[i][2];++j){
      mf.addEdge(s,j,v1[j+1]-v1[j]);
      for(int k=pt[i][1];k<pt[i][3];++k) mf.addEdge(j,sz(v1)+k,ll(v1[j+1]-v1[j])*(v2[k+1]-v2[k]));
    }
    for(int k=pt[i][1];k<pt[i][3];++k) mf.addEdge(sz(v1)+k,t,v2[k+1]-v2[k]);
  }
  cout << mf.flow(s,t);
}

int main(){
  ios::sync_with_stdio(false); cin.tie(0);

  int Q(1);
  // cin>>Q;
  while(Q--) solve();
}
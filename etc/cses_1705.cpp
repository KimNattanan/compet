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

vector<int> adj[100005],adj2[200005];
int disc[100005],low[100005],id,cid[100005];
bitset<100005> isap;
vector<vector<int>> cc;
vector<int> st;

void tarj(int u,int p){
  disc[u]=low[u]=++id;
  st.eb(u);
  for(auto &v:adj[u]) if(v!=p){
    if(disc[v]) chmn(low[u], disc[v]);
    else{
      tarj(v,u);
      chmn(low[u], low[v]);
      if(low[v]>=disc[u]){
        if(disc[u]!=1 || disc[v]!=2) isap[u]=1;
        cc.eb(vector<int>{u});
        while(cc.back().back()!=v) cc.back().eb(st.back()), st.pop_back();
      }
    }
  }
}

int pa[19][200005],lv[200005],op[200005],ed[200005];
void dfs(int u,int p){
  op[u]=++id;
  lv[u] = lv[p]+1;
  pa[0][u]=p;
  for(int i=1;i<19;++i) pa[i][u]=pa[i-1][pa[i-1][u]];
  for(auto &v:adj2[u]) if(v!=p) dfs(v,u);
  ed[u]=id;
}
int LCA(int u,int v){
  if(lv[u]>lv[v]) swap(u,v);
  for(int i=18;i>=0;--i) if(lv[pa[i][v]]>=lv[u]) v=pa[i][v];
  if(u==v) return u;
  for(int i=18;i>=0;--i) if(pa[i][u]!=pa[i][v]) u=pa[i][u], v=pa[i][v];
  return pa[0][u];
}
bool f(int u,int p){
  return op[p] <= op[u] && op[u] <= ed[p];
}

void solve(){
  int n,m,Q; cin>>n>>m>>Q;
  for(int i=0;i<m;++i){
    int u,v; cin>>u>>v;
    adj[u].eb(v), adj[v].eb(u);
  }
  tarj(1,1);
  id=0;
  for(int i=1;i<=n;++i) if(isap[i]) cid[i]=++id;
  for(auto &c:cc){
    ++id;
    for(auto &u:c){
      if(isap[u]) adj2[id].eb(cid[u]), adj2[cid[u]].eb(id);
      else cid[u]=id;
    }
  }
  id=0;
  dfs(1,1);
  while(Q--){
    int u,v,x; cin>>u>>v>>x;
    if(u==x || v==x) cout<<"NO\n";
    else if(!isap[x]) cout<<"YES\n";
    else{
      u=cid[u], v=cid[v], x=cid[x];
      int y=LCA(u,v);
      if(f(x,y) && f(u,x)|f(v,x)) cout<<"NO\n";
      else cout<<"YES\n";
    }
  }
}

int main(){
  ios::sync_with_stdio(false); cin.tie(0);

  int Q(1);
  // cin>>Q;
  while(Q--) solve();

}
/*


*/
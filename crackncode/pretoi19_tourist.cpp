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

int cnt[100005];
map<int,int> _mp;
vector<pii> mp;
int freq[100005][320],p[100005][320];

int fSet(int u,int i){ return p[u][i]==u ? u : p[u][i]=fSet(p[u][i],i); }
void uSet(int u,int v,int i){
  u=fSet(u,i), v=fSet(v,i);
  p[u][i]=v;
}

void solve(){
  int n,m,k,Q; cin>>n>>m>>k>>Q;
  for(int i=0;i<k;++i){
    int x; cin>>x;
    ++cnt[x];
  }
  for(int i=1;i<=100000;++i) if(cnt[i]) ++_mp[cnt[i]];
  for(auto &e:_mp) mp.eb(e);
  vector<pii> edge(m);
  for(auto &[u,v]:edge) cin>>u>>v;
  vector<vector<int>> qrs(Q);
  for(auto &e:qrs){
    int opr; cin>>opr;
    if(opr==1){
      int p,l,r; cin>>p>>l>>r;
      --p;
      e={1,p,l,r};
      for(int i=0;i<sz(mp);++i) if(l<=mp[i].f && mp[i].f<=r) ++freq[p][i];
    }
    else{
      int u,v; cin>>u>>v;
      e={2,u,v};
    }
  }
  reverse(qrs.begin(),qrs.end());
  vector<int> ans;
  for(int i=1;i<=n;++i) fill(p[i],p[i]+sz(mp),i);
  for(int i=0;i<m;++i) for(int j=0;j<sz(mp);++j) if(!freq[i][j]) uSet(edge[i].f, edge[i].s, j);
  for(auto &e:qrs){
    if(e[0]==1){
      for(int i=0;i<sz(mp);++i) if(e[2]<=mp[i].f && mp[i].f<=e[3] && --freq[e[1]][i]==0) uSet(edge[e[1]].f, edge[e[1]].s, i);
    }
    else{
      ans.eb(0);
      for(int i=0;i<sz(mp);++i) if(fSet(e[1],i)==fSet(e[2],i)) ans.back()+=mp[i].s;
    }
  }
  reverse(ans.begin(),ans.end());
  for(auto &e:ans) cout<<e<<'\n';
}

int main(){
  ios::sync_with_stdio(false); cin.tie(0);

  int Q(1);
  // cin>>Q;
  while(Q--) solve();  

}
/*

*/

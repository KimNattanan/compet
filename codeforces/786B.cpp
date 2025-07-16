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

vector<pii> adj[1<<19];
ll d[1<<19],y=1<<18;
using A=pair<ll,int>;
priority_queue<A,vector<A>,greater<A>> pq;
int tid[100005];

void build(int i,int il,int ir,int s){
  d[i]=d[y+i]=linf;
  if(il==ir) return tid[il]=i, adj[i].eb(i+y,0), adj[i+y].eb(i,0), void();
  int mid=il+ir>>1;
  adj[i].eb(i<<1,0), adj[i].eb(i<<1|1,0);
  adj[(i<<1)+y].eb(i+y,0), adj[(i<<1|1)+y].eb(i+y,0);
  build(i<<1,il,mid,s), build(i<<1|1,mid+1,ir,s);
}
void upd(int i,int il,int ir,int opr,int u,int l,int r,int w){
  if(il>r||ir<l) return;
  if(l<=il && ir<=r){
    if(opr==2) adj[tid[u]].eb(i,w);
    else adj[i+y].eb(tid[u],w);
    return;
  }
  int mid=il+ir>>1;
  upd(i<<1,il,mid,opr,u,l,r,w), upd(i<<1|1,mid+1,ir,opr,u,l,r,w);
}

void solve(){
  int n,m,s; cin>>n>>m>>s;
  build(1,1,n,s);
  for(int i=0;i<m;++i){
    int opr; cin>>opr;
    if(opr==1){
      int u,v,w; cin>>u>>v>>w;
      adj[tid[u]].eb(tid[v],w);
    }else{
      int u,l,r,w; cin>>u>>l>>r>>w;
      upd(1,1,n,opr,u,l,r,w);
    }
  }
  pq.emplace(d[tid[s]]=0, tid[s]);
  while(!pq.empty()){
    auto [w,u]=pq.top(); pq.pop();
    if(d[u]!=w) continue;
    for(auto &[v,vw]:adj[u]) if(d[v]>w+vw) pq.emplace(d[v]=w+vw, v);
  }
  for(int i=1;i<=n;++i) cout<<(d[tid[i]] == linf ? -1 : d[tid[i]])<<" ";
}

int main(){
  ios::sync_with_stdio(false); cin.tie(0);

  int Q(1);
  // cin>>Q;
  while(Q--) solve();

}
/*


*/

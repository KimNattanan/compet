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

mt19937 rng(time(0));

struct treap{
  #undef sz
  struct node{
    node *l,*r;
    ll x,sum;
    int sz,prio;
    node(ll x=0):l(nullptr),r(nullptr),prio(rng()),x(x),sum(x),sz(1){}
  };
  using pnode=node*;
  pnode rt;
  treap():rt(nullptr){}
  int sz(pnode t){ return t ? t->sz : 0; }
  ll sum(pnode t){ return t ? t->sum : 0; }
  void upd(pnode t){
    if(!t) return;
    t->sz = sz(t->l) + 1 + sz(t->r);
    t->sum = sum(t->l) + t->x + sum(t->r);
  }
  void split(pnode t,pnode &l,pnode &r,int x){
    if(!t) return void(l=r=nullptr);
    if(sz(t->l)>=x) split(t->l,l,t->l,x), r=t;
    else split(t->r,t->r,r,x-sz(t->l)-1), l=t;
    upd(t);
  }
  void split2(pnode t,pnode &l,pnode &r,ll x){
    if(!t) return void(l=r=nullptr);
    if(t->x <= x) split2(t->r,t->r,r,x), l=t;
    else split2(t->l,l,t->l,x), r=t;
    upd(t);
  }
  void merge(pnode &t,pnode l,pnode r){
    if(!l||!r) return void(t=l?l:r);
    if(l->prio > r->prio) merge(l->r,l->r,r), t=l;
    else merge(r->l,l,r->l), t=r;
    upd(t);
  }
  void insert(pnode &t,pnode x){
    if(!t) return void(t=x);
    if(t->prio < x->prio) split2(t,x->l,x->r,x->x), t=x;
    else{
      if(t->x <= x->x) insert(t->r,x);
      else insert(t->l,x);
    }
    upd(t);
  }
  void insert(ll x){ insert(rt,new node(x)); }
  void erase(pnode &t,ll x){
    if(!t) return;
    if(t->x < x) erase(t->r,x);
    else if(t->x > x) erase(t->l,x);
    else merge(t,t->l,t->r);
    upd(t);
  }
  void erase(ll x){ erase(rt,x); }
  ll qr(int k){
    pnode t1,t2;
    split(rt,t1,t2,sz(rt)-k);
    ll ret = sum(t2);
    merge(rt,t1,t2);
    return ret;
  }
  void print(pnode t){
    if(!t) return;
    print(t->l);
    cout<<(t->x)<<'\n';
    print(t->r);
  }
  void print(){ print(rt); }
}t;

vector<pii> adj[100005];
array<ll,2> mx1[100005],mx2[100005];
ll ans[100005];

void dfs(int u,int p){
  mx1[u]=mx2[u]={0,0};
  for(auto &[v,vw]:adj[u]) if(v!=p){
    dfs(v,u);
    if(mx2[u][0] < mx1[v][0]+vw) mx2[u]={mx1[v][0]+vw, v};
    if(mx1[u][0] < mx2[u][0]) swap(mx1[u],mx2[u]);
  }
  for(auto &[v,vw]:adj[u]) if(v!=p && v!=mx1[u][1]) t.insert(mx1[v][0]+vw);
  if(p==u) t.insert(mx1[u][0]);
}
void dfs2(int u,int p,int k,ll mx=0,ll w0=0){
  t.erase(mx);
  t.insert(mx+w0);
  ans[u]=t.qr(k);
  for(auto &[v,vw]:adj[u]) if(v!=p){
    t.erase(mx1[v][0]+vw);
    t.insert(mx1[v][0]);
    dfs2(v,u,k,max(mx+w0,v==mx1[u][1] ? mx2[u][0] : mx1[u][0]),vw);
    t.insert(mx1[v][0]+vw);
    t.erase(mx1[v][0]);
  }
  t.insert(mx);
  t.erase(mx+w0);
}

int main(){
  ios::sync_with_stdio(false); cin.tie(0);

  int n,k; cin>>n>>k;
  for(int i=1;i<n;++i){
    int u,v,w; cin>>u>>v>>w;
    adj[u].eb(v,w), adj[v].eb(u,w);
  }
  dfs(1,1);
  dfs2(1,1,k);
  for(int i=1;i<=n;++i) cout<<ans[i]<<'\n';

}
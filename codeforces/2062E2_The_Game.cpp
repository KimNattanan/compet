#include<bits/stdc++.h>
using namespace std;
using i3=array<int,3>;
#define eb emplace_back
const int inf=1e9;

struct segment{
  i3 a[1<<20];
  int l0,r0;
  void build(int i,int il,int ir){
    a[i]={inf,-1,0};
    if(il==ir) return;
    int mid=il+ir>>1;
    build(i<<1,il,mid), build(i<<1|1,mid+1,ir);
  }
  void build(int l,int r){
    l0=l,r0=r;
    build(1,l,r);
  }
  void upd(int i,int il,int ir,int id,i3 x){
    if(il==ir) return void(a[i]=x);
    int mid=il+ir>>1;
    if(id<=mid) upd(i<<1,il,mid,id,x);
    else upd(i<<1|1,mid+1,ir,id,x);
    a[i]={min(a[i<<1][0],a[i<<1|1][0]),max(a[i<<1][1],a[i<<1|1][1]),a[i<<1][2]+a[i<<1|1][2]};
  }
  void upd(int id,i3 x){ return upd(1,l0,r0,id,x); }
  i3 qr(int i,int il,int ir,int l,int r){
    if(l<=il&&ir<=r) return a[i];
    if(il>r||ir<l) return {inf,-1,0};
    int mid=il+ir>>1;
    i3 xl=qr(i<<1,il,mid,l,r), xr=qr(i<<1|1,mid+1,ir,l,r);
    return {min(xl[0],xr[0]),max(xl[1],xr[1]),xl[2]+xr[2]};
  }
  i3 qr(int l,int r){ return qr(1,l0,r0,l,r); }
}t1,t2;

vector<int> adj[400005],a[400005];
int op[400005],ed[400005],id;

void dfs0(int u,int p){
  op[u]=++id;
  for(auto &v:adj[u]) if(v!=p) dfs0(v,u);
  ed[u]=id;
}

void solve(){
  int n; cin>>n;
  for(int i=1;i<=n;++i) adj[i].clear(),a[i].clear();
  for(int i=1;i<=n;++i){
    int w; cin>>w;
    a[w].eb(i);
  }
  for(int i=1;i<n;++i){
    int u,v; cin>>u>>v;
    adj[u].eb(v), adj[v].eb(u);
  }
  id=0, dfs0(1,1);
  vector<int> ans;
  t1.build(1,n), t2.build(1,n);
  for(int i=n;i>=1;--i){
    for(auto &e:a[i]){
      auto [mn,mx,cnt] = t2.qr(1,op[e]-1);
      auto [mn2,mx2,cnt2] = t2.qr(ed[e]+1,n);
      mn=min(mn,mn2), mx=max(mx,mx2), cnt+=cnt2;
      if(cnt && (mn>n||mx<1||(op[e]<=mn&&mx<=ed[e]))) ans.eb(e);
    }
    for(auto &e:a[i]){
      auto [mn,mx,cnt] = t1.qr(1,op[e]-1);
      auto [mn2,mx2,cnt2] = t1.qr(ed[e]+1,n);
      mn=min(mn,mn2), mx=max(mx,mx2);
      t2.upd(op[e],{mn,mx,1});
    }
    for(auto &e:a[i]) t1.upd(op[e],{op[e],op[e],1});
  }
  sort(ans.begin(),ans.end());
  cout<<ans.size()<<" ";
  for(auto &e:ans) cout<<e<<" ";
  cout<<'\n';
}

int main(){
  ios::sync_with_stdio(false); cin.tie(0);

  int Q; cin>>Q;
  while(Q--){
    solve();
  }
}

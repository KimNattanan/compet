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
 
 
ll d[100005];
 
struct segment{
  int l0,r0,cnt[1<<18];
  ll mn[1<<18],lz[1<<18];
  bitset<100005> used;
  vector<tuple<int,int,int>> vec[1<<18];
  void init(int l,int r,int s){ l0=l, r0=r, build(1,l,r,s); }
  void build(int i,int il,int ir,int s){
    lz[i]=linf;
    if(il==ir) return void(mn[i]=(il==s ? 0 : linf));
    int mid=il+ir>>1;
    build(i<<1,il,mid,s), build(i<<1|1,mid+1,ir,s);
    mn[i] = min(mn[i<<1],mn[i<<1|1]);
  }
  void flush(int i,int il,int ir){
    if(il!=ir) ::chmn(lz[i<<1], lz[i]), ::chmn(lz[i<<1|1], lz[i]);
    if(cnt[i]==ir-il+1) mn[i]=linf;
    else ::chmn(mn[i], lz[i]);
    lz[i]=linf;
  }
  pair<int,ll> getMin(int i,int il,int ir){
    flush(i,il,ir);
    if(il==ir) return {il,mn[i]};
    int mid=il+ir>>1;
    flush(i<<1,il,mid);
    if(mn[i]==mn[i<<1]) return getMin(i<<1,il,mid);
    return getMin(i<<1|1,mid+1,ir);
  }
  pair<int,ll> getMin(){ return getMin(1,l0,r0); }
  void chmn(int i,int il,int ir,int l,int r,ll w){
    flush(i,il,ir);
    if(il>r||ir<l) return;
    if(l<=il && ir<=r) return ::chmn(lz[i], w), flush(i,il,ir);
    int mid=il+ir>>1;
    chmn(i<<1,il,mid,l,r,w), chmn(i<<1|1,mid+1,ir,l,r,w);
    mn[i] = min(mn[i<<1],mn[i<<1|1]);
    cnt[i] = cnt[i<<1]+cnt[i<<1|1];
  }
  void chmn(int l,int r,ll w){ chmn(1,l0,r0,l,r,w); }
  void insert(int i,int il,int ir,int l,int r,int v,ll w,int id){
    if(il>r||ir<l) return;
    if(l<=il&&ir<=r) return void(vec[i].eb(v,w,id));
    int mid=il+ir>>1;
    insert(i<<1,il,mid,l,r,v,w,id), insert(i<<1|1,mid+1,ir,l,r,v,w,id);
  }
  void insert(int l,int r,int v,ll w,int id){ insert(1,l0,r0,l,r,v,w,id); }
  void qr(int i,int il,int ir,int u){
    flush(i,il,ir);
    for(auto &[v,w,id]:vec[i]) if(!used[id]){
      used[id]=1;
      chmn(v,v,d[u]+w);
    }
    vec[i].clear();
    if(il==ir) return cnt[i]=1, mn[i]=linf, void();
    int mid=il+ir>>1;
    if(u<=mid) qr(i<<1,il,mid,u);
    else qr(i<<1|1,mid+1,ir,u);
    flush(i<<1,il,mid), flush(i<<1|1,mid+1,ir);
    mn[i] = min(mn[i<<1],mn[i<<1|1]);
    cnt[i] = cnt[i<<1]+cnt[i<<1|1];
  }
  void qr(int u){ qr(1,l0,r0,u); }
}t;
 
vector<tuple<int,int,int>> qr[100005];
 
void solve(){
  int n,m,s; cin>>n>>m>>s;
  t.init(1,n,s);
  for(int i=0;i<m;++i){
    int opr; cin>>opr;
    if(opr==1){
      int u,v,w; cin>>u>>v>>w;
      qr[u].eb(v,v,w);
    }else if(opr==2){
      int u,l,r,w; cin>>u>>l>>r>>w;
      qr[u].eb(l,r,w);
    }else{
      int u,l,r,w; cin>>u>>l>>r>>w;
      t.insert(l,r,u,w,i);
    }
  }
  for(int i=1;i<=n;++i) d[i]=-1;
  while(1){
    auto [u,w]=t.getMin();
    if(w==linf) break;
    d[u]=w;
    t.qr(u);
    for(auto &[l,r,vw]:qr[u]) t.chmn(l,r,w+vw);
  }
  for(int i=1;i<=n;++i) cout<<d[i]<<" \n"[i==n];
}
 
int main(){
  ios::sync_with_stdio(false); cin.tie(0);
 
  int Q(1);
  // cin>>Q;
  while(Q--) solve();
 
}

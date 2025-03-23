#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using pii=pair<int,int>;
#define f first
#define s second
#define eb emplace_back
#define sz(x) (int)x.size()
#define add(x,y) ((x+y)%md)
#define Add(x,y) (x=add(x,y))
#define mul(x,y) ((x*y)%md)
#define Mul(x,y) (x=mul(x,y))
template<class T> T chmn(T &x,T y){ return x=min(x,y); }
template<class T> T chmx(T &x,T y){ return x=max(x,y); }
const int inf=1e9;
const ll linf=1e18;
const ll md=1e9+7;

struct segment{
  ll a[1<<22],l0,r0;
  ll b[1<<22];
  bitset<1<<22> lz;
  void init(int l,int r){ l0=l,r0=r; }
  void flush(int i,int il,int ir){
    if(!lz[i]) return;
    if(il!=ir) lz[i<<1]=lz[i<<1|1]=1;
    a[i]=b[i]=lz[i]=0;
  }
  void upd(int i,int il,int ir,int id,int x){
    flush(i,il,ir);
    if(il==ir){
      b[i]=il*(a[i]+=x);
      return;
    }
    if(il>id||ir<id) return;
    int mid=il+ir>>1;
    flush(i<<1,il,mid), flush(i<<1|1,mid+1,ir);
    if(id<=mid) upd(i<<1,il,mid,id,x);
    else upd(i<<1|1,mid+1,ir,id,x);
    a[i]=a[i<<1]+a[i<<1|1], b[i]=b[i<<1]+b[i<<1|1];
  }
  void upd(int id,int x){ upd(1,l0,r0,id,x); }
  ll qr(int i,int il,int ir,int l,int r){
    flush(i,il,ir);
    if(il>r||ir<l) return 0;
    if(l<=il&&ir<=r) return a[i];
    int mid=il+ir>>1;
    flush(i<<1,il,mid), flush(i<<1|1,mid+1,ir);
    return qr(i<<1,il,mid,l,r)+qr(i<<1|1,mid+1,ir,l,r);
  }
  ll qr(int l,int r){ return qr(1,l0,r0,l,r); }
  ll qr2(int i,int il,int ir,int k){
    flush(i,il,ir);
    if(il==ir) return min((ll)k,a[i])*il;
    int mid=il+ir>>1;
    flush(i<<1,il,mid);
    flush(i<<1,il,mid), flush(i<<1|1,mid+1,ir);
    if(a[i<<1]>=k) return qr2(i<<1,il,mid,k);
    return b[i<<1]+qr2(i<<1|1,mid+1,ir,k-a[i<<1]);
  }
  ll qr2(int k){ return qr2(1,l0,r0,k); }
  void clear(){ clear(l0,r0); }
  void clear(int i,int il,int ir,int l,int r){
    flush(i,il,ir);
    if(il>r||ir<l) return;
    if(l<=il&&ir<=r) return lz[i]=1, flush(i,il,ir);
    int mid=il+ir>>1;
    flush(i<<1,il,mid), flush(i<<1|1,mid+1,ir);
    clear(i<<1,il,mid,l,r), clear(i<<1|1,mid+1,ir,l,r);
    a[i]=a[i<<1]+a[i<<1|1], b[i]=b[i<<1]+b[i<<1|1];
  }
  void clear(int l,int r){ clear(1,l0,r0,l,r); }
}t;

vector<pii> qrs[100005];
int a[100005],L[100005],R[100005],sz[100005],big[100005];
ll ans[100005];

void dfs1(int u){
  sz[u]=1;
  big[u]=-1;
  for(auto &v:{L[u],R[u]}) if(v!=-1){
    dfs1(v);
    sz[u]+=sz[v];
    if(big[u]==-1 || sz[v]>sz[big[u]]) big[u]=v;
  }
}
void dfs3(int u,int mx){
  if(mx!=-1) t.upd(mx,1);
  for(auto &v:{L[u],R[u]}) if(v!=-1) dfs3(v,max(mx,a[u]-a[v]));
}
void dfs2(int u){
  if(big[u]==-1){
    for(auto &[k,id]:qrs[u]) ans[id]=-1;
    return;
  }
  for(auto &v:{L[u],R[u]}) if(v!=-1 && v!=big[u]){
    dfs2(v);
    t.clear();
  }
  dfs2(big[u]);
  int cnt=t.qr(0,a[u]-a[big[u]])+1;
  t.clear(0,a[u]-a[big[u]]);
  t.upd(a[u]-a[big[u]],cnt);
  for(auto &v:{L[u],R[u]}) if(v!=-1 && v!=big[u]){
    dfs3(v,a[u]-a[v]);
  }
  for(auto &[k,id]:qrs[u]) ans[id]=(sz[u]>k?t.qr2(k):-1);
}

vector<long long> transfer_problem(int N, int Q, vector<int> A, vector<int> S, vector<int> K) {
  for(int i=0;i<Q;++i) qrs[S[i]].eb(K[i],i);
  for(int i=0;i<N;++i) a[i]=A[i], L[i]=R[i]=-1;
  int rt=-1;
  stack<int> st;
  for(int i=0;i<N;++i){
    while(!st.empty() && a[st.top()]<a[i]) L[i]=st.top(), st.pop();
    if(st.empty()) rt=i;
    else R[st.top()]=i;
    st.emplace(i);
  }
  t.init(0,1000000);
  dfs1(rt);
  dfs2(rt);
  vector<ll> vans(Q);
  for(int i=0;i<Q;++i) vans[i]=ans[i];
  return vans;
}

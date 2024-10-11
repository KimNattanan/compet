#include<bits/stdc++.h>
using namespace std;
using pii=pair<int,int>;
#define f first
#define s second
#define eb emplace_back

map<pii,int> mp;
bitset<600005> ans;
vector<pii> qr[1<<21];
int n,p[600005],sz[600005];
stack<pii> st;
int fSet(int u){ return u==p[u]?u:fSet(p[u]); }
void uSet(int &U,int &V){
  if(U==V) return;
  if(sz[U]>sz[V]) swap(U,V);
  p[U]=V;
  sz[V]+=sz[U];
  st.emplace(U,V);
}
void add(int i,int il,int ir,int l,int r,int u,int v){
  if(il>r||ir<l) return;
  if(l<=il&&ir<=r) return void(qr[i].eb(u,v));
  int mid=il+ir>>1;
  add(i<<1,il,mid,l,r,u,v), add(i<<1|1,mid+1,ir,l,r,u,v);
}
void play(int i,int il,int ir){
  int sz0=st.size();
  for(auto &[u,v]:qr[i]){
    int u1=fSet(u),u2=fSet(u+n),v1=fSet(v),v2=fSet(v+n);
    uSet(u1,v2), uSet(u2,v1);
    if(p[u1]==p[u2]||p[v1]==p[v2]){
      while(st.size()!=sz0) p[st.top().f]=st.top().f, sz[st.top().s]-=sz[st.top().f], st.pop();
      return;
    }
  }
  if(il==ir) ans[il]=1;
  else{
    int mid=il+ir>>1;
    play(i<<1,il,mid), play(i<<1|1,mid+1,ir);
  }
  while(st.size()!=sz0) p[st.top().f]=st.top().f, sz[st.top().s]-=sz[st.top().f], st.pop();
}

signed main(){
  ios::sync_with_stdio(false); cin.tie(0);
  int m; cin>>n>>m;
  for(int i=1;i<=n<<1;++i) p[i]=i,sz[i]=1;
  for(int i=1;i<=m;++i){
    int t,u,v; cin>>t>>u>>v;
    if(u>v) swap(u,v);
    if(t) mp[{u,v}]=i;
    else add(1,1,m,mp[{u,v}],i-1,u,v), mp.erase({u,v});
  }
  for(auto &[a,b]:mp) add(1,1,m,b,m,a.f,a.s);
  play(1,1,m);
  for(int i=1;i<=m;++i) cout<<(ans[i]?"yes\n":"no\n");
}

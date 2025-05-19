#include<bits/stdc++.h>
using namespace std;
using ll=long long;

int p0[200005],p[200005],f[200005][2];
int fSet(int u){ return p[u]==u ? u : p[u]=fSet(p[u]); }

struct A{
  int u;
  ll f0,f1;
  A(int u,ll f0,ll f1):u(u),f0(f0),f1(f1){}
  bool operator<(const A &o)const{
    return f1*o.f0 > f0*o.f1;
  }
};
priority_queue<A> pq;

int main(){
  ios::sync_with_stdio(false); cin.tie(0);

  int n; cin>>n;
  for(int i=2;i<=n;++i) cin>>p0[i];
  for(int i=1;i<=n;++i){
    int x; cin>>x;
    f[i][x]=1;
    p[i]=i;
    if(i!=1) pq.emplace(i,f[i][0],f[i][1]);
  }
  ll ans=0;
  while(!pq.empty()){
    A u=pq.top(); pq.pop();
    if(f[u.u][0]!=u.f0 || f[u.u][1]!=u.f1) continue;
    int v = fSet(p0[u.u]);
    ans += (ll)f[v][1]*f[u.u][0];
    f[v][0] += f[u.u][0];
    f[v][1] += f[u.u][1];
    p[u.u] = v;
    if(v!=1) pq.emplace(v,f[v][0],f[v][1]);
  }
  cout<<ans;
}
#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using db=double;
using ld=long double;
using pii=pair<int,int>;
#define f first
#define s second
#define eb emplace_back
#define sz(x) (int)x.size()
template<class T> T chmn(T &x,T y){ return x=min(x,y); }
template<class T> T chmx(T &x,T y){ return x=max(x,y); }
const db eps=1e-6;

pii blacks[]={};

const int md=998244353, G=3;

ll Pow(ll a,ll b){
  ll res=1;
  for(;b>0;b>>=1,a=(a*a)%md) if(b&1) res=(res*a)%md;
  return res;
}

void ntt(vector<ll> &a,bool inv){
  int n = sz(a);
  static vector<int> rev;
  static vector<ll> rt{0,1};
  if(sz(rev)!=n){
    int k = __builtin_ctz(n);
    rev.assign(n,0);
    for(int i=0;i<n;++i) rev[i] = (rev[i>>1]>>1) | ((i&1)<<(k-1));
  }
  if(sz(rt)<n){
    int k = __builtin_ctz(sz(rt));
    rt.resize(n);
    while((1<<k)<n){
      ll z = Pow(G, (md-1)>>(k+1));
      for(int i=1<<(k-1);i<(1<<k);++i){
        rt[i<<1] = rt[i];
        rt[i<<1|1] = (rt[i]*z)%md;
      }
      ++k;
    }
  }
  for(int i=0;i<n;++i) if(i<rev[i]) swap(a[i], a[rev[i]]);
  for(int len=1;len<n;len<<=1){
    for(int i=0;i<n;i+=(len<<1)){
      for(int j=0;j<len;++j){
        ll u = a[i+j];
        ll v = (a[i+j+len]*rt[len+j])%md;
        a[i+j] = (u+v)%md;
        a[i+j+len] = (u-v+md)%md;
      }
    }
  }
  if(inv){
    reverse(a.begin()+1,a.end());
    ll inv_n=Pow(n,md-2);
    for(auto &e:a) e=(e*inv_n)%md;
  }
}

vector<ll> a[200],b[200],c[400];
ll f[2000000];

void solve(){
  int k; cin>>k;
  int s=1;
  while(s < 2*k-1) s<<=1;
  for(int i=0;i<200;++i){
    a[i].resize(s);
    for(int j=0;j<k;++j) cin>>a[i][j];
  }
  for(int i=0;i<200;++i){
    b[i].resize(s);
    for(int j=0;j<k;++j) cin>>b[i][j];
  }
  for(int i=0;i<400;++i){
    c[i].resize(s);
    for(int j=0;j<k;++j){
      cin>>c[i][j];
      if(i!=0) c[i-1][j+k]=c[i][j];
    }
  }
  for(int i=0;i<200;++i) ntt(a[i],0);
  for(int i=0;i<200;++i) ntt(b[i],0);
  for(int i=0;i<400;++i) ntt(c[i],1);
  ll ans=0;
  for(auto &[i,j]:blacks){
    for(int l=0;l<s;++l) ans+=(((a[i][l]*b[j][l])%md)*c[i+j][l])%md, ans%=md;
  }
  cout<<ans;
}

int main(){
  ios::sync_with_stdio(false); cin.tie(0);

  int Q(1);
  // cin>>Q;
  while(Q--) solve();
}
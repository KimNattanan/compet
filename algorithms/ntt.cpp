#include <bits/stdc++.h>
using namespace std;
using ll=long long;
#define sz(x) (int)x.size()

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

vector<ll> multiply(vector<ll> &a,vector<ll> &b){
  int sz = 1;
  while(sz < sz(a)+sz(b)-1) sz<<=1;
  vector<ll> fa(sz),fb(sz);
  for(int i=0;i<sz(a);++i) fa[i]=a[i];
  for(int i=0;i<sz(b);++i) fb[i]=b[i];
  ntt(fa,0), ntt(fb,0);
  for(int i=0;i<sz;++i) fa[i]=(fa[i]*fb[i])%md;
  ntt(fa,1);
  fa.erase(fa.begin()+sz(a)+sz(b)-1,fa.end());
  return fa;
}
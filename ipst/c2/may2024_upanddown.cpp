#include "upanddown.h"
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

struct persist{
  struct node{
    node *l,*r;
    int t;
    node(int x=0):l(nullptr),r(nullptr),t(x){}
  };
  using pnode=node*;
  vector<pnode> rt;
  int l0,r0;
  void init(int n,int l,int r){
    rt.resize(n);
    l0=l,r0=r;
    build(rt[0],l,r);
  }
  void build(pnode &t,int il,int ir){
    t=new node();
    if(il==ir) return;
    int mid=il+ir>>1;
    build(t->l,il,mid), build(t->r,mid+1,ir);
  }
  void upd(pnode t0,pnode &t1,int il,int ir,int id,int x){
    t1=new node(*t0);
    ++(t1->t);
    if(il==ir) return;
    int mid=il+ir>>1;
    if(id<=mid) upd(t0->l,t1->l,il,mid,id,x);
    else upd(t0->r,t1->r,mid+1,ir,id,x);
  }
  void upd(int t0,int t1,int id,int x){ upd(rt[t0],rt[t1],l0,r0,id,x); }
  int qr(pnode t0,pnode t1,int il,int ir,int l,int r){
    if(il>r||ir<l) return 0;
    if(l<=il&&ir<=r) return t1->t - t0->t;
    int mid=il+ir>>1;
    return qr(t0->l,t1->l,il,mid,l,r) + qr(t0->r,t1->r,mid+1,ir,l,r);
  }
  int qr(int t0,int t1,int l,int r){ return qr(rt[t0],rt[t1],l0,r0,l,r); }
}t;
vector<int> comp;
int xid[200005];

struct fenwick{
  vector<ll> bit;
  ll sum;
  void init(int n){ bit.assign(n,0); sum=0; }
  void upd(int i,ll x){ for(++i;i<sz(bit);i+=i&-i) Add(bit[i],x); Add(sum,x); }
  ll qr(int i){
    ll res=0;
    for(++i;i>0;i-=i&-i) Add(res,bit[i]);
    return res;
  }
}dp[5];

ll upanddown(int N,vector<int> X){
  comp=X;
  sort(comp.begin(),comp.end());
  comp.erase(unique(comp.begin(),comp.end()),comp.end());
  for(int i=0;i<N;++i) xid[i] = upper_bound(comp.begin(),comp.end(),X[i])-comp.begin();
  vector<int> nds(N);
  iota(nds.begin(),nds.end(),0);
  sort(nds.begin(),nds.end(),[&](const int &l,const int &r){
    return X[l]!=X[r] ? X[l]<X[r] : l<r;
  });
  t.init(sz(comp)+5,0,N-1);
  int prv=0;
  for(auto &i:nds){
    t.upd(prv,xid[i],i,1);
    prv=xid[i];
  }
  ll ans=0,sum1,sum2;
  prv=-1;
  for(auto &i:nds){
    if(prv==-1 || xid[i]!=xid[prv]) sum1=sum2=0;
    else{
      ll x1 = t.qr(xid[i],sz(comp),prv,i);
      ll x2 = t.qr(0,xid[i]-1,0,prv);
      ll x3 = t.qr(0,xid[i]-1,i,N-1);
      Add(sum1,x2);
      Add(sum2,mul(x1,sum1));
      Add(ans,mul(sum2,x3));
    }
    prv=i;
  }
  for(int i=0;i<5;++i) dp[i].init(sz(comp)+5);
  for(int i=0;i<N;++i){
    dp[4].upd(xid[i], dp[3].sum-dp[3].qr(xid[i]));
    dp[3].upd(xid[i], dp[2].sum-dp[2].qr(xid[i]));
    dp[2].upd(xid[i], dp[1].qr(xid[i]-1));
    dp[1].upd(xid[i], dp[0].qr(xid[i]-1));
    dp[0].upd(xid[i], 1);
  }
  return add(dp[4].sum,-ans);
}

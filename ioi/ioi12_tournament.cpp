#include<bits/stdc++.h>
using namespace std;
using pii=pair<int,int>;
#define eb emplace_back
using ll=long long;
#define f first
#define s second

mt19937 rng(time(nullptr));

struct info{
  int vL,vR,mn,mx;
  info():vL(1e9),vR(-1),mn(1e9),mx(-1){}
  info(int vL,int vR):vL(vL),vR(vR),mn(vL),mx(vR){}
};
struct treap{
  struct node{
    int sz,prio;
    info val;
    node *l,*r;
    node(info val):sz(1),val(val),prio(rng()),l(nullptr),r(nullptr){}
  };
  using pnode=node*;
  pnode rt;
  int sz(pnode t){return t?t->sz:0;}
  info val(pnode t){return t?t->val:info();}
  void upd(pnode t){
    if(!t) return;
    t->sz=sz(t->l)+1+sz(t->r);
    t->val.mn=min(val(t->l).mn,t->val.vL);
    t->val.mx=max(val(t->r).mx,t->val.vR);
  }
  void split(pnode t,pnode &l,pnode &r,int x){
    if(!t) return void(l=r=nullptr);
    if(sz(t->l)>=x) split(t->l,l,t->l,x),r=t;
    else split(t->r,t->r,r,x-sz(t->l)-1),l=t;
    upd(t);
  }
  void merge(pnode &t,pnode l,pnode r){
    if(!l||!r) return void(t=l?l:r);
    if(l->prio>r->prio) merge(l->r,l->r,r),t=l;
    else merge(r->l,l,r->l),t=r;
    upd(t);
  }
  void init(int n){
    rt=nullptr;
    for(int i=0;i<n;++i) merge(rt,rt,new node(info(i,i)));
  }
  pii qr(int l,int r){
    pnode t1,t2,t3;
    split(rt,t1,t2,l-1);
    split(t2,t2,t3,r-l+1);
    pii ret(val(t2).mn,val(t2).mx);
    merge(rt,t1,new node(info(ret.f,ret.s)));
    merge(rt,rt,t3);
    return ret;
  }
}t;

int rm[100005],qs[100005];

int GetBestPosition(int N, int C, int R, int *K, int *S, int *E) {

  for(int i=N-2,cur=N+1;i>=0;--i){
    if(K[i]>R) cur=i;
    rm[i]=cur;
  }

  t.init(N);

  for(int i=0;i<C;++i){
    auto [l,r]=t.qr(S[i]+1,E[i]+1);
    if(rm[l]<r) continue;
    ++qs[l],--qs[r+1];
    // cerr<<l<<"-"<<r<<endl;
  }
  int ans=0,mx=qs[0];
  for(int i=1;i<N;++i){
    qs[i]+=qs[i-1];
    if(qs[i]>mx) mx=qs[i],ans=i;
  }
  return ans;

}

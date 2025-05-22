#include<bits/stdc++.h>
using namespace std;

mt19937 rng(time(0));

struct persistent_treap{
  struct node{
    node *l,*r;
    int prio,x,sz;
    node(int x=0):x(x),sz(1),l(nullptr),r(nullptr),prio(rng()){}
  };
  using pnode=node*;
  vector<pnode> rt;
  void init(int n){ rt.assign(n,nullptr); }
  int sz(pnode t){ return t ? t->sz : 0; }
  void upd(pnode t){
    if(!t) return;
    t->sz = sz(t->l) + 1 + sz(t->r);
  }
  void split(pnode t,pnode &l,pnode &r,int x){
    if(!t) return void(l=r=nullptr);
    t = new node(*t);
    if(sz(t->l)>=x) split(t->l,l,t->l,x), r=t;
    else split(t->r,t->r,r,x-sz(t->l)-1), l=t;
    upd(t);
  }
  void merge(pnode &t,pnode l,pnode r){
    if(!l||!r) return void(t=l?new node(*l):r?new node(*r):nullptr);
    if(l->prio > r->prio){
      t = new node(*l);
      merge(t->r,l->r,r);
    }
    else{
      t = new node(*r);
      merge(t->l,l,r->l);
    }
    upd(t);
  }
  void insert(int x,int y){ merge(rt[x],rt[x],new node(y)); }
};
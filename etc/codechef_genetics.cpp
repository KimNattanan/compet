#include<bits/stdc++.h>
using namespace std;

using A = array<int,4>;
mt19937 rng(time(0));
int idx[256];

struct persistent_treap{
  struct node{
    node *l,*r;
    int prio,x,sz;
    A f;
    node(int x=-1):x(x),f(A{0,0,0,0}),sz(1),l(nullptr),r(nullptr),prio(rng()){
      if(x!=-1) f[x]=1;
    }
  };
  using pnode=node*;
  vector<pnode> rt;
  void init(int n){
    rt.assign(n,nullptr);
  }
  int sz(pnode t){ return t ? t->sz : 0; }
  A f(pnode t){ return t ? t->f : A{0,0,0,0}; }
  void upd(pnode t){
    if(!t) return;
    t->sz = sz(t->l) + 1 + sz(t->r);
    A fl=f(t->l), fr=f(t->r);
    for(int i=0;i<4;++i) t->f[i] = fl[i] + fr[i];
    ++(t->f[t->x]);
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
  void insert(int t,string s){
    for(auto &e:s) merge(rt[t],rt[t],new node(idx[e]));
  }
  void mutate(int x,int k,char c){
    pnode t1(nullptr),t2(nullptr),t3(nullptr);
    split(rt[x],t1,t2,k-1);
    split(t2,t2,t3,1);
    merge(rt[x],t1,new node(idx[c]));
    merge(rt[x],rt[x],t3);
  }
  void cross(int x1,int x2,int k1,int k2,int y1,int y2){
    pnode t1,t2,t3,t4;
    split(rt[x1],t1,t2,k1);
    split(rt[x2],t3,t4,k2);
    merge(rt[y1],t1,t4);
    merge(rt[y2],t3,t2);
  }
  void count(int x,int l,int r){
    pnode t1,t2;
    split(rt[x],t1,t2,r);
    split(t1,t1,t2,l-1);
    for(int i=0;i<4;++i) cout<<(t2->f[i])<<" \n"[i==3];
  }
}t;

int main(){
  ios::sync_with_stdio(false); cin.tie(0);

  idx['A'] = 0;
  idx['G'] = 1;
  idx['T'] = 2;
  idx['C'] = 3;

  t.init(30025);

  int n; cin>>n;
  for(int i=1;i<=n;++i){
    string s; cin>>s;
    t.insert(i,s);
  }
  int Q; cin>>Q;
  while(Q--){
    string s; cin>>s;
    if(s=="MUTATE"){
      int x,k; cin>>x>>k;
      char c; cin>>c;
      t.mutate(x,k,c);
    }else if(s=="CROSS"){
      int x1,x2,k1,k2; cin>>x1>>x2>>k1>>k2;
      t.cross(x1,x2,k1,k2,n+1,n+2);
      n+=2;
    }else if(s=="COUNT"){
      int x,l,r; cin>>x>>l>>r;
      t.count(x,l,r);
    }
  } 
}
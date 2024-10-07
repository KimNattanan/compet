#include<bits/stdc++.h>
using namespace std;
using ll=long long;

const int MX_X=1e5;

mt19937 rng(911911911);

struct treap{
  struct node{
    node *l,*r;
    int prio,num,mn,mx;
    ll val;
    node(int num=0):num(num),mn(num),mx(num),l(nullptr),r(nullptr),prio(rng()),val(0){}
  };
  using pnode=node*;
  pnode rt;
  treap():rt(nullptr){}
  void upd(pnode t){
    if(!t) return;
    t->mn=t->mx=t->num;
    t->val=0;
    if(t->l){
      t->mn=t->l->mn;
      t->val+=t->l->val+1LL*t->l->mx*t->num;
    }
    if(t->r){
      t->mx=t->r->mx;
      t->val+=t->r->val+1LL*t->r->mn*t->num;
    }
  }
  void split(pnode t,pnode &l,pnode &r,int x){
    if(!t) return void(l=r=nullptr);
    if(t->num>x) split(t->l,l,t->l,x),r=t;
    else split(t->r,t->r,r,x),l=t;
    upd(t);
  }
  void merge(pnode &t,pnode l,pnode r){
    if(!l||!r) return void(t=l?l:r);
    if(l->prio>r->prio) merge(l->r,l->r,r),t=l;
    else merge(r->l,l,r->l),t=r;
    upd(t);
  }
  ll insert(int num){
    pnode t1,t2;
    split(rt,t1,t2,num);
    merge(rt,t1,new node(num));
    ll ret=rt->val;
    merge(rt,rt,t2);
    return ret;
  }
}t2;

struct line{
  ll m,c;
  line(ll m=0,ll c=-1e18):m(m),c(c){}
  template<class T> ll operator()(const T &x){ return m*x+c; }
};
struct lichao{
  line f[1<<18];
  ll lz[1<<18];
  void flush(int i,int il,int ir){
    if(il+1!=ir) lz[i<<1]+=lz[i], lz[i<<1|1]+=lz[i];
    f[i].c+=lz[i];
    lz[i]=0;
  }
  void add(int i,int il,int ir,line f2){
    flush(i,il,ir);
    if(il+1==ir) return void(f[i]= f[i](il)>f2(il) ? f[i] : f2);
    int mid=il+ir>>1;
    if(f[i].m>f2.m) swap(f[i],f2);
    if(f[i](mid)<f2(mid)){
      swap(f[i],f2);
      add(i<<1,il,mid,f2);
    }
    else add(i<<1|1,mid,ir,f2);
  }
  void add(line f2){ add(1,1,MX_X+1,f2); }
  void add(ll m,ll c){ add(1,1,MX_X+1,line(m,c)); }
  void lift(int i,int il,int ir,ll m,ll c){
    if(il==ir) return;
    flush(i,il,ir);
    int mid=il+ir>>1;
    if(f[i].m>=m) return lift(i<<1,il,mid,m,c);
    f[i].c+=c;
    if(il+1!=ir) lz[i<<1]+=c, lift(i<<1|1,mid,ir,m,c);
  }
  void lift(ll m,ll c){ lift(1,1,MX_X+1,m,c); }
  ll qr(int i,int il,int ir,int x){
    flush(i,il,ir);
    if(il+1==ir) return f[i](x);
    int mid=il+ir>>1;
    if(x<mid) return max(f[i](x),qr(i<<1,il,mid,x));
    return max(f[i](x),qr(i<<1|1,mid,ir,x));
  }
  ll qr(int x){ return qr(1,1,MX_X+1,x); }
}t;

int a[100005];
multiset<int> ms;

int main(){
  ios::sync_with_stdio(false); cin.tie(0);

  int n;
  cin>>n;
  for(int i=1;i<=n;i++) cin>>a[i];
  for(int i=1;i<=n;i++){
    ll l=-1,r=-1;
    auto itr=ms.upper_bound(a[i]);
    if(itr!=ms.end()) r=*itr;
    if(itr!=ms.begin()) --itr, l=*itr;
    if(l!=-1 && r!=-1) t.lift(-a[i],-l*r+l*a[i]+a[i]*r);
    else if(r!=-1) t.lift(-a[i],a[i]*r);
    t.add(-a[i],t2.insert(a[i])+1LL*a[i]*a[i]);
    ms.emplace(a[i]);
    if(i==1) continue;
    int x;
    cin>>x>>x;
    ll ans=t.qr(x);
    if(ans>0) ans+=*ms.begin()-1;
    cout<<max(0ll,ans/(*ms.begin()))<<'\n';
  }

}

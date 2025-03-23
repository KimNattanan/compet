#include "fence.h"
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
  pii t[1<<21];
  int l0,r0;
  void init(int l,int r){
    l0=l, r0=r;
    build(1,l0,r0);
  }
  void build(int i,int il,int ir){
    t[i]={-inf,-1};
    if(il==ir) return;
    int mid=il+ir>>1;
    build(i<<1,il,mid), build(i<<1|1,mid+1,ir);
  }
  void upd(int i,int il,int ir,int id,pii x){
    if(id<il||id>ir) return;
    if(il==ir) return void(t[i]=x);
    int mid=il+ir>>1;
    if(id<=mid) upd(i<<1,il,mid,id,x);
    else upd(i<<1|1,mid+1,ir,id,x);
    t[i]=max(t[i<<1],t[i<<1|1]);
  }
  void upd(int id,pii x){ upd(1,l0,r0,id,x); }
  pii qr(int i,int il,int ir,int y0,int y1){
    if(t[i].f<=y1 || il>=y0) return {-inf,-1};
    int mid=il+ir>>1;
    if(ir<y0){
      if(il==ir) return t[i];
      if(t[i<<1|1].f>y1) return qr(i<<1|1,mid+1,ir,y0,y1);
      return qr(i<<1,il,mid,y0,y1);
    }
    pii v=qr(i<<1|1,mid+1,ir,y0,y1);
    if(v.s!=-1) return v;
    return qr(i<<1,il,mid,y0,y1);
  }
  int qr(int y0,int y1){ return qr(1,l0,r0,y0,y1).s; }
}t;

struct E{
  int x,y0,y1,mode,id;
  E(int x,int y0,int y1,int mode,int id):x(x),y0(y0),y1(y1),mode(mode),id(id){}
  bool operator<(const E &o)const{
    if(x!=o.x) return x<o.x;
    return mode>o.mode;
  }
};

int h[400005],n;
vector<int> adj[400005];
int p[400005][25],lv[400005];
ll qs[400005];

void dfs(int u){
  for(int i=1;i<=21;++i) p[u][i]=p[p[u][i-1]][i-1];
  qs[u]=qs[p[u][0]]+h[u];
  lv[u]=lv[p[u][0]]+1;
  for(auto &v:adj[u]){
    p[v][0]=u;
    dfs(v);
  }
}
int LCA(int u,int v){
  if(lv[u]>lv[v]) swap(u,v);
  for(int i=21;i>=0;--i) if(lv[p[v][i]]>=lv[u]) v=p[v][i];
  if(u==v) return u;
  for(int i=21;i>=0;--i) if(p[u][i]!=p[v][i]) u=p[u][i], v=p[v][i];
  return p[u][0];
}


void init(int N, 
          int M, 
          std::vector<std::vector<int>> LL, 
          std::vector<std::vector<int>> UR, 
          std::vector<int> H, 
          std::vector<std::vector<int>> P) {   
  //Fill your code here
  vector<int> Y;
  for(int i=0;i<N;++i) Y.eb(LL[i][1]), Y.eb(UR[i][1]);
  for(int i=0;i<M;++i) Y.eb(P[i][1]);
  sort(Y.begin(),Y.end());
  Y.erase(unique(Y.begin(),Y.end()),Y.end());
  t.init(0,sz(Y));
  

  vector<E> ev;
  for(int i=0;i<N;++i){
    ev.eb(LL[i][0],LL[i][1],UR[i][1],1,i);
    ev.eb(UR[i][0],LL[i][1],UR[i][1],-1,i);
  }
  for(int i=0;i<M;++i){
    ev.eb(P[i][0],P[i][1],P[i][1],1,N+i);
    ev.eb(P[i][0],P[i][1],P[i][1],-1,N+i);
  }
  sort(ev.begin(),ev.end());
  for(int i=0;i<N;++i) h[i]=H[i];
  for(auto &[x,y0,y1,mode,id]:ev){
    y0=lower_bound(Y.begin(),Y.end(),y0)-Y.begin();
    y1=lower_bound(Y.begin(),Y.end(),y1)-Y.begin();
    if(mode==1){
      t.upd(y0,{y1,id});
    }
    else{
      int res=t.qr(y0,y1);
      int p = (res==-1 ? N+M : res);
      adj[p].eb(id);
      t.upd(y0,{-inf,-1});
    }
  }
  p[N+M][0]=N+M;
  dfs(N+M);
  n=N;
}

long long ask(int A, int B) {
  //Fill your code here
  return qs[A+n]+qs[B+n]-2*qs[LCA(A+n,B+n)];
}

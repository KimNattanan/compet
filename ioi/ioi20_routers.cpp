#include "routers.h"
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

int ask(int x){
  return use_detector(x);
}

int lm[1005],rm[1005];

void play(int il,int ir,int l,int r){
  if(l==r) return chmn(lm[l],il), chmx(rm[l],ir), void();
  if(il+1==ir) return rm[l]=il, lm[r]=ir, void();
  int mid=il+ir>>1;
  int x=ask(mid);
  play(il,mid,l,x), play(mid,ir,x,r);
}

std::vector<int> find_routers(int L, int n, int q) {
  fill(lm,lm+n,L);
  play(0,L,0,n-1);
  vector<int> p(n);
  for(int i=1;i<n;++i) p[i]=2*rm[i-1]-p[i-1];
  return p;
}

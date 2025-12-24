#include<bits/stdc++.h>
using namespace std;
using ll=long long;
#define eb emplace_back
#define sz(x) (int)x.size()

struct Line{
  ll m,c;
  Line(ll m=0,ll c=-1e18):m(m),c(c){}
  template<class T> ll operator()(const T &x){ return m*x+c; }
};
struct Cht{
  deque<Line> dq;
  bool check(Line f1,Line f2,Line f3){
    if(f2.m==f3.m) return f2.c>=f3.c;
    return (f2.c-f1.c)*(f2.m-f3.m) < (f3.c-f2.c)*(f1.m-f2.m);
  }
  void add(Line f){
    while(dq.size()>1 && check(dq.end()[-2],dq.back(),f)) dq.pop_back();
    if(dq.empty() || dq.back().m!=f.m || dq.back().c<f.c) dq.eb(f);
  }
  void add(ll m,ll c){ add(Line(m,c)); }
  ll qr(ll x){
    if(dq.empty()) return -1e18;
    int l=0,r=sz(dq)-1;
    while(l<r){
      int mid=l+r>>1;
      if(dq[mid](x)<dq[mid+1](x)) l=mid+1;
      else r=mid;
    }
    return dq[l](x);
  }
  void clear(){ dq.clear(); }
}cht;
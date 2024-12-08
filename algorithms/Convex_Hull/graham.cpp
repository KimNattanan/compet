#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using P=pair<ll,ll>;
#define f first
#define s second
#define eb emplace_back

vector<P> getCvh(vector<P> v){
  int n=v.size();
  if(n<=3) return v;
  for(int i=1;i<n;++i) if(v[i].s<v[0].s) swap(v[i],v[0]);
  sort(v.begin()+1,v.end(),[&](const P &l,const P &r){
    if((l.f<v[0].f) ^ (r.f<v[0].f)) return r.f<v[0].f;
    ll xl=l.f-v[0].f, yl=l.s-v[0].s, xr=r.f-v[0].f, yr=r.s-v[0].s;
    if(yl*xr != yr*xl) return yl*xr < yr*xl;
    return xl*xl+yl*yl < xr*xr+yr*yr;
  });
  auto ch=[&](P p1,P p2,P p3){
    ll val = (p2.s-p1.s)*(p3.f-p2.f) - (p2.f-p1.f)*(p3.s-p2.s);
    return val==0 ? 0 : (val<0 ? -1 : 1);
  };
  vector<P> cv({v[0],v[1],v[2]});
  for(int i=3;i<n;++i){
    while(cv.size()>2 && ch(cv.end()[-2],cv.back(),v[i])==1) cv.pop_back();
    cv.eb(v[i]);
  }
  return cv;
}

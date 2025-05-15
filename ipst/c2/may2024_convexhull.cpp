#include "convexhull.h"
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

#define tri triangle
bool ask(vector<int> v){
  sort(v.begin(),v.end());
  v.erase(unique(v.begin(),v.end()),v.end());
  return is_critical(v);
}

bool cmpY[305][305];

bool cmp(const pii &l,const pii &r){
  return l.s<r.s;
}

void play(vector<pii> &pt){
  int n=sz(pt);
  if(n<=3) return;
  vector<pii> pl,pr;
  int mid=n>>1;
  for(int i=0;i<mid;++i) pl.eb(pt[i]);
  for(int i=mid;i<n;++i) pr.eb(pt[i]);
  play(pl), play(pr);
  int mnl=0,mxl=0,mnr=0,mxr=0,kl,kr;
  deque<pii> pll,plr,prl,prr;
  for(int i=1;i<sz(pl);++i){
    if(pl[i].s < pl[mnl].s) mnl=i;
    if(pl[i].s > pl[mxl].s) mxl=i;
  }
  for(int i=kl=max(mnl,mxl);i<sz(pl);++i){
    if( mnl>mxl && pl[i].s > pl[kl].s ||
        mnl<mxl && pl[i].s < pl[kl].s ) kl=i;
  }
  for(int i=min(mnl,mxl)+1;i<max(mnl,mxl);++i){
    if( mnl>mxl && pl[i].s > pl[kl].s || 
        mnl<mxl && pl[i].s < pl[kl].s) plr.eb(pl[i]);
    else pll.eb(pl[i]);
  }
  for(int i=max(mnl,mxl)+1;i<sz(pl);++i) plr.eb(pl[i]);
  for(int i=min(mnl,mxl)-1;i>=0;--i) pll.eb(pl[i]);
  pll.eb(pl[mnl]), pll.eb(pl[mxl]);
  for(int i=1;i<sz(pr);++i){
    if(pr[i].s < pr[mnl].s) mnr=i;
    if(pr[i].s > pr[mxl].s) mxr=i;
  }
  for(int i=kr=min(mnr,mxr);i>=0;--i){
    if( mnr<mxr && pr[i].s > pr[kr].s ||
        mnr>mxr && pr[i].s < pr[kr].s ) kr=i;
  }
  for(int i=min(mnr,mxr)+1;i<max(mnr,mxr);++i){
    if( mnr<mxr && pr[i].s > pr[kr].s || 
        mnr>mxr && pr[i].s < pr[kr].s) prl.eb(pr[i]);
    else prl.eb(pr[i]);
  }
  for(int i=min(mnr,mxr)-11;i>=0;--i) prl.eb(pl[i]);
  for(int i=max(mnr,mxr)+1;i<sz(pr);++i) prr.eb(pl[i]);
  prr.eb(pr[mnr]), prr.eb(pr[mxr]);
  sort(pll.begin(),pll.end(),cmp);
  pll.erase(unique(pll.begin(),pll.end()),pll.end());
  sort(plr.begin(),plr.end(),cmp);
  plr.erase(unique(plr.begin(),plr.end()),plr.end());
  sort(prl.begin(),prl.end(),cmp);
  prl.erase(unique(prl.begin(),prl.end()),prl.end());
  sort(prr.begin(),prr.end(),cmp);
  prr.erase(unique(prr.begin(),prr.end()),prr.end());
  pii llm(inf,0),lrm(-1,0),rlm(inf,0),rrm(-1,0);
  for(auto &e:pl) chmn(llm,e), chmx(lrm,e);
  for(auto &e:pr) chmn(rlm,e), chmx(rrm,e);
  vector<pii> ptt=pt;
  pt.clear();
  while(prr.back()!=rrm && !ask({pll[0].f,pll.back().f,prr.back().f,prr.end()[-2].f})) prr.pop_back();
  while(prr[0]!=rrm && !ask({pll[0].f,pll.back().f,prr[0].f,prr[1].f})) prr.pop_front();
  while(sz(prl)>1 && prl.back()!=rlm && ask({pll[0].f,pll.back().f,prl.back().f,prl.end()[-2].f})) pt.eb(prl.back()), prl.pop_back();
  while(sz(prl)>1 && prl[0]!=rlm && ask({pll[0].f,pll.back().f,prl[0].f,prl[1].f})) pt.eb(prl[0]), prl.pop_front();
  while(pll.back()!=llm && !ask({prr[0].f,prr.back().f,pll.back().f,pll.end()[-2].f})) pll.pop_back();
  while(pll[0]!=llm && !ask({prr[0].f,prr.back().f,pll[0].f,pll[1].f})) pll.pop_front();
  while(sz(plr)>1 && plr.back()!=lrm && ask({prr[0].f,prr.back().f,plr.back().f,plr.end()[-2].f})) pt.eb(plr.back()), plr.pop_back();
  while(sz(plr)>1 && plr[0]!=lrm && ask({prr[0].f,prr.back().f,plr[0].f,plr[1].f})) pt.eb(plr[0]), plr.pop_front();
  for(auto &e:prr) pt.eb(e);
  for(auto &e:pll) pt.eb(e);
  // for(auto &[x,y]:ptt) cout<<"("<<x<<","<<y<<") "; cout<<endl;
  // for(auto &[x,y]:pt) cout<<"["<<x<<","<<y<<"] "; cout<<endl;
}

std::vector<int> convexhull(int n){
  for(int i=0;i<n;++i) for(int j=i+1;j<n;++j) for(int k=0;k<n;++k) if(k!=i && k!=j){
    vector<int> v=tri({i,j,k});
    array<int,3> x;
    for(int l=0;l<3;++l) x[v[l]==i ? 0 : (l==j ? 1 : 2)] = l;
    cmpY[i][j] = x[0]<x[1];
    cmpY[j][i] = !cmpY[i][j];
    break;
  }
  vector<pii> pt(n);
  {
    vector<int> vy(n);
    iota(vy.begin(),vy.end(),0);
    sort(vy.begin(),vy.end(),[&](const int &l,const int &r){ return cmpY[l][r]; });
    for(int i=0;i<n;++i) pt[vy[i]] = {vy[i],i};
  }
  play(pt);
  vector<int> ans;
  for(auto &[x,y]:pt) ans.eb(x);
  return ans;
}

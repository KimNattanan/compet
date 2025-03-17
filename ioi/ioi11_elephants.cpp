#include "elephants.h"
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using pii=pair<int,int>;
using i3=array<int,3>;
#define f first
#define s second
#define eb emplace_back
#define sz(x) (int)x.size()
#define add(x,y) ((x+y)%md)
#define Add(x,y) (x=add(x,y))
#define mul(x,y) ((x*y)%md)
#define Mul(x,y) (x=mul(x,y))
const int inf=1e9;
const ll linf=1e18;
const ll md=1e9+7;

int n,L,X_[150005],sq,upd_cnt;
vector<vector<i3>> dp;
multiset<pii> ms;

void init_block(vector<i3> &v){
  for(int r=sz(v), l=r-1; l>=0; --l){
    while(v[r-1][0]>=v[l][0]+L) --r;
    if(r==sz(v)) v[l][1]=1, v[l][2]=v[l][0]+L;
    else v[l][1]=1+v[r][1], v[l][2]=v[r][2];
  }
}
int get_ans(){
  int ans=0;
  for(int i=0, cur=0; i<sz(dp); ++i){
    auto val=lower_bound(dp[i].begin(),dp[i].end(),i3{cur,0,0});
    if(val!=dp[i].end()) ans+=(*val)[1], cur=(*val)[2];
  }
  return ans;
}

void init(int N, int L, int X[]){
  ++L;
  n=N, ::L=L, upd_cnt=0, sq=sqrt(n);
  dp.clear();
  if(ms.empty()) for(int i=0;i<n;++i) ms.emplace(X_[i]=X[i],i);
  for(auto &[x,i]:ms){
    if(dp.empty() || sz(dp.back())==sq) dp.eb(vector<i3>{});
    dp.back().eb(i3{x,0,0});
  }
  for(auto &e:dp) init_block(e);
}

int update(int i, int y){
  int y0=X_[i];
  X_[i]=y;
  ms.erase({y0,i}), ms.emplace(y,i);
  if(++upd_cnt==sq) init(n,L-1,X_);
  else{
    int cnt=0, prev=-1;
    for(auto &e:dp){
      int b0=(prev<y0 && y0<=e.back()[0]);
      int b1=(prev<y && y<=e.back()[0]);
      prev=e.back()[0];
      if(b0) e.erase(lower_bound(e.begin(),e.end(),i3{y0,0,0}));
      if(b1) e.insert(lower_bound(e.begin(),e.end(),i3{y,0,0}),i3{y,0,0});
      if(b0|b1) init_block(e);
      if(Add(cnt,add(b0,b1))==2) break;
    }
    if(cnt==1){
      dp.back().insert(lower_bound(dp.back().begin(),dp.back().end(),i3{y,0,0}),i3{y,0,0});
      init_block(dp.back());
    }
  }
  return get_ans();
}

#include "fish.h"
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using pii=pair<int,int>;
#define f first
#define s second
#define eb emplace_back

int N,M;
int X[300005],Y[300005],W[300005];

vector<pii> pos;
vector<pair<int,ll>> QS[300005];
vector<ll> dp[2];
int L[300005],R[300005];

ll qs(int x,int y){
  auto itr=upper_bound(QS[x].begin(),QS[x].end(),pair<int,ll>(y,LLONG_MAX));
  --itr;
  return itr->s;
}
pii getRange(int x,int y1,int y2){
  return pii(lower_bound(pos.begin()+L[x],pos.begin()+R[x]+1,pii(x,y1))-pos.begin(),
             upper_bound(pos.begin()+L[x],pos.begin()+R[x]+1,pii(x,y2))-pos.begin()-1);
}
struct segment{
  vector<segment> child;
  int l,r,mid;
  ll mx[3];
  segment(int l_=0,int r_=0):l(l_),r(r_),mid(l+(r-l>>1)){
    mx[0]=mx[1]=mx[2]=0;
  }
  void build(){
    if(l==r) return;
    child.eb(l,mid),child.eb(mid+1,r);
    child[0].build(),child[1].build();
  }
  void upd(int i,int z,ll x){
    if(l==r) return void(mx[z]=x);
    if(i<=mid) child[0].upd(i,z,x);
    else child[1].upd(i,z,x);
    mx[z]=max(child[0].mx[z],child[1].mx[z]);
  }
  ll qr(int z,int l0,int r0){
    if(l0<=l&&r<=r0) return mx[z];
    if(l>r0||r<l0) return 0;
    return max(child[0].qr(z,l0,r0),child[1].qr(z,l0,r0));
  }
}t;

long long max_weights(int N_, int M_, std::vector<int> X_, std::vector<int> Y_,
                      std::vector<int> W_) {
  N=N_,M=M_;
  for(int i=1;i<=M;++i) X[i]=X_[i-1]+1,Y[i]=Y_[i-1]+1,W[i]=W_[i-1];

  for(int i=1;i<=M;++i){
    QS[X[i]].eb(Y[i],W[i]);
    if(X[i]>1) pos.eb(X[i]-1,Y[i]);
    if(X[i]<N) pos.eb(X[i]+1,Y[i]);
  }
  for(int i=1;i<=N;++i){
    QS[i].eb(0,0);
    sort(QS[i].begin(),QS[i].end());
    for(int j=1;j<QS[i].size();++j) QS[i][j].s+=QS[i][j-1].s;
    pos.eb(i,0);
  }
  pos.eb(0,0);
  pos.eb(N+1,0);
  QS[0].eb(0,0);
  QS[N+1].eb(0,0);
  sort(pos.begin(),pos.end());
  pos.erase(unique(pos.begin(),pos.end()),pos.end());
  for(int i=0;i<pos.size();++i){
    if(!L[pos[i].f]) L[pos[i].f]=i;
    R[pos[i].f]=i;
  }
  t=segment(0,pos.size()-1);
  t.build();
  dp[0]=dp[1]=vector<ll>(pos.size());

  int l,r;
  for(int i=1;i<pos.size();++i){
    auto &[x,y]=pos[i];
    tie(l,r)=getRange(x-1,0,y-1);
    if(l<=r) dp[0][i]=t.qr(1,l,r)+qs(x-1,y);
    if(i>3){
      tie(l,r)=getRange(x-2,0,y-1);
      if(l<=r) dp[0][i]=max(dp[0][i],t.qr(0,l,r)+qs(x-1,y));
    }

    tie(l,r)=getRange(x-1,y,N);
    if(l<=r) dp[1][i]=t.qr(2,l,r)-qs(x,y);
    if(i>2){
      tie(l,r)=getRange(x-2,y,N);
      if(l<=r) dp[1][i]=max(dp[1][i],t.qr(2,l,r));
    }
    if(i+1<pos.size()){
      t.upd(i,0,max(dp[0][i],dp[1][i]));
      t.upd(i,1,dp[0][i]-qs(x,y));
      t.upd(i,2,max(dp[0][i],dp[1][i])+qs(x+1,y));
    }
  }

  return dp[1].back();

//   /*
//   0: 0,1: qrz_1: dp[i][k][z]
//   1: 2:   qr0_2: dp[i][k][0]-qs[i][k]
//   2: 3,4: qrz_3: dp[i][k][z]+qs[i+1][k]
//   */

}

#include <bits/stdc++.h>
#include "cake.h"
using namespace std;
using ll=long long;
using pii=pair<int,int>;
#define f first
#define s second

pair<ll,int> dp[100005];
vector<int> X,Y;
int N;

pair<ll,int> f(int l,int r,ll C){
  return {dp[l].f+C+1LL*(X[r]-X[l])*(Y[r]-Y[l]),dp[l].s+1};
}

void cal(ll C){
  deque<pii> dq;
  dq.emplace_back(1,0);
  for(int i=1;i<N;++i){
    while(dq.size()>1&&dq[1].f==i) dq.pop_front();
    dp[i]=f(dq.front().s,i,C);
    while(dq.size()>1&&f(dq.back().s,dq.back().f,C)>=f(i,dq.back().f,C)) dq.pop_back();
    int l=max(i+1,dq.back().f),r=N;
    while(l<r){
      int mid=l+r>>1;
      if(f(dq.back().s,mid,C)>=f(i,mid,C)) r=mid;
      else l=mid+1;
    }
    if(l!=N) dq.emplace_back(l,i);
  }
}

long long whipped_cream_price(int N, int M, std::vector<int> X, std::vector<int> Y) {
  ::X=X,::Y=Y,::N=N;
  ll l=0,r=1LL*(X[N-1]-X[0])*(Y[N-1]-Y[0]);
  while(l<r){
    ll mid=l+r>>1;
    cal(mid);
    if(dp[N-1].s>M) l=mid+1;
    else r=mid;
  }
  cal(l);
  return dp[N-1].f-l*M;
}

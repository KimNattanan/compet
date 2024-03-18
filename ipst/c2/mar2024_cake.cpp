#include <bits/stdc++.h>
using namespace std;
#include "cake.h"
using ll=long long;
#define sz(x) (int)(x).size()
#define eb emplace_back
using pii=pair<int,int>;
#define f first
#define s second

ll X[100005],Y[100005];
int n;
pair<ll,int> dp[100005];

pair<ll,int> f(int l,int r,ll pnt){
  return {dp[l].f+(X[r]-X[l])*(Y[r]-Y[l])+pnt,dp[l].s+1};
}

void cal(ll pnt){
  deque<pii> dq;
  dp[1]={0,0};
  dq.eb(2,1);
  for(int i=2;i<=n;++i){
    while(sz(dq)>1&&dq[1].f<=i) dq.pop_front();
    dp[i]=f(dq.front().s,i,pnt);
    while(sz(dq)&&dq.back().f>i&&f(dq.back().s,dq.back().f,pnt)>=f(i,dq.back().f,pnt)) dq.pop_back();
    if(dq.empty()) dq.eb(i+1,i);
    else{
      int l=max(i+1,dq.back().f),r=n+1;
      while(l<r){
        int mid=l+r>>1;
        if(f(dq.back().s,mid,pnt)>=f(i,mid,pnt)) r=mid;
        else l=mid+1;
      }
      if(l<=n) dq.eb(l,i);
    }
  }
}

long long whipped_cream_price(int N, int M, std::vector<int> X, std::vector<int> Y) {
  // write your code here
  n=N;
  for(int i=1;i<=N;++i) ::X[i]=X[i-1], ::Y[i]=Y[i-1];

  ll l=-1e10,r=1LL*(X[n-1]-X[0])*(Y[n-1]-Y[0]);
  while(l<r){
    ll mid=l+r>>1;
    cal(mid);
    if(dp[n].s>M) l=mid+1;
    else r=mid;
  }
  cal(l);
  return dp[n].f-l*M;
}
/*
5 2
1 2
3 3
4 5
6 9
8 10
*/

#include "fish.h"
#include<bits/stdc++.h>
using namespace std;
using ll=long long;

int N,M;
int X[300005],Y[300005],W[300005],W2[100005];
ll dp[100005][3];

long long max_weights(int N_, int M_, std::vector<int> X_, std::vector<int> Y_,
                      std::vector<int> W_) {
  N=N_,M=M_;
  for(int i=1;i<=M;++i) X[i]=X_[i-1],Y[i]=Y_[i-1],W[i]=W_[i-1];

  for(int i=1;i<=M;++i) W2[X[i]]=W[i];
  for(int i=0;i<=N;++i){
    dp[i][1]=dp[i][2]=-1e18;
  }
  for(int i=1;i<=N;++i){
    dp[i][0]=max({dp[i-1][0],dp[i-1][1],dp[i-1][2]});
    dp[i][1]=W2[i]+dp[i-1][0];
    if(i>2&&i<N) dp[i][2]=W2[i]+dp[i-1][1];
  }
  return max(dp[N][0],dp[N][1]);

}

#include "fish.h"
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
 
int N,M;
int X[300005],Y[300005],W[300005];
int W2[305][305];
ll qs[305][305],dp[305][305][3];
 
long long max_weights(int N_, int M_, std::vector<int> X_, std::vector<int> Y_,
                      std::vector<int> W_) {
  N=N_,M=M_;
  for(int i=1;i<=M;++i) X[i]=X_[i-1]+1,Y[i]=Y_[i-1]+1,W[i]=W_[i-1];
 
  for(int i=1;i<=M;++i) W2[X[i]][Y[i]]=W[i];
  for(int i=1;i<=N;++i) for(int j=1;j<=N;++j) qs[i][j]=qs[i][j-1]+W2[i][j];
 
  for(int i=1;i<=N;++i) dp[0][i][0]=dp[0][i][1]=-1e18;
 
  for(int i=1;i<=N+1;++i){
    for(int j=0;j<=N;++j){
      for(int k=0;k<j;++k){
        dp[i][j][0]=max(dp[i][j][0],dp[i-1][k][0]+qs[i-1][j]-qs[i-1][k]);
        if(i>3) dp[i][j][0]=max(dp[i][j][0],dp[i-2][k][0]+qs[i-1][j]),
                dp[i][j][0]=max(dp[i][j][0],dp[i-2][k][1]+qs[i-1][j]);
      }
      for(int k=j;k<=N;++k){
        dp[i][j][1]=max(dp[i][j][1],dp[i-1][k][1]+qs[i][k]-qs[i][j]);
        dp[i][j][1]=max(dp[i][j][1],dp[i-1][k][0]+qs[i][k]-qs[i][j]);
        if(i>2) dp[i][j][1]=max(dp[i][j][1],dp[i-2][k][1]+qs[i-1][k]),
                dp[i][j][1]=max(dp[i][j][1],dp[i-2][k][0]+qs[i-1][k]);
      }
    }
  }
  return dp[N+1][0][1];
 
}

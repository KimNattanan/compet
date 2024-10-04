#include "mosaic.h"
#include<bits/stdc++.h>
using namespace std;
using ll=long long;

const int K=3;
ll a[K+5][200005],b[200005][K+5],_qs1[500000],_qs2[500000];
auto qs1=_qs1+250000, qs2=_qs2+250000;

std::vector<long long> mosaic(std::vector<int> X, std::vector<int> Y,
                              std::vector<int> T, std::vector<int> B,
                              std::vector<int> L, std::vector<int> R) {
  int Q=T.size(), n=X.size();
  vector<ll> ans(Q,0);
  
  if(n<=K){
    for(int i=1;i<=n;++i) a[1][i]=X[i-1], a[i][1]=Y[i-1];
    for(int i=2;i<=n;++i) for(int j=2;j<=n;++j) a[i][j]=!(a[i-1][j]|a[i][j-1]);
    for(int i=1;i<=n;++i) for(int j=1;j<=n;++j) a[i][j]+=a[i-1][j]+a[i][j-1]-a[i-1][j-1];
    for(int q=0;q<Q;++q) ans[q]=a[B[q]+1][R[q]+1]-a[B[q]+1][L[q]]-a[T[q]][R[q]+1]+a[T[q]][L[q]];
    return ans;
  }

  for(int i=1;i<=n;++i) a[1][i]=X[i-1], b[i][1]=Y[i-1];
  for(int i=1;i<=K;++i) a[i][1]=Y[i-1], b[1][i]=X[i-1];
  for(int i=2;i<=K;++i) for(int j=2;j<=n;++j) a[i][j]=!(a[i-1][j]|a[i][j-1]);
  for(int i=2;i<=n;++i) for(int j=2;j<=K;++j) b[i][j]=!(b[i-1][j]|b[i][j-1]);
  for(int i=K;i<=n;++i) qs1[i-K]=a[K][i], qs1[K-i]=b[i][K];
  for(int i=-n;i<=n;++i) qs1[i]+=qs1[i-1];
  for(int i=-n;i<=n;++i) qs2[i]=qs1[i]+qs2[i-1];
  for(int i=1;i<=K;++i) for(int j=1;j<=n;++j) a[i][j]+=a[i-1][j]+a[i][j-1]-a[i-1][j-1];
  for(int i=1;i<=n;++i) for(int j=1;j<=K;++j) b[i][j]+=b[i-1][j]+b[i][j-1]-b[i-1][j-1];
  for(int q=0;q<Q;++q){
    ++T[q],++L[q],++B[q],++R[q];
    if(B[q]<=K) ans[q]=a[B[q]][R[q]]-a[B[q]][L[q]-1]-a[T[q]-1][R[q]]+a[T[q]-1][L[q]-1];
    else if(R[q]<=K) ans[q]=b[B[q]][R[q]]-b[B[q]][L[q]-1]-b[T[q]-1][R[q]]+b[T[q]-1][L[q]-1];
    else{
      if(T[q]<=K) ans[q]+=a[K][R[q]]-a[K][L[q]-1]-a[T[q]-1][R[q]]+a[T[q]-1][L[q]-1], T[q]=K+1;
      if(L[q]<=K) ans[q]+=b[B[q]][K]-b[T[q]-1][K]-b[B[q]][L[q]-1]+b[T[q]-1][L[q]-1], L[q]=K+1;
      array<int,4> ids{L[q]-B[q],L[q]-T[q],R[q]-B[q],R[q]-T[q]};
      sort(ids.begin(),ids.end());
      auto [i1,i2,i3,i4]=ids;
      ans[q]+=qs2[i4]-qs2[i3-1]-qs2[i2-1]+qs2[i1-2];
    }
  }

  return ans;
}

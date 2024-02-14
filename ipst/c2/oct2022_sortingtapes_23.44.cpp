#include <bits/stdc++.h>
#include "sortingtapes.h"
using namespace std;
#define eb emplace_back
#define sz(x) (int)(x).size()

template<class Compare>
struct fenwick{
  Compare cmp;
  vector<int> bit;
  int v0;
  fenwick(int n=0,int x=0){init(n,x);}
  void init(int n,int x=0){
    bit.assign(n,x);
    v0=x;
  }
  void upd(int i,int x){
    for(;i<bit.size();i+=i&-i) bit[i]=cmp(x,bit[i])?x:bit[i];
  }
  int qr(int i){
    int ret=v0;
    for(;i>0;i-=i&-i) ret=cmp(bit[i],ret)?bit[i]:ret;
    return ret;
  }
};

int id1[100005],id2[100005],ub[100005];

std::vector<int> sort_tapes(int N, std::vector<int> A, std::vector<int> B) {

  if(N>30000){
    int l=0,r=0;
    vector<int> C;
    while(l<N&&r<N){
      if(compare(A[l],B[r])) C.eb(A[l++]);
      else C.eb(B[r++]);
    }
    while(l<N) C.eb(A[l++]);
    while(r<N) C.eb(B[r++]);
    return C;
  }

  fenwick<greater<int>> fw1(N+5,0);
  fenwick<less<int>> fw2(N+5,N);

  int last=-1;

  auto play=[&](int i){
    int mn=fw1.qr(id1[i]+1);
    int mx=fw2.qr(N-id1[i]+1);
    vector<int> vec;
    int L,R;
    for(int j=mn;j<mx;++j){
      if(j==mn) L=R=B[j];
      else L=min(L,B[j]),R=max(R,B[j]);
      vec.eb(B[j]);
    }
    int ans=mx;
    if(vec.size()){
      if(abs(L-last)<abs(R-last)) sort(vec.begin(),vec.end());
      else sort(vec.rbegin(),vec.rend());
      for(int j=0;j<sz(vec);++j){
        if(id2[vec[j]]>=ans) continue;
        if(compare(i,vec[j])) ans=min(ans,id2[vec[j]]);
        last=vec[j];
      }
    }
    ub[i]=ans;
    fw1.upd(id1[i]+1,ans);
    fw2.upd(N-id1[i]+1,ans);
  };

  for(int i=0;i<N;++i) id1[A[i]]=i, id2[B[i]]=i;
  for(int i=0;i<N;++i) play(i);

  int now=0;
  vector<int> C;
  for(int i=0;i<N;++i){
    for(;now<ub[A[i]];++now) C.eb(B[now]);
    C.eb(A[i]);
  }
  while(now<N) C.eb(B[now++]);

  return C;
}

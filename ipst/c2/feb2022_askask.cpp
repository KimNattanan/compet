#include "askask.h"
#include<bits/stdc++.h>
using namespace std;
#define eb emplace_back
using pii=pair<int,int>;

vector<int> sol1(int N){
  vector<vector<int>> Z;
  for(int i=1;i<N;i<<=1){
    vector<int> z;
    for(int j=0;j<N;j+=i+i){
      for(int k=j;k<j+i;++k) z.eb(k);
    }
    Z.eb(z);
  }
  reverse(Z.begin(),Z.end());
  vector<bool> res=analyse(Z);
  int l=0,r=N-1;
  int sz=N>>1;
  for(auto e:res){
    if(e) r-=sz;
    else l+=sz;
    sz>>=1;
  }
  return {l,l};
}

int f(int a,int b){return a<<3|b;}
int f(pii x){return x.first<<3|x.second;}
int g(pii x){return abs(x.first-x.second);}

vector<int> sol2(int N){
  vector<vector<int>> Z(23);
  for(int i=0;i<8;++i){
    for(int j=0;j<8;++j){
      int val=f(i,j);
      int dif=abs(i-j);
      Z[i].eb(val),Z[8+j].eb(val);
      if(dif!=7) Z[16+dif].eb(val);
    }
  }
  vector<bool> res=analyse(Z);
  vector<pii> vec;
  for(int i=0;i<8;++i){
    for(int j=0;j<8;++j){
      if(res[i]&res[8+j]) vec.eb(i,j);
    }
  }
  if(vec.size()==1) return {f(vec[0]),f(vec[0])};
  if(vec.size()==2) return {f(vec[0]),f(vec[1])};
  int cnt=0;
  for(int i=0;i<7;++i){
    if(res[16+i]) ++cnt;
  }
  if(cnt==0) return {f(0,7),f(7,0)};
  if(cnt==1){
    if(g(vec[0])==g(vec[3])&&res[16+g(vec[0])]) return {f(vec[0]),f(vec[3])};
    return {f(vec[1]),f(vec[2])};
  }
  if(g(vec[0])!=g(vec[3])&&res[16+g(vec[0])]&&res[16+g(vec[3])]) return {f(vec[0]),f(vec[3])};
  return {f(vec[1]),f(vec[2])};
}

std::vector<int> find_bombs(int N){
  // edit this function
  if(N!=64) return sol1(N);
  return sol2(N);
}

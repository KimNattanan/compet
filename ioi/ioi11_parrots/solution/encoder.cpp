#include "encoder.h"
#include "encoderlib.h"
#include<bits/stdc++.h>
using namespace std;
#define eb emplace_back
namespace Encode{


struct bignum{
  short base=256,len=320;
  array<short,320> a;
  bignum(short x=0){
    for(int i=0;i<len;++i) a[i]=x%base,x/=base;
  }
  bignum& operator+=(const bignum &o){
    for(int i=0;i<len;++i){
      a[i]+=o.a[i];
      if(a[i]>=base) a[i]-=base,++a[i+1];
    }
    return *this;
  }
  bignum& operator-=(const bignum &o){
    for(int i=0;i<len;++i){
      a[i]-=o.a[i];
      if(a[i]<0) a[i]+=base,--a[i+1];
    }
    return *this;
  }
  friend bignum operator+(const bignum &l,const bignum &r){return bignum(l)+=r;}
  int cmp(const bignum &r){
    for(int i=len-1;i>=0;--i){
      if(a[i]!=r.a[i]) return a[i]<r.a[i]?-1:1;
    }
    return 0;
  }
  bool operator<(const bignum &o){return this->cmp(o)==-1;}
  bool operator>(const bignum &o){return this->cmp(o)==1;}
  bool operator<=(const bignum &o){return !(*this>o);}
};

bool ok=0;
bignum dp[325][260],qs[325][260];
void f(){
  ok=1;
  int n=325,m=260;
  for(int j=0;j<m;++j) dp[1][j].a[0]=1,qs[1][j].a[0]=j+1;
  for(int i=2;i<n;++i){
    for(int j=0;j<m;++j){
      dp[i][j]=qs[i-1][j];
      if(j==0) qs[i][j]=dp[i][j];
      else qs[i][j]=qs[i][j-1]+dp[i][j];
    }
  }
}


}; using namespace Encode;
void encode(int N, int M[])
{
  if(!ok) f();
  bignum num;
  for(int i=0;i<N;++i) num.a[i]=M[i];
  int L=5*N;
  vector<int> vec(L);
  for(int i=L-1;i>=0;--i){
    int l=0,r=255;
    while(l<r){
      int mid=l+r>>1;
      if(qs[i+1][mid]<=num) l=mid+1;
      else r=mid;
    }
    if(l==0) break;
    num-=qs[i+1][l-1];
    vec[i]=l;
  }
  for(auto &e:vec) send(e);
}

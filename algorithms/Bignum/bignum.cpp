#include<bits/stdc++.h>
using namespace std;
using ll=long long;

struct bignum{
  ll base=256,len=320;
  array<ll,320> a;
  bignum(ll x=0){
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
  bignum& operator*=(const ll &o){
    ll r=0;
    for(int i=0;i<len;++i){
      a[i]=a[i]*o+r;
      r=a[i]/base;
      a[i]%=base;
    }
    return *this;
  }
  friend bignum operator+(const bignum &l,const bignum &r){return bignum(l)+=r;}
  friend bignum operator-(const bignum &l,const bignum &r){return bignum(l)-=r;}
  friend bignum operator*(const bignum &l,const ll &r){return bignum(l)*=r;}
  int cmp(const bignum &r){
    for(int i=len-1;i>=0;--i){
      if(a[i]!=r.a[i]) return a[i]<r.a[i]?-1:1;
    }
    return 0;
  }
  bool operator==(const bignum &o){return this->cmp(o)==0;}
  bool operator<(const bignum &o){return this->cmp(o)==-1;}
  bool operator>(const bignum &o){return this->cmp(o)==1;}
  bool operator<=(const bignum &o){return !(*this>o);}
  bool operator>=(const bignum &o){return !(*this<o);}
  bool operator!=(const bignum &o){return !(*this==o);}
  friend ostream& operator<<(ostream &os,const bignum &x){
    for(int i=x.len-1;i>0;--i) os<<x.a[i]<<" ";
    os<<x.a[0];
    return os;
  }
};

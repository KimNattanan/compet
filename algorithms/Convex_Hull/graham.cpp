#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using P=pair<ll,ll>;
#define f first
#define s second
#define eb emplace_back

vector<P> getCvh(vector<P> v,bool collinear = false){
  int n=v.size();
  sort(v.begin(),v.end());
  v.erase(unique(v.begin(),v.end()),v.end());
  auto ch=[&](P p1,P p2,P p3){
    return (p2.s-p1.s)*(p3.f-p2.f) - (p2.f-p1.f)*(p3.s-p2.s) >= collinear;
  };
  vector<P> cv;
  for(int i=0;i<n;++i){
    while(cv.size()>1 && ch(cv.end()[-2],cv.back(),v[i])) cv.pop_back();
    cv.eb(v[i]);
  }
  int m=cv.size();
  for(int i=n-1;i>=0;--i){
    while(cv.size()>m && ch(cv.end()[-2],cv.back(),v[i])) cv.pop_back();
    cv.eb(v[i]);
  }
  cv.pop_back();
  return cv;
}

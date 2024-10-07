#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using ld=long double;

struct line{
  ll m,c;
  line(ll m=0,ll c=-1e18):m(m),c(c){}
  template<class T> ll operator()(const T &x){ return m*x+c; }
};
struct cht{
  deque<line> dq;
  bool check(line f1,line f2,line f3){
    return ld(f2.c-f1.c)*(f2.m-f3.m) < ld(f3.c-f2.c)*(f1.m-f2.m);
  }
  void add(line f){
    while(dq.size()>1 && check(dq.end()[-2],dq.back(),f)) dq.pop_back();
    dq.emplace_back(f);
  }
  void add(ll m,ll c){ add(line(m,c)); }
}cv;

ll a[100005],ans[100005];

int main(){
  ios::sync_with_stdio(false); cin.tie(0);

  int n;
  cin>>n;
  for(int i=1;i<=n;i++) cin>>a[i];
  sort(a+1,a+1+n);
  ll cur=0;
  for(int i=1;i<=n;i++){
    if(i!=1) cur+=a[i-1]*a[i];
    cv.add(-a[i],cur+a[i]*a[i]);
  }
  deque<line> &dq = cv.dq;
  for(int i=1;i<=100000;i++){
    while(dq.size()>1 && dq.back()(i)<dq.end()[-2](i)) dq.pop_back();
    ans[i]=dq.back()(i);
    if(ans[i]>0) ans[i]+=a[1]-1;
    ans[i]/=a[1];
  }
  int Q;
  cin>>Q;
  while(Q--){
    int x;
    cin>>x>>x;
    cout<<ans[x]<<'\n';
  }
}

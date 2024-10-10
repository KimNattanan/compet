#include<bits/stdc++.h>
using namespace std;
const int md=1e9-1;

struct fenwick{
  vector<int> bit;
  void init(int n){ bit.assign(n,0); }
  void upd(int i,int x){ for(;i<bit.size();i+=i&-i) bit[i]=(bit[i]+x)%md; }
  int qr(int i){
    int ret=0;
    for(;i>0;i-=i&-i) ret=(ret+bit[i])%md;
    return ret;
  }
}fw[45];

signed main(){
  ios::sync_with_stdio(false); cin.tie(0);
  int n,k; cin>>n>>k;
  for(int i=1;i<=k;++i) fw[i].init(n+5);
  for(int i=1;i<=n;++i){
    int x; cin>>x;
    fw[1].upd(x,1);
    for(int j=2;j<=k;++j) fw[j].upd(x,((fw[j-1].qr(n)-fw[j-1].qr(x))%md+md)%md);
  }
  cout<<fw[k].qr(n);
}

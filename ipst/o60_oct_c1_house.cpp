#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using i4=array<int,4>;
#define eb emplace_back

i4 a[200005][19];

signed main(){
  ios::sync_with_stdio(false); cin.tie(0);
  int n,Q; cin>>n>>Q;
  function<i4(i4,i4)> f=[](i4 l,i4 r){
    return i4{l[0]+r[0],
              max(l[1],l[0]+r[1]),
              max(r[2],r[0]+l[2]),
              max({l[3],r[3],l[2]+r[1]})};
  };
  for(int i=0;i<n;++i){
    int x; cin>>x;
    if(x<0) a[i][0]={x,0,0,0};
    else a[i][0]={x,x,x,x};
    for(int j=1;j<19&&i-(1<<j)+1>=0;++j) a[i][j]=f(a[i-(1<<j-1)][j-1],a[i][j-1]);
  }
  function<int(int,int)> qr=[&](int l,int r){
    int n=r-l+1;
    i4 ret={0,0,0,0};
    for(int i=18;i>=0;--i){
      if(n&1<<i) ret=f(a[r][i],ret), r-=1<<i;
    }
    return ret[3];
  };
  while(Q--){
    int l,r; cin>>l>>r;
    l=max(0,l), r=min(n-1,r);
    cout<<qr(l,r)<<'\n';
  }
}

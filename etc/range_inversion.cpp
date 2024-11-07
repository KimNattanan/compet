#include<bits/stdc++.h>
using namespace std;
using ll=long long;
#define eb emplace_back

ll qs[320];
int a[100005],qs2[320][100005],n,sq;
array<int,100005> _a[2];

ll countInv(int l,int r){
  if(l==r) return _a[0][l]=a[l], 0;
  int mid=l+r>>1;
  ll ret=countInv(l,mid)+countInv(mid+1,r);
  int il=l, ir=mid+1, cur=l;
  while(il<=mid&&ir<=r){
    if(_a[0][il]<=_a[0][ir]) _a[1][cur++]=_a[0][il++];
    else ret+=mid-il+1, _a[1][cur++]=_a[0][ir++];
  }
  while(il<=mid) _a[1][cur++]=_a[0][il++];
  while(ir<=r) _a[1][cur++]=_a[0][ir++];
  swap(_a[0],_a[1]);
  return ret;
}

void build(){
  sq=sqrt(n);
  for(int i=0;i*sq<n;++i){
    qs[i]=countInv(i*sq,(i+1)*sq-1);
    if(i) qs[i]+=qs[i-1];
  }
  for(int i=0;i<n;++i) ++qs2[i/sq][a[i]];
  for(int i=0;i*sq<n;++i){
    for(int j=0;j<n;++j){
      if(i!=0 && j!=0) qs2[i][j]+=qs2[i-1][j]+qs2[i][j-1]-qs2[i-1][j-1];
      else if(i!=0) qs2[i][j]+=qs2[i-1][j];
      else if(j!=0) qs2[i][j]+=qs2[i][j-1];
    }
  }
}
ll qr(int l,int r){
  int bl=l/sq, br=r/sq;
  if(bl+1>=br) return countInv(l,r);
  ++bl, --br;
  ll ret=qs[br]-qs[bl-1];
  for(; l!=bl*sq; ++l) if(a[l]!=0) ret += qs2[br][a[l]-1]-qs2[bl-1][a[l]-1];
  for(; r/sq!=br; --r) ret += qs2[br][n-1]-qs2[bl-1][n-1]-qs2[br][a[r]]+qs2[bl-1][a[r]];
  return ret;
}

int main(){
  ios::sync_with_stdio(false); cin.tie(0);
  
  cin>>n;
  vector<int> comp;
  for(int i=0;i<n;++i) cin>>a[i], comp.eb(a[i]);
  sort(comp.begin(),comp.end());
  comp.erase(unique(comp.begin(),comp.end()),comp.end());
  for(int i=0;i<n;++i) a[i]=lower_bound(comp.begin(),comp.end(),a[i])-comp.begin();
  build();
  
  int Q; cin>>Q;
  while(Q--){
    int l,r; cin>>l>>r;
    --l,--r;
    cout<<qr(l,r)<<'\n';
  }
}

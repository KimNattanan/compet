#include<bits/stdc++.h>
using namespace std;
#define eb emplace_back
using ll=long long;

struct fenwick{
  vector<ll> bit;
  void init(int n){ bit.assign(n,0); }
  void upd(int i,ll x){ for(++i;i<bit.size();i+=i&-i) bit[i]+=x; }
  void upd(int l,int r,ll x){ upd(l,x), upd(r+1,-x); }
  ll qr(int i){
    ll ret=0;
    for(++i;i>0;i-=i&-i) ret+=bit[i];
    return ret;
  }
}t1,t2;

int a[1000005];
bitset<1000005> b;

int main(){
  ios::sync_with_stdio(false); cin.tie(0);
  int m,n,Q; cin>>m>>n>>Q;
  t1.init(n+5),t2.init(n+5);
  t2.upd(0,m);
  while(Q--){
    char c; cin>>c;
    if(c=='s'){
      int x,y; cin>>x>>y;
      y=(a[x]+y)%n;
      if(a[x]==y) continue;
      if(b[x]){
        if(!y) t1.upd(0,n-a[x]), t1.upd(a[x],-n);
        else if(!a[x]) t1.upd(0,y-n), t1.upd(y,n);
        else if(a[x]<y) t1.upd(0,y-a[x]), t1.upd(a[x],y-1,-n);
        else t1.upd(0,y-a[x]), t1.upd(y,a[x]-1,n);
      }
      else{
        if(!y) t1.upd(0,a[x]-n), t1.upd(a[x]+1,n);
        else if(!a[x]) t1.upd(0,n-y), t1.upd(y+1,-n);
        else if(a[x]<y) t1.upd(0,a[x]-y), t1.upd(a[x]+1,y,n);
        else t1.upd(0,a[x]-y), t1.upd(y+1,a[x],-n);
      }
      a[x]=y;
    }
    else if(c=='f'){
      int x; cin>>x;
      if(b[x]){
        if(a[x]) t1.upd(0,a[x]-1,n-(a[x]<<1)), t1.upd(a[x]+1,-n-(a[x]<<1)), t2.upd(0,a[x]-1,2), t2.upd(a[x]+1,2);
        else t1.upd(0,-n), t2.upd(0,2);
      }
      else{
        if(a[x]) t1.upd(0,a[x]-1,(a[x]<<1)-n), t1.upd(a[x]+1,n+(a[x]<<1)), t2.upd(0,a[x]-1,-2), t2.upd(a[x]+1,-2);
        else t1.upd(0,n), t2.upd(0,-2);
      }
      b[x]=!b[x];
    }
    else{
      int y; cin>>y;
      cout<<t1.qr(y)+y*t2.qr(y)<<'\n';
    }
  }
}

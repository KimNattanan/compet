#include<bits/stdc++.h>
using namespace std;
#define eb emplace_back
using ll=long long;

struct segment{
  ll t[1<<21],lz[1<<21],lz2[1<<21],lz3[1<<21];
  int l0,r0;
  void build(int i,int il,int ir,int m){
    t[i]=(ll(ir-il+1)*(il+ir)>>1)*m;
    if(il==ir) return;
    int mid=il+ir>>1;
    build(i<<1,il,mid,m), build(i<<1|1,mid+1,ir,m);
  }
  void build(int l,int r,int m){ l0=l,r0=r,build(1,l,r,m); }
  void flush(int i,int il,int ir){
    if(il!=ir) lz[i<<1]+=lz[i], lz[i<<1|1]+=lz[i],
               lz2[i<<1]+=lz2[i], lz2[i<<1|1]+=lz2[i],
               lz3[i<<1]+=lz3[i], lz3[i<<1|1]+=lz3[i];
    if(lz[i]) t[i]+=lz[i]*(ir-il+1), lz[i]=0;
    if(lz2[i]) t[i]+=lz2[i]*(ir-il+1)*(il+ir)>>1, lz2[i]=0;
    if(lz3[i]) t[i]-=lz3[i]*(ir-il+1), lz3[i]=0;
  }
  void upd1(int i,int il,int ir,int l,int r,ll v){
    flush(i,il,ir);
    if(il>r||ir<l) return;
    if(l<=il&&ir<=r) return lz[i]+=v,flush(i,il,ir);
    int mid=il+ir>>1;
    upd1(i<<1,il,mid,l,r,v), upd1(i<<1|1,mid+1,ir,l,r,v);
    t[i]=t[i<<1]+t[i<<1|1];
  }
  void upd1(int l,int r,ll v){ upd1(1,l0,r0,l,r,v); }
  void upd2(int i,int il,int ir,int l,int r,ll v){
    flush(i,il,ir);
    if(il>r||ir<l) return;
    if(l<=il&&ir<=r) return lz2[i]+=v,lz3[i]+=v*l,flush(i,il,ir);
    int mid=il+ir>>1;
    upd2(i<<1,il,mid,l,r,v), upd2(i<<1|1,mid+1,ir,l,r,v);
    t[i]=t[i<<1]+t[i<<1|1];
  }
  void upd2(int l,int r,ll v){ upd2(1,l0,r0,l,r,v); }
  ll qr(int i,int il,int ir,int id){
    flush(i,il,ir);
    if(il==ir) return t[i];
    int mid=il+ir>>1;
    if(id<=mid) return qr(i<<1,il,mid,id);
    return qr(i<<1|1,mid+1,ir,id);
  }
  ll qr(int id){ return qr(1,l0,r0,id); }
}t;

int a[1000005];
bitset<1000005> b;

int main(){
  ios::sync_with_stdio(false); cin.tie(0);
  int m,n,Q; cin>>m>>n>>Q;
  t.build(0,n,m);
  while(Q--){
    char c; cin>>c;
    if(c=='s'){
      int x,y; cin>>x>>y;
      int a2=(a[x]+y)%n;
      if(a2==a[x]) continue;
      if(b[x]){
        if(a[x]==0) t.upd1(0,n,a2), t.upd1(0,a2-1,-n);
        else if(a2==0) t.upd1(0,n,a[x]), t.upd1(a[x],n,-n);
        else if(a2>a[x]) t.upd1(0,n,a2-a[x]), t.upd1(a[x],a2-1,-n);
        else t.upd1(0,n,a2-a[x]), t.upd1(a2,a[x]-1,n);
      }
      else{
        if(a[x]==0) t.upd1(0,n,-a2), t.upd1(0,a2,n);
        else if(a2==0) t.upd1(0,n,a[x]-n), t.upd1(a[x]+1,n,n);
        else if(a2>a[x]) t.upd1(0,n,a[x]-a2), t.upd1(a[x]+1,a2,n);
        else t.upd1(0,n,a[x]-a2), t.upd1(a2+1,a[x],-n);
      }
      a[x]=a2;
    }
    else if(c=='f'){
      int x; cin>>x;
      if(b[x]){
        if(a[x]==0) t.upd1(0,n,-n),t.upd2(0,n,2);
        else t.upd1(0,a[x]-1,n-(a[x]<<1)),t.upd2(0,a[x]-1,2),t.upd1(a[x]+1,n,2-n),t.upd2(a[x]+1,n,2);
      }
      else{
        if(a[x]==0) t.upd1(0,n,n),t.upd2(0,n,-2);
        else t.upd1(0,a[x]-1,(a[x]<<1)-n),t.upd2(0,a[x]-1,-2),t.upd1(a[x]+1,n,n-2),t.upd2(a[x]+1,n,-2);
      }
      b[x]=!b[x];
    }
    else{
      int x; cin>>x;
      cout<<t.qr(x)<<'\n';
    }
  }
}

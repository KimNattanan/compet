#include<bits/stdc++.h>
using namespace std;
#define eb emplace_back
using i4=array<int,4>;

struct segment{
  int l0,r0,lz[1<<18];
  i4 val[1<<18];
  void build(int l,int r){ l0=l,r0=r; }
  void flush(int i,int il,int ir){
    if(il!=ir) lz[i<<1]+=lz[i],lz[i<<1|1]+=lz[i];
    val[i][0]+=lz[i], val[i][1]+=lz[i];
    lz[i]=0;
  }
  void upd(int i,int il,int ir,int l,int r){
    flush(i,il,ir);
    if(il>r||ir<l) return;
    if(l<=il&&ir<=r) return ++lz[i],flush(i,il,ir);
    int mid=il+ir>>1;
    upd(i<<1,il,mid,l,r), upd(i<<1|1,mid+1,ir,l,r);
    val[i][0]=val[i<<1][0], val[i][1]=val[i<<1|1][1];
    val[i][2]=val[i<<1][2]+val[i<<1|1][2]+(val[i<<1][1]<val[i<<1|1][0]);
    val[i][3]=val[i<<1][3]+val[i<<1|1][3]+(val[i<<1][1]>val[i<<1|1][0]);
  }
  void upd(int l,int r){ upd(1,l0,r0,l,r); }
  i4 qr(int i,int il,int ir,int l,int r){
    flush(i,il,ir);
    if(il>r||ir<l) return {-1,-1,-1,-1};
    if(l<=il&&ir<=r) return val[i];
    int mid=il+ir>>1;
    i4 tl=qr(i<<1,il,mid,l,r), tr=qr(i<<1|1,mid+1,ir,l,r);
    if(tl[0]==-1) return tr;
    if(tr[0]==-1) return tl;
    return {tl[0],tr[1],tl[2]+tr[2]+(tl[1]<tr[0]),tl[3]+tr[3]+(tl[1]>tr[0])};
  }
  i4 qr(int l,int r){ return qr(1,l0,r0,l,r); }
}t;

int main(){
  ios::sync_with_stdio(false); cin.tie(0);
  int n,Q; cin>>n>>Q;
  t.build(1,n);
  while(Q--){
    int x,l,r; cin>>x>>l>>r;
    if(x==1) t.upd(l,r);
    else{
      i4 val=t.qr(l,r);
      if(x==2) cout<<val[0]<<" "<<val[1]<<'\n';
      else cout<<val[0]<<" "<<val[1]<<" "<<val[2]<<" "<<val[3]<<'\n';
    }
  }
}

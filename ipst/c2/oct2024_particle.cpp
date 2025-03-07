#include<bits/stdc++.h>
using namespace std;
using ll=long long;

struct segment{
  ll a[1<<21],lz[1<<21][2],b[1<<21];
  int l0,r0;
  void init(int l,int r){
    l0=l,r0=r;
  }
  void flush(int i,int il,int ir){
    if(il!=ir){
      lz[i<<1][0]*=lz[i][0], lz[i<<1][1] = lz[i<<1][1]*lz[i][0]+lz[i][1];
      lz[i<<1|1][0]*=lz[i][0], lz[i<<1|1][1] = lz[i<<1|1][1]*lz[i][0]+lz[i][1];
    }
    a[i] = a[i]*lz[i][0]+lz[i][1]*(ir-il+1);
    b[i] = b[i]*lz[i][0]+lz[i][1];
    lz[i][0]=1, lz[i][1]=0;
  }
  void upd(int i,int il,int ir,int l,int r,ll x){
    flush(i,il,ir);
    if(il>r||ir<l) return;
    if(l<=il&&ir<=r) return lz[i][0]=-lz[i][0], lz[i][1]=x-lz[i][1], flush(i,il,ir);
    int mid=il+ir>>1;
    upd(i<<1,il,mid,l,r,x), upd(i<<1|1,mid+1,ir,l,r,x);
    a[i]=a[i<<1]+a[i<<1|1];
    b[i]=b[i<<1];
  }
  void upd(int l,int r,ll x){ upd(1,l0,r0,l,r,x); }
  ll qr(int i,int il,int ir,int l,int r){
    flush(i,il,ir);
    if(il>r||ir<l) return 0;
    if(l<=il&&ir<=r) return a[i];
    int mid=il+ir>>1;
    return qr(i<<1,il,mid,l,r)+qr(i<<1|1,mid+1,ir,l,r);
  }
  ll qr(int l,int r){ return qr(1,l0,r0,l,r); }
  int qr2(int i,int il,int ir,int l,int r,ll vl,ll vr){
    if(il==ir) return il;
    int mid=il+ir>>1;
    flush(i,il,ir);
    flush(i<<1|1,mid+1,ir);
    flush(i<<1,il,mid);
    if(mid<l) return qr2(i<<1|1,mid+1,ir,l,r,vl+a[i<<1],vr);
    if(mid>=r) return qr2(i<<1,il,mid,l,r,vl,vr+a[i<<1|1]);
    if(a[i<<1]+vl<a[i<<1|1]+vr-b[i<<1|1]) return qr2(i<<1|1,mid+1,ir,l,r,vl+a[i<<1],vr);
    return qr2(i<<1,il,mid,l,r,vl,vr+a[i<<1|1]);
  }
}t;

void init(int N) {
  t.init(0,N-1);
}
void generateParticle(int L,int R,int P) {
  t.upd(L,R,P);
}
long long countSize(int L,int R) {
  return t.qr(L,R);
}
int bestPartition(int L,int R) {
  if(L==R) return L;
  return t.qr2(1,t.l0,t.r0,L,R,-t.qr(0,L-1),-t.qr(R+1,t.r0));
}

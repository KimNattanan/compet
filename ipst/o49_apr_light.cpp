#include<bits/stdc++.h>
using namespace std;
#define eb emplace_back

struct segment{
  int il,mid,ir,val;
  bool lz;
  vector<segment> adj;
  segment(int l,int r):il(l),mid(l+r>>1),ir(r),val(r-l+1),lz(0){}
  void flush(){
    if(il!=ir&&adj.empty()) adj.eb(il,mid),adj.eb(mid+1,ir);
    if(!lz) return;
    if(il!=ir) adj[0].lz^=1,adj[1].lz^=1;
    val=ir-il+1-val;
    lz=0;
  }
  void upd(int l,int r){
    flush();
    if(il>r||ir<l) return;
    if(l<=il&&ir<=r) return lz^=1,flush();
    adj[0].upd(l,r), adj[1].upd(l,r);
    val=adj[0].val+adj[1].val;
  }
};

int main(){
  ios::sync_with_stdio(false); cin.tie(0);
  int n,Q; cin>>n>>Q;
  segment t(1,n);
  while(Q--){
    int x; cin>>x;
    t.upd(x+1,n);
    cout<<t.val<<'\n';
  }
}

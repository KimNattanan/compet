#include<bits/stdc++.h>
using namespace std;
using ll=long long;
#define eb emplace_back

struct segment{
  ll t[1<<18][9],v[1<<18][3];
  int l0,r0;
  void build(int l,int r){ l0=l,r0=r; }
  void upd(int i,int il,int ir,int l,int r,ll x){
    if(il+1==ir) return void(t[i][0]=x);
    int mid=il+ir>>1;
    if(r<=mid) upd(i<<1,il,mid,l,r,x);
    else if(l>mid) upd(i<<1|1,mid+1,ir,l,r,x);
    else if(r==mid+2) v[i][2]=x;
    else if(l==mid-1) v[i][1]=x;
    else v[i][0]=x;
    auto &[l0,l1,l2,l3,l4,l5,l6,l7,l8]=t[i<<1];
    auto &[r0,r1,r2,r3,r4,r5,r6,r7,r8]=t[i<<1|1];
    auto &[t0,t1,t2,t3,t4,t5,t6,t7,t8]=t[i];
    auto &[_v0,_v1,_v2]=v[i];
    ll v0=_v0, v1=_v1, v2=_v2;
    if(il+2==ir){
      t0=min({l0,v0,v1});
      t1=l0;
      t3=v0;
      return;
    }
    t0=min({l0+r0,l1+v0+r3,l2+v1+r3,l1+v2+r6});
    v0 = (il<=mid&&mid+1<=ir-1) ? _v0 : 0;
    v1 = (il<=mid-1&&mid+1<=ir-1) ? _v1 : 0;
    v2 = (il<=mid&&mid+2<=ir-1) ? _v2 : 0;
    t1=min({l0+r1,l1+v0+r4,l2+v1+r4,l1+v2+r7});
    v0 = (il<=mid&&mid+1<=ir-2) ? _v0 : 0;
    v1 = (il<=mid-1&&mid+1<=ir-2) ? _v1 : 0;
    v2 = (il<=mid&&mid+2<=ir-2) ? _v2 : 0;
    t2=min({l0+r2,l1+v0+r5,l2+v1+r5,l1+v2+r8});
    v0 = (il+1<=mid&&mid+1<=ir) ? _v0 : 0;
    v1 = (il+1<=mid-1&&mid+1<=ir) ? _v1 : 0;
    v2 = (il+1<=mid&&mid+2<=ir) ? _v2 : 0;
    t3=min({l3+r0,l4+v0+r3,l5+v1+r3,l4+v2+r6});
    v0 = (il+1<=mid&&mid+1<=ir-1) ? _v0 : 0;
    v1 = (il+1<=mid-1&&mid+1<=ir-1) ? _v1 : 0;
    v2 = (il+1<=mid&&mid+2<=ir-1) ? _v2 : 0;
    t4=min({l3+r1,l4+v0+r4,l5+v1+r4,l4+v2+r7});
    v0 = (il+1<=mid&&mid+1<=ir-2) ? _v0 : 0;
    v1 = (il+1<=mid-1&&mid+1<=ir-2) ? _v1 : 0;
    v2 = (il+1<=mid&&mid+2<=ir-2) ? _v2 : 0;
    t5=min({l3+r2,l4+v0+r5,l5+v1+r5,l4+v2+r8});
    v0 = (il+2<=mid&&mid+1<=ir) ? _v0 : 0;
    v1 = (il+2<=mid-1&&mid+1<=ir) ? _v1 : 0;
    v2 = (il+2<=mid&&mid+2<=ir) ? _v2 : 0;
    t6=min({l6+r0,l7+v0+r3,l8+v1+r3,l7+v2+r6});
    v0 = (il+2<=mid&&mid+1<=ir-1) ? _v0 : 0;
    v1 = (il+2<=mid-1&&mid+1<=ir-1) ? _v1 : 0;
    v2 = (il+2<=mid&&mid+2<=ir-1) ? _v2 : 0;
    t7=min({l6+r1,l7+v0+r4,l8+v1+r4,l7+v2+r7});
    v0 = (il+2<=mid&&mid+1<=ir-2) ? _v0 : 0;
    v1 = (il+2<=mid-1&&mid+1<=ir-2) ? _v1 : 0;
    v2 = (il+2<=mid&&mid+2<=ir-2) ? _v2 : 0;
    t8=min({l6+r2,l7+v0+r5,l8+v1+r5,l7+v2+r8});
  }
  void upd(int l,int r,ll x){ upd(1,l0,r0,l,r,x); }
}t;

vector<ll> calculate_costs(vector<int> W, vector<int> A, vector<int> B, vector<int> E){
  vector<int> qid(E.size());
  iota(qid.begin(),qid.end(),0);
  sort(qid.begin(),qid.end(),[&](const int &l,const int &r){
    return E[l]<E[r];
  });
  vector<int> item_id(W.size());
  iota(item_id.begin(),item_id.end(),0);
  sort(item_id.begin(),item_id.end(),[&](const int &l,const int &r){
    return W[l]<W[r];
  });
  int n=A.size();
  vector<tuple<int,ll,int,int>> item;
  ll sumA=A[0];
  for(int i=1;i<n;++i){
    sumA+=A[i];
    item.eb(abs(W[item_id[i]]-W[item_id[i-1]]),B[item_id[i]]+B[item_id[i-1]]-A[item_id[i]]-A[item_id[i-1]],i-1,i);
    if(i!=1) item.eb(abs(W[item_id[i]]-W[item_id[i-2]]),B[item_id[i]]+B[item_id[i-2]]-A[item_id[i]]-A[item_id[i-2]],i-2,i);
  }
  sort(item.begin(),item.end());
  int cur_q=0;
  vector<ll> ans(E.size());
  t.build(0,n-1);
  for(auto &[d,v,l,r]:item){
    while(cur_q<E.size()&&E[qid[cur_q]]<d) ans[qid[cur_q++]] = sumA+t.t[1][0];
    t.upd(l,r,v);
  }
  while(cur_q<E.size()) ans[qid[cur_q++]] = sumA+t.t[1][0];
  return ans;
}

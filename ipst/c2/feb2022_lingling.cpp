#include "lingling.h"
#include<bits/stdc++.h>
using namespace std;
#define eb emplace_back
using ll=long long;
using pii=pair<int,int>;
#define f first
#define s second

vector<int> P;
int N,sq,dp[450][200005];
ll dp2[450][450];
int mp[200005],mp2[200005];

ll inv_cnt(vector<int> &vec){
  int n=vec.size();
  if(n==1) return 0LL;
  vector<int> L,R;
  for(int i=0;i<n>>1;++i) L.eb(vec[i]);
  for(int i=n>>1;i<n;++i) R.eb(vec[i]);
  ll cnt=inv_cnt(L)+inv_cnt(R);
  int l=0,r=0;
  vec.clear();
  while(l<L.size()&&r<R.size()){
    if(L[l]>R[r]){
      cnt+=L.size()-l;
      vec.eb(R[r++]);
    }
    else vec.eb(L[l++]);
  }
  while(l<L.size()) vec.eb(L[l++]);
  while(r<R.size()) vec.eb(R[r++]);
  return cnt;
}

ll f(int i0,int j0,int i1,int j1){
  if(i0>i1||j0>j1) return 0;
  ll sum=dp[i1][j1];
  if(j0>0) sum-=dp[i1][j0-1];
  if(i0>0){
    sum-=dp[i0-1][j1];
    if(j0>0) sum+=dp[i0-1][j0-1];
  }
  return sum;
}

struct seg1{
  vector<seg1> child;
  int l,r,mid,mn,mx,mx2;
  seg1(int l_=0,int r_=0):l(l_),r(r_),mid(l+(r-l>>1)){}
  void build(){
    if(l==r){
      mn=mx=P[l];
      mx2=mp2[l];
      return;
    }
    child.eb(l,mid),child.eb(mid+1,r);
    child[0].build(),child[1].build();
    mn=min(child[0].mn,child[1].mn);
    mx=max(child[0].mx,child[1].mx);
    mx2=max(child[0].mx2,child[1].mx2);
  }
  pii qr(int l0,int r0){
    if(l0<=l&&r<=r0) return pii(mn,mx);
    if(l>r0||r<l0) return pii(1e9,-1);
    pii L=child[0].qr(l0,r0),R=child[1].qr(l0,r0);
    return pii(min(L.f,R.f),max(L.s,R.s));
  }
  int qr2(int l0,int r0){
    if(l0<=l&&r<=r0) return mx2;
    if(l>r0||r<l0) return -1;
    return max(child[0].qr2(l0,r0),child[1].qr2(l0,r0));
  }
}t1;

void init_monkeys(vector<int> P, int Q){
  // edit this function
  ::P=P;
  N=P.size();
  sq=sqrt(N);
  vector<int> vec;
  for(int i=0;i<N;++i){
    mp[i]=-1;
    int sqi=i/sq;
    ++dp[sqi][P[i]];
    if(i%sq==0&&i>0) dp2[sqi-1][sqi-1]=inv_cnt(vec),vec.clear();
    vec.eb(P[i]);
  }
  int temp=(N-1)/sq;
  dp2[temp][temp]=inv_cnt(vec);
  for(int i=0;i<=temp;++i){
    for(int j=0;j<N;++j){
      if(i>0) dp[i][j]+=dp[i-1][j];
      if(j>0){
        dp[i][j]+=dp[i][j-1];
        if(i>0) dp[i][j]-=dp[i-1][j-1];
      }
    }
  }
  for(int i=0;i<=temp;++i){
    for(int j=i+1;j<=temp;++j){
      dp2[i][j]=dp2[j][j]+dp2[i][j-1];
      for(int k=j*sq;k<(j+1)*sq&&k<N;++k){
        dp2[i][j]+=f(i,P[k]+1,j-1,N-1);
      }
    }
  }

  for(int i=0;i<N;++i){
    mp2[i]=mp[P[i]];
    mp[P[i]]=i;
  }
  t1=seg1(0,N-1),t1.build();
}

long long minimum_branches(int L, int R){
  // edit this function

  pii temp=t1.qr(L,R);
  if(temp.f<L||temp.s>R||t1.qr2(L,R)>=L) return -1;

  int sqL=L/sq,sqR=R/sq;
  ll ans=0;
  vector<int> vec;
  if(sqL==sqR){
    for(int i=L;i<=R;++i) vec.eb(P[i]);
  }
  else if(sqL+1==sqR){
    for(int i=L;i/sq==sqL;++i) vec.eb(P[i]);
    for(int i=sqR*sq;i<=R;++i) vec.eb(P[i]);
  }
  else{
    ans+=dp2[sqL+1][sqR-1];
    for(int i=L;i/sq==sqL;++i) vec.eb(P[i]),ans+=f(sqL+1,0,sqR-1,P[i]-1);
    for(int i=sqR*sq;i<=R;++i) vec.eb(P[i]),ans+=f(sqL+1,P[i]+1,sqR-1,N-1);
  }
  return ans+inv_cnt(vec);
}

// int main(){
//   ios::sync_with_stdio(false); cin.tie(0);
//   int n; cin>>n;
//   vector<int> vec(n);
//   for(int i=0;i<n;++i) cin>>vec[i];
//   init_monkeys(vec,0);
//   while(1){
//     int l,r; cin>>l>>r;
//     if(l==-1) return 0;
//     cout<<minimum_branches(l-1,r-1)<<endl;
//   }
//   return 0;
// }

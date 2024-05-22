#include "sailing.h"
#include<bits/stdc++.h>
using namespace std;
using pii=pair<int,int>;
using ll=long long;
#define f first
#define s second
#define eb emplace_back

const int MX=32;

mt19937 rng(time(0));
bitset<MX> pat;
bool pat0[]={1,0,1,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1};
deque<bool> cur;

bool check(){
  for(int i=0;i<MX;++i) if(cur.end()[-1-i]!=pat[i]) return 0;
  return 1;
}

int sub1(){
  flag();
  for(int i=3;i<=5000;++i){
    for(int j=1;j<i;++j) if(sail_forward()) flag();
    for(int j=2;j<i;++j) sail_backward();
    if(!sail_backward()) return i-1;
  }
}

int set_sail() {
  
  return sub1();

  cur.clear();
  for(int i=0;i<MX;++i) pat[i]=pat0[i];//rng()%2;
  if(pat[0]) flag();
  for(int i=1;i<MX;++i){
    if(sail_forward()!=pat[i]) flag();
  }
  for(int i=MX-2;i>=0;--i){
    if(sail_backward()!=pat[i]){
      int n2=MX-i;
      for(int j=0;j<n2;++j) if(sail_forward()) flag();
      int ans=1;
      flag();
      for(int j=0;j<n2;++j){
        if(sail_forward()) break;
        flag();
        ++ans;
      }
      return ans;
    }
  }
  for(int i=0;i<MX;++i) cur.eb(sail_backward());
  int ans=MX;
  while(!check()) cur.eb(sail_backward()), cur.pop_front(), ++ans;
  return ans;
}

#include "sailing.h"
#include<bits/stdc++.h>
using namespace std;

// #define SUB1
#define go sail_forward
#define back sail_backward
const int K=32;

mt19937 rng(time(0));
int pat[K+5],cur[1000005];

int set_sail() {
  #ifdef SUB1
    flag();
    bool z=0;
    for(int i=2;;++i){
      for(int j=0;j<i;++j) if(go()) flag();
      for(int j=0;j<i;++j) if(!back() && j==i-1) return i;
    }
  #endif

  flag();
  int ans;
  for(int i=1;i<K;++i) if(go()) ans=i, flag();
  for(int i=1;i<K;++i) if(!back() && i==K-1) return ans;
  ans=K;
  for(int i=0;i<K;++i) pat[i]=rng()&1;
  for(int i=0;i<K;++i) if(go()!=pat[i]) flag();
  for(int i=1;i<K;++i) cur[i]=go();
  for(int i=K;;++i){
    cur[i]=go();
    bool ok=1;
    for(int j=i-K+1;j<=i;++j) ok &= (cur[j]==pat[j-(i-K+1)]);
    if(ok) return ans;
    ++ans;
  }
}

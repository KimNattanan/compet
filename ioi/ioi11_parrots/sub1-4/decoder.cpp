#include "decoder.h"
#include "decoderlib.h"
#include<bits/stdc++.h>
using namespace std;
 
void decode(int N, int L, int X[])
{
  vector<int> ans(N);
  for(int i=0;i<L;++i){
    int id=0;
    for(int mask=1<<4;mask>=1;mask>>=1) id+=(mask&X[i])?mask:0;
    for(int mask=1<<5,j=1;j<=100;j*=10,mask<<=1) ans[id]+=(mask&X[i])?j:0;
  }
  for(auto &e:ans) output(e);
}

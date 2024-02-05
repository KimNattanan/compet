#include "encoder.h"
#include "encoderlib.h"
#include<bits/stdc++.h>
using namespace std;
 
void encode(int N, int M[])
{
  for(int i=0;i<N;++i){
    vector<int> vec(9,i);
    int x=M[i];
    for(int j=x/100-1, mask=1<<7 ;j>=0;--j,x-=100) vec[j]+=mask;
    for(int j=x/10-1, mask=1<<6 ;j>=0;--j,x-=10) vec[j]+=mask;
    for(int j=x-1, mask=1<<5 ;j>=0;--j,x-=1) vec[j]+=mask;
    for(auto &e:vec) send(e);
  }
}

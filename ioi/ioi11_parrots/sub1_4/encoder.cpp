#include "encoder.h"
#include "encoderlib.h"
#include<bits/stdc++.h>
using namespace std;

void encode(int N, int M[])
{
  for(int i=0;i<N;++i) M[i]=0;
  for(int i=0;i<N;++i) send(0);
}

#include "testlib.h"
#include<bits/stdc++.h>
using namespace std;

void gen(int Q,int N_min,int N_max,int M_min,int M_max){
  cout<<Q<<'\n';
  {
    --Q;
    int N=N_max;
    int M=M_max;
    cout<<N<<" "<<M<<'\n';
    for(int i=1;i<=N;++i) cout<<rnd.next(1,30000)<<" \n"[i==N];
  }
  while(Q--){
    int N=rnd.next(N_min,N_max);
    int M=rnd.next(M_min,M_max);
    cout<<N<<" "<<M<<'\n';
    for(int i=1;i<=N;++i) cout<<rnd.next(1,30000)<<" \n"[i==N];
  }
}

int main(int argc, char* argv[]){
  registerGen(argc, argv, 1);
  int test_num = opt<int>("test-num");
  int test_begin = opt<int>("test-begin");
  int Q = opt<int>(1);
  int N_min = opt<int>(2);
  int N_max = opt<int>(3);
  int M_min = opt<int>(4);
  int M_max = opt<int>(5);

  for(int i=0;i<test_num;++i){
    startTest(test_begin+i);
    gen(Q,N_min,N_max,M_min,M_max);
  }
}
/*
gen 100 1 100 1 100 -test-num 3 -test-begin 1 > {1-3}
gen 1000 50 100 500 1000 -test-num 3 -test-begin 4 > {4-6}
gen 1000 50000 100000 100000000 1000000000 -test-num 4 -test-begin 7 > {7-10}
*/
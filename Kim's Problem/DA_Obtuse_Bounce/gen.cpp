#include "testlib.h"
#include<bits/stdc++.h>
using namespace std;

void gen(int n,int Q,int y_mul){
  cout<<n<<'\n';
  for(int i=0;i<n;++i){
    int x=rnd.next(-15000,15000);
    int y=rnd.next(-15000,15000)*y_mul;
    cout<<x<<" "<<y<<'\n';
  }
  cout<<Q<<'\n';
  for(int i=0;i<n;++i){
    int x=rnd.next(-15000,15000);
    int y=rnd.next(-15000,15000)*y_mul;
    cout<<x<<" "<<y<<'\n';
  }
}

int main(int argc, char* argv[]){
  registerGen(argc, argv, 1);
  int test_num = opt<int>("test-num");
  int test_begin = opt<int>("test-begin");
  int n = opt<int>(1);
  int Q = opt<int>(2);
  int y_mul = opt<int>(3);

  for(int i=0;i<test_num;++i){
    startTest(test_begin+i);
    gen(n,Q,y_mul);
  }
}
/*
gen 200000 50 1 -test-num 3 -test-begin 1 > {1-3}
gen 200000 200000 0 -test-num 3 -test-begin 4 > {4-6}
gen 200000 200000 1 -test-num 4 -test-begin 7 > {7-10}
*/
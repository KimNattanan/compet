#include "testlib.h"
#include<bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]){
  registerValidation(argc, argv);
  int Q=inf.readInt(1,1000,"Q");
  inf.readEoln();
  while(Q--){
    int n=inf.readInt(1,100000,"N");
    inf.readSpace();
    int m=inf.readInt(1,1000000000,"M");
    inf.readEoln();
    for(int i=1;i<=n;++i){
      inf.readInt(1,30000,"x");
      if(i==n) inf.readEoln();
      else inf.readSpace();
    }
  }
  inf.readEof();
}

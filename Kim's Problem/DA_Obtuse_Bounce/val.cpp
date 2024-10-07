#include "testlib.h"
#include<bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]){
  registerValidation(argc, argv);
  int n=inf.readInt(1,200000,"N");
  inf.readEoln();
  for(int i=0;i<n;++i){
    inf.readInt(-15000,15000,"px");
    inf.readSpace();
    inf.readInt(-15000,15000,"py");
    inf.readEoln();
  }
  int Q=inf.readInt(1,200000,"Q");
  inf.readEoln();
  for(int i=0;i<n;++i){
    inf.readInt(-15000,15000,"x");
    inf.readSpace();
    inf.readInt(-15000,15000,"y");
    inf.readEoln();
  }
  inf.readEof();
}

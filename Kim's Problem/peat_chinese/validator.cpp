#include <bits/stdc++.h>
#include "testlib.h"
 
using namespace std;
 
int main(int argc, char *argv[]) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int max_m=min(1LL*n*(n-1)/2,200000LL);
    int m = inf.readInt(n-1, max_m, "m");
    inf.readSpace();
    int k = inf.readInt(1, n, "k");
    inf.readEoln();

    for(int i=0;i<m;++i){
        inf.readInt(1, n, "u");
        inf.readSpace();
        inf.readInt(1, n, "v");
        inf.readSpace();
        inf.readInt(1, 1000000000, "w");
        inf.readEoln();
    }

    inf.readEof();
}

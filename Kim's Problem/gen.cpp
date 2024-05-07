#include <bits/stdc++.h>
#include "testlib.h"
#include "aquagenlib.h"
using namespace std;
using ll=long long;
using pii=pair<int,int>;
#define f first
#define s second
#define eb emplace_back

template<class T>
T rnd_min(const T &l,const T &r,const int &t){
    T ret=rnd.next(l,r);
    --t;
    while(t--) ret=min(ret,rnd.next(l,r));
    return ret;
}

template<class T>
T rnd_max(const T &l,const T &r,const int &t){
    T ret=rnd.next(l,r);
    --t;
    while(t--) ret=max(ret,rnd.next(l,r));
    return ret;
}

int main(int argc, char* argv[]){
    registerGen(argc, argv, 1);
    int n=opt<int>(1);

    return 0;
}

/*
gen 200 0 1_ > $
gen 200 0 2_ > $
gen 50 1 3_ > $
gen 50 1 kim > $
gen 50 1 5_ > $
gen 50 1 68_ > $
gen 200 1 7_ > $
gen 200 1 8_ > $
gen 200 1 9_ > $
gen 200 1  10_ > $
*/

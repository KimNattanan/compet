#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;
using ll=long long;
using pii=pair<int,int>;
#define f first
#define s second

template<class T>
T rnd_min(const T &l,const T &r,int t){
    T ret=rnd.next(l,r);
    --t;
    while(t--) ret=min(ret,rnd.next(l,r));
    return ret;
}

template<class T>
T rnd_max(const T &l,const T &r,int t){
    T ret=rnd.next(l,r);
    --t;
    while(t--) ret=max(ret,rnd.next(l,r));
    return ret;
}

int main(int argc, char* argv[]){
    registerGen(argc, argv, 1);
    int sub=opt<int>(1);
    int n,m,k;

    int Q_=50;
    cout<<Q_<<'\n';
    for(int Q=1;Q<=Q_;++Q){
        if(sub==1) n=rnd.next(1,1000), m=rnd.next(1,1000), k=rnd.next(1,1000);
        else n=rnd_max(5001,1000000,5), m=rnd.next(1,1000000), k=rnd.next(1,n);
        cout<<n<<" "<<m<<" "<<k<<'\n';
    }

    return 0;
}

/*
gen 1 0 1_ > $
gen 1 0 2_ > $
gen 1 1 3_ > $
gen 1 1 kim > $
gen 1 1 5_ > $
gen 2 1 68_ > $
gen 2 1 7_ > $
gen 2 1 8_ > $
gen 2 1 9_ > $
gen 2 1  10_ > $
*/
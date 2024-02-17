#include <bits/stdc++.h>
#include "aquagenlib.h"
#include "testlib.h"
using namespace std;

template<class T>
T rnd_min(T l,T r,int t){
    T ret=rnd.next(l,r);
    --t;
    while(t--) ret=min(ret,rnd.next(l,r));
    return ret;
}

int main(int argc, char* argv[]){
    registerGen(argc, argv, 1);
    int sub=opt<int>(1);
    int n=opt<int>(2);
    int k=(sub==1?1:rnd.next(2,n));

    if(sub==2){
        cout<<n<<" "<<n-1<<" "<<k<<'\n';
        for(int i=1;i<n;++i){
            cout<<i<<" "<<i+1<<" "<<rnd.next(1,1000000000)<<'\n';
        }
        return 0;
    }

    int max_m=min(1LL*n*(n-1)/2,200000LL);
    int m=(n==632?max_m:rnd.next(n-1,max_m));
    cout<<n<<" "<<m<<" "<<k<<'\n';
    
    vector<pair<int,int>> edges=gen_connected_graph(n,m);
    for(auto &e:edges){

        cout<<e.first+1<<" "<<e.second+1<<" "<<rnd_min(1,1000000000,4)<<'\n';
    }

    return 0;
}

/*
gen 1 632 1 > $
gen 1 50000 2 > $
gen 1 70000 3 > $
gen 1 100000 4 > $
gen 1 100000 5 > $
gen 1 100000 6 > $
gen 2 50000 7 > $
gen 2 70000 8 > $
gen 2 80000 9 > $
gen 2 100000 10 > $
gen 2 100000 11 > $
gen 2 100000 12 > $
gen 2 100000 13 > $
gen 2 100000 14 > $
gen 3 632 15 > $
gen 3 50000 16 > $
gen 3 70000 17 > $
gen 3 100000 18 > $
gen 3 100000 19 > $
gen 3 100000 20 > $
*/
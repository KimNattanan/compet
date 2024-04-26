#include <bits/stdc++.h>
#include "testlib.h"
#include "aquagenlib.h"
using namespace std;
using pii=pair<int,int>;
#define f first
#define s second

template<class T>
T rnd_min(T l,T r,int t){
    T ret=rnd.next(l,r);
    --t;
    while(t--) ret=min(ret,rnd.next(l,r));
    return ret;
}

template<class T>
T rnd_max(T l,T r,int t){
    T ret=rnd.next(l,r);
    --t;
    while(t--) ret=max(ret,rnd.next(l,r));
    return ret;
}

int main(int argc, char* argv[]){
    registerGen(argc, argv, 1);
    int n=opt<int>(1);
    int k=opt<int>(2);

    cout<<n<<" "<<k<<'\n';
    for(int i=1;i<=n;++i) cout<<rnd.next(0,int(1e9))<<" \n"[i==n];
    vector<pii> edge=gen_edge_tree(n,1,n);
    for(auto &[u,v]:edge) cout<<u+1<<" "<<v+1<<'\n';

    return 0;
}

/*
gen 100000 0 1_ > $
gen 2000 1 2_ > $
gen 2000 1 3_ > $
gen 2000 1 4_ > $
gen 100000 100 5_ > $
gen 100000 100 6_ > $
gen 100000 99999 7_ > $
gen 100000 99999 8_ > $
gen 100000 99999 9_ > $
gen 100000 99999 10_ > $
*/
#include <bits/stdc++.h>
#include "testlib.h"
#include "aquagenlib.h"
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
    
    int n,m,H,S;
    if(sub==2) n=100;
    else n=100000;
    n-=4;
    m=rnd.next(n-1,(int)min(1LL*n*(n-1)>>1,199991LL));
    H=rnd.next(1,n), S=(sub==1?H:rnd.next(1,n));
    vector<pii> edge=gen_connected_graph(n,m);
    for(auto &[u,v]:edge) ++u,++v;
    n+=4;
    cout<<n<<" "<<m+9<<" "<<H<<" "<<S<<'\n';
    for(auto &[u,v]:edge) cout<<u<<" "<<v<<" "<<rnd.next(1,1000000000)<<'\n';
    cout<<H<<" "<<n<<" "<<99<<'\n';
    cout<<H<<" "<<n-1<<" "<<7<<'\n';
    cout<<H<<" "<<n-2<<" "<<99<<'\n';
    cout<<S<<" "<<n<<" "<<1<<'\n';
    cout<<S<<" "<<n-1<<" "<<1<<'\n';
    cout<<S<<" "<<n-2<<" "<<1<<'\n';
    cout<<n-3<<" "<<n<<" "<<1<<'\n';
    cout<<n-3<<" "<<n-1<<" "<<1<<'\n';
    cout<<n-3<<" "<<n-2<<" "<<1<<'\n';

    int Q_=n;
    cout<<Q_<<'\n';
    set<int> s;
    for(int Q=1;Q<=Q_;++Q) cout<<Q<<'\n';

    return 0;
}

/*
gen 1 0 1_ > $
gen 1 0 2_ > $
gen 2 1 3_ > $
gen 2 1 kim > $
gen 2 1 5_ > $
gen 3 1 68_ > $
gen 3 1 7_ > $
gen 3 1 8_ > $
gen 3 1 9_ > $
gen 3 1  10_ > $
*/
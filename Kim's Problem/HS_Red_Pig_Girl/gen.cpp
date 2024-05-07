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
    int n=opt<int>(1);
	int S=opt<int>(2);
	int m=rnd.next(n-1,(n*(n-1))>>1);
	vector<pii> edge=gen_connected_graph(n,m);
    for(auto &[u,v]:edge) ++u,++v;

    cout<<n<<" "<<m<<'\n';
    for(auto &[u,v]:edge) cout<<u<<" "<<v<<" "<<rnd.next(1,int(1e9))<<'\n';

	int Q_(5); cout<<Q_<<'\n';
    for(int Q=1;Q<=5;++Q){
        int K=rnd_max(100000,500000,2);
        cout<<K<<" "<<(Q==1 ? 0 : S)<<'\n';
        if(Q==2){
            int x=rnd.next(1,n);
            for(int i=1;i<=K;++i) cout<<x<<" \n"[i==K];
        }
        else for(int i=1;i<=K;++i) cout<<rnd.next(1,n)<<" \n"[i==K];
        for(int i=1;i<=K;++i) cout<<rnd.next(1,n)<<" \n"[i==K];
    }

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
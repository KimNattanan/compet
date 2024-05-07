#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;
using ll=long long;
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
    int sub=opt<int>(1);
    
	int Q = (sub==3 ? int(1e5) : 100);
	cout<<Q<<'\n';
	while(Q--){
		ll n,l,r;
		if(Q>20) n=rnd.next(1LL,( sub==1 ? ll(1e5) : 1LL<<60 ));
		else n=1e5;
		ll sz=0;
		for(ll i=1;i>0&&i<n;i<<=1) sz|=i;
		if(Q>=20&&Q<=40){
			l=rnd_min(1LL,sz,10);
			r=rnd_max(1LL,sz,10);
		}
		if(sub==2){
			l=rnd_min(1LL,sz,2);
			r=min(sz,l-1+rnd_max(1,100000,3));
		}
		else{
			l=rnd_min(1LL,sz,2);
			r=rnd_max(1LL,sz,2);
		}
		if(r<l) swap(l,r);
		cout<<n<<" "<<l<<" "<<r<<'\n';
	}

    return 0;
}

/*
gen 1 1_ > $
gen 1 2_ > $
gen 2 3_ > $
gen 2 kim > $
gen 2 5_ > $
gen 2 6_ > $
gen 3 7_ > $
gen 3 8_ > $
gen 3 9_ > $
gen 3 0_ > $
*/
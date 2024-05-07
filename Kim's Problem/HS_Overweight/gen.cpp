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
    int n=opt<int>(1);
	
	int Q_(3);
	cout<<Q_<<'\n';
	for(int Q=1;Q<=3;++Q){
		cout<<n<<'\n';
		if(Q==1){
			for(int i=1;i<=n;++i) cout<<1000000LL*i<<" \n"[i==n];
			for(int i=2;i<=n;++i) cout<<1000000<<" \n"[i==n];
		}
		else if(Q==2){
			for(int i=1,x=1;i<=n;++i,x+=2) cout<<x<<" \n"[i==n];
			for(int i=2;i<=n;++i) cout<<1<<" \n"[i==n];
		}
		else{
			for(int i=1;i<=n;++i) cout<<rnd.next(1LL,ll(1e6)*n)<<" \n"[i==n];
			for(int i=2;i<=n;++i) cout<<rnd.next(1,int(1e6))<<" \n"[i==n];
		}
	}

    return 0;
}

/*
gen 1000 1_ > $
gen 1000 2_ > $
gen 1000 3_ > $
gen 500000 kim > $
gen 500000 5_ > $
gen 500000 68_ > $
gen 500000 7_ > $
gen 500000 8_ > $
gen 500000 9_ > $
gen 500000 0_ > $
*/
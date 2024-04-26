#include <bits/stdc++.h>
#include "testlib.h"
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
    int sub=opt<int>(1);
    int n1=opt<int>(2), n2=opt<int>(3);
	int m1=min(5000,n1*(n1-1)>>1), m2=min(5000,n2*(n2-1)>>1);

	set<pii> edge;

	cout<<2<<'\n';
	cout<<n1<<" "<<m1<<'\n';
	for(int i=1;i<=n1;++i) cout<<rnd.next(0,1000000000)<<" \n"[i==n1];
	for(int i=1;i<=n1;++i){
		if(sub==1) cout<<1;
		else cout<<rnd.next(1,5000);
		cout<<" \n"[i==n1];
	}
	while(edge.size()!=m1){
		int u=rnd.next(1,n1);
		int v=rnd.next(1,n1);
		if(u!=v) edge.emplace(min(u,v),max(u,v));
	}
	for(auto &[u,v]:edge) cout<<u<<" "<<v<<'\n';
	edge.clear();
	
	cout<<n2<<" "<<m2<<'\n';
	for(int i=1;i<=n2;++i) cout<<rnd.next(0,1000000000)<<" \n"[i==n2];
	for(int i=1;i<=n2;++i){
		if(sub==1) cout<<1;
		else cout<<rnd.next(1,5000);
		cout<<" \n"[i==n2];
	}
	while(edge.size()!=m2){
		int u=rnd.next(1,n2);
		int v=rnd.next(1,n2);
		if(u!=v) edge.emplace(min(u,v),max(u,v));
	}
	for(auto &[u,v]:edge) cout<<u<<" "<<v<<'\n';

    return 0;
}

/*
gen 1 100 5000 1_ > $
gen 1 100 5000 2_ > $
gen 2 100 5000 3_ > $
gen 2 100 5000 4_ > $
gen 2 100 5000 5_ > $
gen 2 100 5000 6_ > $
gen 2 100 5000 7_ > $
gen 2 100 5000 8_ > $
gen 2 100 5000 9_ > $
gen 2 100 5000 10_ > $
*/
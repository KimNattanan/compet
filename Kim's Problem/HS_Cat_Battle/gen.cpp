#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;

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
    int n=opt<int>(2);
	int m=opt<int>(3);
	cout<<n<<" "<<m<<'\n';

	if(sub==1){
		set<int> s;
		while(s.size()<m) s.emplace(rnd.next((int)1,(int)1000000000));
		int id=0;
		for(auto &e:s){
			++id;
			cout<<id<<" "<<e<<'\n';
		}
		return 0;
	}
	if(sub==2){
		multiset<int> ms;
		set<int> s;
		while(ms.size()<m) ms.emplace(rnd.next((int)1,(int)n));
		while(s.size()<m) s.emplace(rnd.next((int)1,(int)1000000000));
		vector<int> v1,v2;
		for(auto &e:ms) v1.emplace_back(e);
		for(auto &e:s) v2.emplace_back(e);
		for(int i=0;i<m;++i) cout<<v1[i]<<" "<<v2[i]<<'\n';
		return;
	}

	for(int i=0;i<m;++i) cout<<rnd.next((int)1,(int)n)<<" "<<rnd.next((int)1,(int)1000000000)<<'\n';

    return 0;
}

/*
gen 1 500 500 1_ > $
gen 1 317 317 2_ > $
gen 2 500 100000 3_ > $
gen 2 500 100000 4_ > $
gen 3 500 100000 5_ > $
gen 3 500 100000 6_ > $
gen 3 500 100000 7_ > $
gen 3 500 100000 8_ > $
gen 3 500 100000 9_ > $
gen 3 500 100000 10_ > $
*/
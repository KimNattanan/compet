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

int MXW = 1e9;

int main(int argc, char* argv[]){
    registerGen(argc, argv, 1);
    int sub=opt<int>(1);
	
	int n=1000, m=1000;
	if(sub==3) n=m=100;
	cout<<n<<" "<<m<<'\n';
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j) cout<<(sub<3 ? sub : rnd.next(1,MXW))<<" \n"[j==m];
	}

    return 0;
}

/*
gen 1 ags > $
gen 2 sdfg > $
gen 3 y2yh > $
gen 3 suhaj2 > $
gen 3 8uhybj > $
gen 3 kim > $
gen 4 381ty > $
gen 4 9asuh8dvc > $
gen 4 0018_k2 > $
gen 4 -0987vG > $
*/
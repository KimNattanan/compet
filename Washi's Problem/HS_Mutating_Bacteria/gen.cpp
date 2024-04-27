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

	cout<<"5\n";
	cout<<1<<'\n'<<rnd.next(1,10000)<<'\n';
	for(int _=1;_<5;++_){

		int n;
		if(sub==1){
			n=100000;
			cout<<n<<'\n';
			int x=rnd.next(1,10000);
			for(int i=1;i<=n;++i) cout<<x<<" \n"[i==n];
		}
		else if(sub==2){
			n=5000;
			cout<<n<<'\n';
			if(_==1) for(int i=1;i<=n;++i) cout<<i<<" \n"[i==n];
			else for(int i=1;i<=n;++i) cout<<rnd.next(1,10000)<<" \n"[i==n];
		}
		else{
			n=100000;
			cout<<n<<'\n';
			if(_==1){
				int cur=1;
				int z=1;
				for(int i=1;i<=n;++i){
					cout<<cur<<" \n"[i==n];
					cur+=z;
					if(cur==10001) z=-1,cur=9999;
					else if(cur==0) z=1,cur=2;
				}
			}
			else if(_==2){
				int x=rnd.next(2,9999);
				cout<<x-1<<" ";
				for(int i=2;i<n;++i) cout<<x<<" ";
				cout<<x+1<<'\n';
			}
			else for(int i=1;i<=n;++i) cout<<rnd.next(1,10000)<<" \n"[i==n];
		}

	}

    return 0;
}

/*
gen 1 1_ > $
gen 2 2_ > $
gen 2 3_ > $
gen 2 4_ > $
gen 3 5_ > $
gen 3 6_ > $
gen 3 7_ > $
gen 3 8_ > $
gen 3 9_ > $
gen 3 10_ > $
*/
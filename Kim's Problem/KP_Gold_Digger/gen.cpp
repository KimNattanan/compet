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
    int Q=opt<int>(2);

    int p0=-1;
    if(sub==1) p0=0;
    else if(sub==2) p0=rnd.next(0,500);
    
    cout<<Q<<"\n";
    while(Q--){
        int R=rnd.next(1,2000),C=rnd.next(1,2000);
        cout<<R<<" "<<C<<"\n";
        vector<pair<int,int>> vec;
        vector<string> s(R+5);
        for(int i=1;i<=R;++i){
            for(int j=0;j<C;++j){
                int x=rnd.next(1,100);
                if(x<=30) s[i]+="#";
                else if(x<=60) s[i]+="*",vec.emplace_back(i,j+1);
                else s[i]+=".",vec.emplace_back(i,j+1);
            }
            cout<<s[i]<<"\n";
        }

        shuffle(vec.begin(),vec.end(),mt19937_64(10086001));
        int n=rnd.next(1,min((int)vec.size(),1000));
        int W=rnd_max(0,10000,5);
        cout<<n<<" "<<W<<"\n";
        for(int i=0;i<n;++i){
            auto &[a,b]=vec[i];
            int p=p0==-1?rnd.next(0,500):p0;
            cout<<a<<" "<<b<<" "<<p<<"\n";
        }
    }

    return 0;
}

/*
gen 1 1_ > $
gen 1 2_ > $
gen 1 3_ > $
gen 2 4_ > $
gen 2 5_ > $
gen 2 6_ > $
gen 3 7_ > $
gen 3 8_ > $
gen 3 9_ > $
gen 3 10_ > $
gen 3 11_ > $
gen 3 12_ > $
gen 3 13_ > $
gen 3 14_ > $
gen 3 15_ > $
*/
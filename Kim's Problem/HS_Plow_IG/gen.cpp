#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;
using ll=long long;
using pii=pair<int,int>;
#define f first
#define s second
#define eb emplace_back

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

    cout<<"3\n";
    if(sub==1){
        cout<<"5000 1000\n";
        for(int i=1,cur=1;i<=5000;++i,cur=(cur==1000?1:cur+1)) cout<<cur<<" \n"[i==5000];
        for(int i=1;i<=1000;++i) cout<<rnd.next(1,1000000000)<<" \n"[i==1000];
        cout<<"5000 1000\n";
        for(int i=1,cur=1000;i<=5000;++i,cur=(cur==1?1000:cur-1)) cout<<cur<<" \n"[i==5000];
        for(int i=1;i<=1000;++i) cout<<rnd.next(1,1000000000)<<" \n"[i==1000];
        cout<<"5000 1000\n";
        for(int i=1;i<=5000;++i) cout<<rnd.next(1,1000)<<" \n"[i==5000];
        for(int i=1;i<=1000;++i) cout<<rnd.next(1,1000000000)<<" \n"[i==1000];
    }
    else{
        int n=200000,k=1000;
        cout<<"200000 1000\n";
        for(int i=1,cur=1;i<=200000;++i,cur=(cur==1000?1:cur+1)) cout<<cur<<" \n"[i==200000];
        for(int i=1;i<=1000;++i) cout<<rnd.next(1,1000000000)<<" \n"[i==1000];
        cout<<"200000 1000\n";
        for(int i=1,cur=1000;i<=200000;++i,cur=(cur==1?1000:cur-1)) cout<<cur<<" \n"[i==200000];
        for(int i=1;i<=1000;++i) cout<<rnd.next(1,1000000000)<<" \n"[i==1000];
        cout<<"200000 1000\n";
        for(int i=1;i<=200000;++i) cout<<rnd.next(1,1000)<<" \n"[i==200000];
        for(int i=1;i<=1000;++i) cout<<rnd.next(1,1000000000)<<" \n"[i==1000];
    }

    return 0;
}

/*
gen 1 0 1_ > $
gen 1 0 2_ > $
gen 1 1 3_ > $
gen 1 1 kim > $
gen 1 1 5_ > $
gen 2 1 68_ > $
gen 2 1 7_ > $
gen 2 1 8_ > $
gen 2 1 9_ > $
gen 2 1  10_ > $
*/
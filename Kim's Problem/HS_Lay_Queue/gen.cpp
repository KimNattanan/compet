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

    cout<<10<<'\n';
    for(int Q=1;Q<=10;++Q){
        if(Q==10){
            cout<<"1\n"<<rnd.next(1,1000000000)<<'\n';
            continue;
        }
        int n=100000;
        if(sub==1) n=rnd.next(1,100000);
        cout<<n<<'\n';
        if(sub==1) for(int i=1;i<=n;++i) cout<<(int)floor(1e9-sqrt((double)i*(double)i*(double)i))<<" \n"[i==n];
        else if(sub==2){
            int x=rnd.next(1,100000000);
            for(int i=1;i<=n;++i) cout<<x+i<<" \n"[i==n];
        }
        else{
            if(Q==1){
                int x=rnd.next(1,100000000);
                for(int i=1;i<=n;++i) cout<<x+i<<" \n"[i==n];
            }
            else if(Q==2){
                int x=rnd.next(n+5,1000000000);
                for(int i=1;i<=n;++i) cout<<x-i<<" \n"[i==n];
            }
            else if(Q==3){
                int x=rnd.next(1,1000000000);
                for(int i=1;i<=n;++i) cout<<x<<" \n"[i==n];
            }
            else for(int i=1;i<=n;++i) cout<<rnd.next(1,1000000000)<<" \n"[i==n];
        }
    }

    return 0;
}

/*
gen 1 0 1_ > $
gen 1 0 2_ > $
gen 2 1 3_ > $
gen 2 1 kim > $
gen 3 1 5_ > $
gen 3 1 68_ > $
gen 3 1 7_ > $
gen 3 1 8_ > $
gen 3 1 9_ > $
gen 3 1  10_ > $
*/
#include <bits/stdc++.h>
#include "testlib.h"
#include "aquagenlib.h"
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

int a[100005], b[100005];

int main(int argc, char* argv[]){
    registerGen(argc, argv, 1);
    int sub=opt<int>(1);
    int n=opt<int>(2);
    int m=opt<int>(3);

    int x=rnd.next(1,n);
    int Q=m-1;
    if(sub==2||sub==3) Q=0;
    if(sub==1){
        for(int i=1;i<=n;++i){
            if(i==x) a[i]=1, b[i]=1e9;
            else a[i]=rnd.next(2,(int)(1e9)), b[i]=rnd.next(1,(int)(1e9-1));
        }
    }
    else if(sub==2||sub==4){
        for(int i=1;i<=n;++i){
            if(i==x) a[i]=b[i]=1e9;
            else a[i]=rnd.next(1,int(1e9)), b[i]=rnd.next(1,int(1e9));
        }
    }
    else{
        for(int i=1;i<=n;++i){
            a[i]=rnd.next(1,int(1e9)), b[i]=rnd.next(1,int(1e9));
        }
    }

    cout<<n<<" "<<m<<" "<<x<<'\n';
    for(int i=1;i<=n;++i) cout<<a[i]<<" \n"[i==n];
    for(int i=1;i<=n;++i) cout<<b[i]<<" \n"[i==n];

    vector<pii> edge=gen_undirected_graph(n,m);
    for(auto &[u,v]:edge) cout<<(++u)<<" "<<(++v)<<'\n';
    cout<<Q<<'\n';
    vector<int> vec(Q);
    iota(vec.begin(),vec.end(),1);
    shuffle(vec.begin(),vec.end(),mt19937_64(118452759));
    for(int i=1;i<=Q;++i) cout<<vec[i-1]<<" \n"[i==Q];

    return 0;
}

/*
gen 1 100000 200000 1_ > $
gen 2 100000 200000 2_ > $
gen 3 100000 200000 3_ > $
gen 3 100000 200000 4_ > $
gen 4 100000 200000 5_ > $
gen 4 100000 200000 6_ > $
gen 5 100000 200000 7_ > $
gen 5 100000 200000 8_ > $
gen 5 100000 200000 9_ > $
gen 5 100000 200000 10_ > $
*/
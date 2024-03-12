#include "bombs.h"
#include<bits/stdc++.h>
using namespace std;
using ll=long long;

multiset<ll> L,R;
ll t,lz,ans;

void initialize(int N) { return; }

long long max_hp_loss(int X, int T, int A, int P) {
    if(L.empty()){
        t=T;
        L.emplace(X), R.emplace(X);
        return ans=A;
    }

    lz+=(T-t)*P, t=T;
    if(X<*L.rbegin()-lz){
        ans+=X-*L.rbegin()+lz;
        L.emplace(X+lz), L.emplace(X+lz);
        R.emplace(*L.rbegin()-2*lz), L.erase(prev(L.end()));
    }
    else if(X>*R.begin()+lz){
        ans+=*R.begin()+lz-X;
        R.emplace(X-lz), R.emplace(X-lz);
        L.emplace(*R.begin()+2*lz), R.erase(R.begin());
    }
    else L.emplace(X+lz), R.emplace(X-lz);

    return ans+=A;
}
/*
6
30 0 6 1
35 0 10 1
25 1 5 1
10 3 10 20
15 3 7 20
20 3 8 20
*/

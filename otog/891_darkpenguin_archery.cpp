#include<bits/stdc++.h>
using namespace std;
#include "archery.h"
using ll=long long;

long long minPenguinCoin(int N, vector<int> A, vector<int> U, vector<int> D){
    // edit this
    priority_queue<ll> pql;
    priority_queue<ll,vector<ll>,greater<ll>> pqr;
    pql.push(A[0]),pqr.push(A[0]);
    ll lzl=D[0],lzr=U[0],ans=0;
    for(int i=1;i<N;++i){
        if(A[i]<pql.top()-lzl){
            ans+=abs(pql.top()-lzl-A[i]);
            pql.push(A[i]+lzl);
            pql.push(A[i]+lzl);
            pqr.push(pql.top()-lzl-lzr);
            pql.pop();
        }
        else if(A[i]>pqr.top()+lzr){
            ans+=abs(pqr.top()+lzr-A[i]);
            pqr.push(A[i]-lzr);
            pqr.push(A[i]-lzr);
            pql.push(pqr.top()+lzr+lzl);
            pqr.pop();
        }
        else{
            pql.push(A[i]+lzl);
            pqr.push(A[i]-lzr);
        }
        lzl+=D[i];
        lzr+=U[i];
    }
    return ans;
}

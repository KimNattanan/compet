#include "function.h"
#include<bits/stdc++.h>
using namespace std;
// #define endl '\n'
using ll=long long;
using pii=pair<int,int>;
#define f first
#define s second

ll qs[500005],qs2[500005],dp[500005][2];
ll cost(int l,int r){
    return qs2[r]-qs2[l-1]-qs[l-1]*(qs[r]-qs[l-1]);
}
void play(int l,int r,int optl,int optr,bool z){
    if(l>r) return;
    int mid=l+(r-l>>1);
    pair<ll,int> best(LLONG_MAX,0);
    for(int i=optl;i<=min(mid,optr);++i){
        best=min(best,{dp[i-1][!z]+cost(i,mid),i});
    }
    dp[mid][z]=best.f;
    play(l,mid-1,optl,best.s,z),play(mid+1,r,best.s,optr,z);
}

long long minPenguinValue(int N, int M, std::vector<int> A){
    // edit this
    for(int i=1;i<=N;++i) qs[i]=qs[i-1]+ll(A[i-1]),qs2[i]=qs2[i-1]+ll(A[i-1])*qs[i];
    for(int i=1;i<=N;++i) dp[i][1]=cost(1,i);
    for(int i=2;i<=M;++i) play(1,N,1,N,i&1);
    return dp[N][M&1];
}

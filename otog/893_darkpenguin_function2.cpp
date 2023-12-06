// #include "function.h"
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
#define eb emplace_back

ll qs[500005],qs2[500005],dp[2][500005];

struct line{
    ll m,c;
    line(ll m_,ll c_):m(m_),c(c_){}
    ll operator()(ll x){return m*x+c;}
};
struct cv_hull{
    deque<line> dq[2];
    long double f(line a,line b){return (long double)(b.c-a.c)/(a.m-b.m);}
    bool replace(line a,line b,line c){return f(a,b)>=f(b,c);}
    void add(bool k,line x){
        while(dq[k].size()>=2&&replace(dq[k][dq[k].size()-2],dq[k].back(),x)) dq[k].pop_back();
        dq[k].eb(x);
    }
}dp2;

long long minPenguinValue(int N, int M, std::vector<int> A){
    // edit this
    for(int i=1;i<=N;++i){
        qs[i]=qs[i-1]+A[i-1],qs2[i]=qs2[i-1]+1LL*A[i-1]*A[i-1];
        dp[1][i]=qs[i]*qs[i]+qs2[i]>>1;
    }
    for(int k=2;k<=M;++k){
        bool now=k&1,prev=!now;
        int id=0;
        dp2.dq[prev].clear();
        dp2.dq[prev].eb(line(0,0));
        for(int i=1;i<=N;++i){
            id=min(id,(int)dp2.dq[prev].size()-1);
            while(id+1<dp2.dq[prev].size()&&dp2.dq[prev][id](qs[i])>dp2.dq[prev][id+1](qs[i])) ++id;
            dp[now][i]=dp2.dq[prev][id](qs[i])+((qs[i]*qs[i]+qs2[i]>>1));
            dp2.add(prev,line(-qs[i],dp[prev][i]+((qs[i]*qs[i]-qs2[i])>>1)));
        }
    }

    return dp[M&1][N];
}

// int main(){
//     ios::sync_with_stdio(false); cin.tie(0);

//     int n,m; cin>>n>>m;
//     vector<int> vec(n);
//     for(auto &e:vec) cin>>e;
//     cout<<minPenguinValue(n,m,vec);

//     return 0;
// }

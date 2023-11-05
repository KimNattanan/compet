#include<bits/stdc++.h>
using namespace std;
#include "stairs.h"
using ll=long long;
const ll md=1e9+7;

struct matrix{
    vector<vector<ll>> a;
    int n,m;
    matrix(int n_=0,int m_=0){
        n=n_,m=m_;
        a=vector<vector<ll>>(n,vector<ll>(m));
    }
    matrix operator*(const matrix &o)const{
        matrix res(n,o.m);
        for(int i=0;i<n;++i){
            for(int j=0;j<o.m;++j){
                for(int k=0;k<m;++k){
                    res.a[i][j]=(res.a[i][j]+(a[i][k]*o.a[k][j])%md)%md;
                }
            }
        }
        return res;
    }
}m0[65]={matrix(100,100)},m1(100,100),m2(1,100);
ll dp[105];

int countWays(long long N, int M, std::vector<int> S){
    // edit this
    for(auto &e:S) dp[e]=1,m0[0].a[e-1][0]=1;
    for(int i=0;i<99;++i) m0[0].a[i][i+1]=1;
    for(int i=1;i<=100;++i){
        for(auto &e:S) if(e<=i) dp[i]=(dp[i]+dp[i-e])%md;
    }
    if(N<=100) return dp[N];
    N-=100;
    for(int i=1;i<63;++i) m0[i]=m0[i-1]*m0[i-1];
    for(int i=0;i<100;++i) m1.a[i][i]=1;
    for(ll i=0,j=1;i<63&&N;++i,j<<=1) if(j&N) m1=m1*m0[i],N^=j;
    for(int i=0;i<100;++i) m2.a[0][i]=dp[100-i];
    m2=m2*m1;
    return m2.a[0][0];
}

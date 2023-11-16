#include "celeb.h"
#include<bits/stdc++.h>
using namespace std;
using ll=long long;

struct line{
	ll m,c;
	line(ll m_,ll c_):m(m_),c(c_){}
	ll operator()(const ll &x)const{
		return m*x+c;
	}
};
struct cv_hull{
	deque<line> dq;
	long double f(line a,line b){
		return 1.0*(a.c-b.c)/(b.m-a.m);
	}
	bool replace(line a,line b,line c){
		return f(b,c)>=f(a,b);
	}
	void add(line x){
		while(dq.size()>=2&&replace(dq[dq.size()-2],dq.back(),x)) dq.pop_back();
		dq.push_back(x);
	}
	line operator[](const int i)const{
		return dq[i];
	}
}dp;

std::vector<long long> max_revenue(int N, int K, 
				   std::vector<long long> X,
				   std::vector<int> 	M)
{
	for(int i=0;i<N;++i) dp.add(line(-i,X[i]));
	vector<ll> vec(K);
	for(int i=K-1,j=0;i>=0;--i){
		while(j+1<dp.dq.size()&&dp[j](M[i])<=dp[j+1](M[i])) ++j;
		vec[i]=dp[j](M[i]);
	}
	return vec;
}


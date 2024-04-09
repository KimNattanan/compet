#include "gap.h"
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
#define eb emplace_back

long long findGap(int T, int N)
{
	if(T==1){
		ll a=1,b=1e18;
		vector<ll> vec;
		for(int i=0;i<N+1>>1;++i){
			MinMax(a,b,&a,&b);
			if(a==b) vec.eb(a);
			else vec.eb(a++), vec.eb(b--);
		}
		sort(vec.begin(),vec.end());
		ll ans=0;
		for(int i=1;i<vec.size();++i) ans=max(ans,vec[i]-vec[i-1]);
		return ans;
	}
	ll a,b,c,d;
	MinMax(1,1e18,&a,&b);
	if(N==2) return b-a;
	ll ans=(b-a+N-2)/(N-1);
	
	for(ll i=a+ans;i-ans<=b;i+=ans){
		MinMax(a+1,i,&c,&d);
		if(c==-1) continue;
		ans=max(ans,c-a);
		a=d;
	}

	return ans;
}

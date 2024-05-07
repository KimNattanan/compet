/*
	HS_Cat_Box_solution2
*/
#include<bits/stdc++.h>
using namespace std;
using ll=long long;


ll f(ll x,ll num){
	if(x==0 || num==0) return 0;
	int n = 63-__builtin_clzll(num);
	assert((1LL<<n)>0 && x>0 && num>0);
	if((1LL<<n) > x) return f(x, num>>1);
	return (num>>1) + (num&1) + f(x-(1LL<<n), num>>1);
}


int main(){
    ios::sync_with_stdio(false); cin.tie(0);

	
	int Q; cin>>Q;
	while(Q--){
		ll num,l,r; cin>>num>>l>>r;
		cout<< f(r,num) - f(l-1,num) <<'\n';
	}

    return 0;
}
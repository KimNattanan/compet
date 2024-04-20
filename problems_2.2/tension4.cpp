#include<bits/stdc++.h>
using namespace std;
using ll=long long;

ll cal(ll x){
	if(x==0) return 0;
	ll ret=((ll)sqrt(x))+1>>1;
	return ret+cal(x>>1);
}

int main(){
	ios::sync_with_stdio(false); cin.tie(0);

	ll n; cin>>n;
	int Q; cin>>Q;
	while(Q--){
		ll l,r; cin>>l>>r;
		cout<<cal(r)-cal(l-1)<<'\n';
	}

	return 0;
}

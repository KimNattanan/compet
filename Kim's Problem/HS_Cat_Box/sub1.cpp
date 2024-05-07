/*
	HS_Cat_Box_sub1
*/
#include<bits/stdc++.h>
using namespace std;
using ll=long long;

vector<bool> v;
void dfs(ll n){
	if(n==1) return void(v.emplace_back(1));
	dfs(n>>1);
	v.emplace_back(n&1);
	dfs(n>>1);
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

	int Q; cin>>Q;
	while(Q--){
		ll n,l,r; cin>>n>>l>>r;
		v.clear(), dfs(n);
		int ans=0;
		for(int i=l-1;i<r;++i) ans+=v[i];
		cout<<ans<<'\n';
	}

    return 0;
}
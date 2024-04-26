#include<bits/stdc++.h>
using namespace std;
using ll=long long;

const ll md=1e9+7;

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n,m; cin>>n>>m;
	ll ans=1;
    for(int i=0,x;i<m;++i) cin>>x>>x, ans=(ans<<1)%md;
	cout<<(ans-1+md)%md;

    return 0;
}
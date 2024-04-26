#include<bits/stdc++.h>
using namespace std;
using ll=long long;

const ll md=1e9+7;

int cnt[505];

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n,m; cin>>n>>m;
    for(int i=1;i<=m;++i){
		int a,b; cin>>a>>b;
		++cnt[a];
	}
	ll ans=1;
	for(int i=1;i<=n;++i) ans=(ans*(cnt[i]+1))%md;
	cout<<(ans-1+md)%md;

    return 0;
}
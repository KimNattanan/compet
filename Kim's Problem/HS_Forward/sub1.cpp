/*
	HS_Forward
*/
#include<bits/stdc++.h>
using namespace std;
using ll=long long;

int a[5005],b[5005];

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

	int Q; cin>>Q;
	while(Q--){
		int n,m; cin>>n>>m;
		for(int i=1;i<=n;++i) cin>>a[i];
		for(int i=1;i<=n;++i) cin>>b[i];
		for(int i=0;i<m;++i){
			int u,v; cin>>u>>v;
		}
		ll ans=0;
		for(int i=1;i<=n;++i) ans+=a[i];
		cout<<ans<<'\n';
	}

    return 0;
}
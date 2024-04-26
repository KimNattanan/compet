/*
	HS_Abyss-Point_sub_1
*/
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using pii=pair<int,int>;
#define f first
#define s second
#define eb emplace_back

ll a[100005];

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n,k; cin>>n>>k;
	for(int i=1;i<=n;++i) cin>>a[i];
	ll ans=0;
	for(int i=1;i<n;++i){
		int u,v; cin>>u>>v;
		ans+=a[u]+a[v]+min(a[u],a[v]);
	}
	cout<<ans;

    return 0;
}
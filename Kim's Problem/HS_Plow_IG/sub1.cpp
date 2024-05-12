#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const ll md=1e9+7;
#define eb emplace_back

int a[200005];
ll ans[1005],b[1005];

int main(){
	ios::sync_with_stdio(false); cin.tie(0);

	int Q; cin>>Q;
	while(Q--){
		int n,k; cin>>n>>k;
		for(int i=1;i<=n;++i) cin>>a[i];
		for(int i=1;i<=k;++i) cin>>b[i];
		for(int i=1;i<=n;++i){
			int mx=a[i];
			for(int j=i-1;j>0;--j){
				mx=max(mx,a[j]);
				if(a[j]!=a[i] || mx==a[i]) continue;
				ans[mx]=(ans[mx]+b[a[i]])%md;
			}
		}
		for(int i=1;i<=k;++i) cout<<ans[i]<<" \n"[i==k], ans[i]=0;
	}

    return 0;
}
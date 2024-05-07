/*
	HS_Overweight_sub1
*/
#include<bits/stdc++.h>
using namespace std;
using ll=long long;

ll a[500005],pos[500005];

int main(){
	ios::sync_with_stdio(false); cin.tie(0);

	int Q; cin>>Q;
	while(Q--){
		int n; cin>>n;
		for(int i=1;i<=n;++i) cin>>a[i];
		for(int i=2;i<=n;++i) cin>>pos[i], pos[i]+=pos[i-1];
		for(int i=1;i<=n;++i){
			int l=i-1, r=i+1;
			while(l>0&&a[l]<a[i]-(pos[i]-pos[l])) --l;
			while(r<=n&&a[r]<a[i]-(pos[r]-pos[i])) ++r;
			cout<<max(i-l-1, r-i-1)<<" ";
		}
		cout<<'\n';
	}

	return 0;
}
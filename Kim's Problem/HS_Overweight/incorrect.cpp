/*
	HS_Overweight_sub2
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
			int L,R,l,r;
			l=0,r=i-1;
			while(l<r){
				int mid=l+r+1>>1;
				if(a[mid]<a[i]-(pos[i]-pos[mid])) r=mid-1;
				else l=mid;
			}
			L=l;
			l=i+1,r=n+1;
			while(l<r){
				int mid=l+r>>1;
				if(a[mid]<a[i]-(pos[mid]-pos[i])) l=mid+1;
				else r=mid;
			}
			R=l;
			cout<<max(i-L-1, R-i-1)<<" ";
		}
		cout<<'\n';
	}

	return 0;
}
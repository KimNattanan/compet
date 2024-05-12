#include<bits/stdc++.h>
using namespace std;

int main(){
	ios::sync_with_stdio(false); cin.tie(0);

	int n,k; cin>>n>>k;
	int K=1<<k, cnt=0, cnt2=0;
	for(int i=1;i<K;++i){
		for(int j=1;j<K;j<<=1) ++cnt;
	}
	for(int i=1;i<K;++i){
		for(int j=(i-1)&i;j>0;j=(j-1)&1) ++cnt;
	}
	cout<<cnt+n*k<<'\n';
	
	// for(int i=1;i<K;++i){
	// 	for(int j=0;j<n;++j) ++cnt2;
	// }
	// cout<<cnt2<<'\n';

	return 0;
}
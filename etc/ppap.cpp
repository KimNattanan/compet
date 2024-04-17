#include<bits/stdc++.h>
using namespace std;
using ll=long long;

ll len[50]={1};

bool play(int i,ll j){
	if(i==0) return 0;
	ll n=len[i-1];
	if(j<=n) return play(i-1,j);
	if(j==n+1) return 0;
	if(j<=2*n+1) return !play(i-1,j-n-1);
	return play(i-1,j-2*n-1);
}

int main(){
	ios::sync_with_stdio(false); cin.tie(0);

	int m;
	while(len[m]<1e18) ++m, len[m]=len[m-1]*3+1;

	int Q; cin>>Q;
	while(Q--){
		ll n; cin>>n;
		int id=lower_bound(len,len+m+1,n)-len;
		cout<<(play(id,n)?'A':'P')<<'\n';
	}

	return 0;
}

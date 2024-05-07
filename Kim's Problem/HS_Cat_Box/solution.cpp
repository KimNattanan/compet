/*
	HS_Cat_Box
*/
#include<bits/stdc++.h>
using namespace std;
using ll=long long;

ll f(ll n,ll il,ll ir,ll ql,ll qr){
	if(ql<=il && ir<=qr) return n;
	if(il>qr || ir<ql) return 0;
	ll mid=il+(ir-il>>1);
	if(qr<mid) return f(n>>1,il,mid-1,ql,qr);
	if(ql>mid) return f(n>>1,mid+1,ir,ql,qr);
	return f(n>>1,il,mid-1,ql,qr) + (n&1) + f(n>>1,mid+1,ir,ql,qr);
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

	int Q; cin>>Q;
	while(Q--){
		ll n,l,r; cin>>n>>l>>r;
		ll sz=0;
		for(ll i=1;i<=n && i>0;i<<=1) sz|=i;
		cout<<f(n,1,sz,l,r)<<'\n';
	}

    return 0;
}
/*
	HS_Lay_Queue_sub2
*/
#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int Q; cin>>Q;
	while(Q--){
		int n,x; cin>>n;
		for(int i=1;i<=n;++i) cin>>x;
		cout<<min(n,2)<<'\n';
	}

    return 0;
}

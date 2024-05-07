/*
	HS_Overweight
*/
#include<bits/stdc++.h>
using namespace std;
using ll=long long;

ll a[500005],pos[500005];
int lm[500005],rm[500005];
stack<int> st;

int main(){
	ios::sync_with_stdio(false); cin.tie(0);

	int Q; cin>>Q;
	while(Q--){
		int n; cin>>n;
		for(int i=1;i<=n;++i) cin>>a[i];
		for(int i=2;i<=n;++i) cin>>pos[i], pos[i]+=pos[i-1];
		while(!st.empty()) st.pop();
		for(int i=1;i<=n;++i){
			while(!st.empty() && a[i]-(pos[i]-pos[st.top()]) > a[st.top()]) st.pop();
			if(st.empty()) lm[i]=0;
			else lm[i]=st.top();
			st.emplace(i);
		}
		while(!st.empty()) st.pop();
		for(int i=n;i>=1;--i){
			while(!st.empty() && a[i]-(pos[st.top()]-pos[i]) > a[st.top()]) st.pop();
			if(st.empty()) rm[i]=n+1;
			else rm[i]=st.top();
			st.emplace(i);
		}
		for(int i=1;i<=n;++i) cout<<max(i-lm[i]-1,rm[i]-i-1)<<" ";
		cout<<'\n';
	}

	return 0;
}
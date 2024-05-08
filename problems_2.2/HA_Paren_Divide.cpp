/*
	HA_Paren_Divide
*/
#include<bits/stdc++.h>
using namespace std;
#define eb emplace_back

void solve(){
	string s; cin>>s;
	int n=s.size();
	stack<bool> st;
	vector<int> vec;
	int cur=0;
	for(int i=0;i<n;++i){
		if(s[i]=='(') st.emplace(1);
		else if(st.empty()) return void(cout<<0<<'\n');
		else ++cur, st.pop();
		if(st.empty()) vec.eb(cur);
	}
	if(!st.empty()) return void(cout<<0<<'\n');

	int sum=vec.back(), mx=vec[0];
	for(int i=(int)vec.size()-1;i>0;--i){
		vec[i]-=vec[i-1];
		mx=max(mx,vec[i]);
	}
	for(int i=mx;i<=sum;++i){
		if(sum%i) continue;
		int cur=0;
		bool ok=1;
		for(int j=0;j<vec.size();++j){
			cur+=vec[j];
			if(cur>i){
				ok=0;
				break;
			}
			else if(cur==i) cur=0;
		}
		if(ok) return void(cout<<sum/i<<'\n');
	}
}

int main(){
	ios::sync_with_stdio(false); cin.tie(0);

	int Q; cin>>Q;
	while(Q--) solve();

	return 0;
}

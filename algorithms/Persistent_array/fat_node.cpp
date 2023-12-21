#include<bits/stdc++.h>
using namespace std;
#define eb emplace_back
using pii=pair<int,int>;
#define f first
#define s second

struct persistent{
	vector<vector<pii>> vec;
	void init(int n){
		vec=vector<vector<pii>>(n,vector<pii>(1));
	}
	void add(int i,int t,int x){
		vec[i].eb(t,x+vec[i].back().s);
	}
	int qr(int i,int t){
		int id=upper_bound(vec[i].begin(),vec[i].end(),pii(t,INT_MAX))-vec[i].begin()-1;
		return vec[i][id].s;
	}
};

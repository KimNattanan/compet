#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#include "marble.h"

using A=bitset<505>;

A basis[505];
int n,cnt;

void insert_vec(A &v,bool val){
	v[n]=val;
	++cnt;
	for(int i=0;i<n;++i){
		if(!v[i]) continue;
		if(basis[i].none()) return void(basis[i]=v);
		v^=basis[i];
	}
}
bool check_vec(A v){
	for(int i=0;i<n;++i){
		if(!v[i]) continue;
		if(basis[i].none()) return 1;
		v^=basis[i];
	}
	return 0;
}
 
std::vector<int> guess_marble(int N) {
	// edit this
	int MX=min(41,N);
	n=N;

	A tmp;
	tmp[0]=1;
	insert_vec(tmp,0);
	for(int i=MX;i>=1&&cnt<N;--i){
		arrange(i);
		for(int j=i-1;j>=0&&cnt<N;--j){
			for(int k=0;k<N;++k) tmp[k]=(k%i==j);
			if(check_vec(tmp)) insert_vec(tmp,query(j)&1);
		}
	}
	for(int j=N-1;j>0;--j){
		if(!basis[j][N]) continue;
		for(int i=j-1;i>=0;--i) basis[i][N]=basis[i][N]^(basis[j][N]&basis[i][j]);
	}
	vector<int> ans(N);
	for(int i=0;i<N;++i) ans[i]=basis[i][N];
 
	return ans;
}

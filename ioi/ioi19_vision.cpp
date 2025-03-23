#include "vision.h"
#include<bits/stdc++.h>
using namespace std;
#define eb emplace_back

vector<int> v1[405], v2[405];
int v1_or[405], v2_or[405];
int v1_qor[405], v2_qor[405];

int play(int H,int W,int K){
	vector<int> vec;
	for(int i=K;i<=H+W-2;++i){
		vec.eb(add_and({v1_or[i],v1_qor[i-K]}));
		vec.eb(add_and({v2_or[i],v2_qor[i-K]}));
	}
	return add_or(vec);
}
void construct_network(int H, int W, int K) {
	for(int i=0;i<H;++i) for(int j=0;j<W;++j) v1[i+j].eb(W*i+j), v2[i-j+W-1].eb(W*i+j);
	for(int i=0;i<=H+W-2;++i){
		v1_or[i]=add_or(v1[i]), v2_or[i]=add_or(v2[i]);
		if(i==0) v1_qor[i]=v1_or[i], v2_qor[i]=v2_or[i];
		else v1_qor[i]=add_or({v1_or[i],v1_qor[i-1]}), v2_qor[i]=add_or({v2_or[i],v2_qor[i-1]});
	}
	if(H+W-2==K) play(H,W,K);
	else add_and({play(H,W,K),add_not(play(H,W,K+1))});
}

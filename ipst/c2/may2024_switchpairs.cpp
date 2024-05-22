#include "switchpairs.h"
#include<bits/stdc++.h>
using namespace std;
using pii=pair<int,int>;
using ll=long long;
#define f first
#define s second
#define eb emplace_back

int timer=0;
const int MX_timer=15000;
int ask(vector<int> vec){
	if(++timer>MX_timer) assert(0);
	return control_switches(vec);
}

int N,N2;
vector<int> unused;
vector<pii> ans;
vector<int> fix(vector<int> vec){
	for(auto &[a,x]:ans) vec[a]=x;
	return vec;
}
void insert_ans(int a,int x){
	ans.eb(a,x);
	unused.erase(lower_bound(unused.begin(),unused.end(),a));
}

void all(bool x,int now){
	vector<int> vec(N2);
	int l=0, r=unused.size()-1;
	while(l<r){
		int mid=l+r>>1;
		for(int i=0;i<unused.size();++i) vec[unused[i]]=x^(i>mid);
		if(ask(fix(vec))>now) r=mid;
		else l=mid+1;
	}
	insert_ans(unused[l],x);
	l=0, --r;
	while(l<r){
		int mid=l+r+1>>1;
		for(int i=0;i<unused.size();++i) vec[unused[i]]=x^(i<mid);
		if(ask(fix(vec))>now) l=mid;
		else r=mid-1;
	}
	insert_ans(unused[l],x);
}

void solve(int N_){
	N=N_, N2=N<<1;
	vector<int> vec(N2),_1(N2,1),_0(N2,0);
	unused.resize(N2);
	iota(unused.begin(),unused.end(),0);
	vector<int> bits(10);
	for(int now=0;now<N;++now){
		if(ask(fix(_0))>now){ all(0,now); continue; }
		if(ask(fix(_1))>now){ all(1,now); continue; }
		int bit,msk,state;
		iota(bits.begin(),bits.end(),0);
		shuffle(bits.begin(),bits.end(),mt19937(0));
		for(auto &e:bits){
			bit=e, msk=1<<e;
			state=0;
			for(int j=0;j<N2;++j) vec[j]=bool(j&msk);
			if(ask(fix(vec))>now) break;
			state=1;
			if(e==bits.back()) break;
			for(int j=0;j<N2;++j) vec[j]=!vec[j];
			if(ask(fix(vec))>now) break;
		}
		int l=0, r=unused.size()-1;
		while(l<r){
			int mid=l+r>>1;
			for(int i=0;i<unused.size();++i) vec[unused[i]]=(i>mid)^state^bool(unused[i]&msk);
			if(ask(fix(vec))>now) r=mid;
			else l=mid+1;
		}
		insert_ans(unused[l],state^bool(unused[l]&msk));
		l=0, --r;
		while(l<r){
			int mid=l+r+1>>1;
			for(int i=0;i<unused.size();++i) vec[unused[i]]=(i<mid)^state^bool(unused[i]&msk);
			if(ask(fix(vec))>now) l=mid;
			else r=mid-1;
		}
		insert_ans(unused[l],state^bool(unused[l]&msk));
	}
	ask(fix(vec));
}

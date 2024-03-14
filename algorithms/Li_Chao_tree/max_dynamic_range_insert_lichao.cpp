#include <bits/stdc++.h>
using namespace std;
#include "particle.h"
using ll=long long;
#define eb emplace_back
 
const ll inf=LLONG_MAX>>1;
 
struct line{
	ll m,c;
	line(ll m=0,ll c=0):m(m),c(c){}
	ll operator()(const ll &x)const{return m*x+c;}
};
struct lichao{
	line f;
	int l,r;
	vector<lichao> child;
	lichao(int l=0,int r=0):l(l),r(r),f(0,-inf){}
	inline void flush(){
		if(l+1==r||child.size()) return;
		child.eb(l,l+r>>1), child.eb(l+r>>1,r);
	}
	inline void upd1(int l0,int r0,line f2){
		if(l>=r0||r<=l0) return;
		if(f(l0)>=f2(l0) && f(r0)>=f2(r0)) return;
		if(l0<=l&&r<=r0) return upd2(f2);
		flush();
		child[0].upd1(l0,r0,f2), child[1].upd1(l0,r0,f2);
	}
	inline void upd2(line f2){
		int mid=l+r>>1;
		bool bl=f(l)<f2(l);
		bool bm=f(mid)<f2(mid);
		bool br=f(r)<f2(r);
		if(bm) swap(f,f2);
		if(f2.c==-inf||l+1==r) return;
		flush();
		if(bl!=bm) child[0].upd2(f2);
		else if(br!=bm) child[1].upd2(f2);
	} 
	inline ll qr(ll x){
		if(child.empty()) return f(x);
		if(x>=(l+r>>1)) return max(f(x),child[1].qr(x));
		return max(f(x),child[0].qr(x));
	}
}t;

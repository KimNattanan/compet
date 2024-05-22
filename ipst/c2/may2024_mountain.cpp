#include<bits/stdc++.h>
using namespace std;
using pii=pair<int,int>;
using ll=long long;
#define f first
#define s second
#define eb emplace_back
#include "mountain.h"

ll a[100005];

struct segment{
	ll sum[1<<18];
	int lz[1<<18],l0,r0;
	void build(int l,int r){ l0=l,r0=r; }
	void flush(int i,int il,int ir){
		if(!lz[i]) return;
		if(il!=ir) lz[i<<1]+=lz[i], lz[i<<1|1]+=lz[i];
		sum[i]+=lz[i]*(a[ir]-a[il-1]);
		lz[i]=0;
	}
	void upd(int i,int il,int ir,int l,int r,int x){
		flush(i,il,ir);
		if(l<=il&&ir<=r) return lz[i]+=x, flush(i,il,ir);
		if(il>r||ir<l) return;
		int mid=il+ir>>1;
		upd(i<<1,il,mid,l,r,x), upd(i<<1|1,mid+1,ir,l,r,x);
		sum[i]=sum[i<<1]+sum[i<<1|1];
	}
	ll qr(int i,int il,int ir,int l,int r){
		flush(i,il,ir);
		if(l<=il&&ir<=r) return sum[i];
		if(il>r||ir<l) return 0LL;
		int mid=il+ir>>1;
		return qr(i<<1,il,mid,l,r)+qr(i<<1|1,mid+1,ir,l,r);
	}
	void upd(int l,int r,int x){ upd(1,l0,r0,l,r,x); }
	ll qr(int l,int r){ return qr(1,l0,r0,l,r); }
};


int lh[100005],rh[100005];
vector<int> adj[100005],A,C;


int p[100005],big[100005],head[100005],tour[100005],id;
int dfs(int u,int p){
	int szu=1,mx=0;
	::p[u]=p;
	big[u]=-1;
	for(auto &v:adj[u]){
		int szv=dfs(v,u);
		szu+=szv;
		if(szv>mx) mx=szv, big[u]=v;
	}
	return szu;
}
void decomp(int u,int h){
	tour[u]=++id;
	head[u]=h;
	a[id]=a[id-1]+A[u]-(p[u]==-1 ? 0 : A[p[u]]);
	if(big[u]!=-1) decomp(big[u],h);
	for(auto &v:adj[u]) if(v!=big[u]) decomp(v,v);
}


ll cost;
segment t_red,t_blue;
void add_red(int u,int x){
	t_red.upd(tour[head[u]],tour[u],x);
	cost+=x*t_blue.qr(tour[head[u]],tour[u]);
	if(p[head[u]]!=-1) add_red(p[head[u]],x);
}
void add_blue(int u,int x){
	t_blue.upd(tour[head[u]],tour[u],x);
	cost+=x*t_red.qr(tour[head[u]],tour[u]);
	if(p[head[u]]!=-1) add_blue(p[head[u]],x);
}


void initialize(int N, std::vector<int> A, std::vector<int> C) {
	::A=A, ::C=C;
	stack<int> st;
	int rt=-1;
	for(int i=0;i<N;++i) lh[i]=rh[i]=-1;
	for(int i=0;i<N;++i){
		while(!st.empty()&&A[st.top()]<A[i]) st.pop();
		if(rt==-1) rt=i;
		else if(st.empty()) lh[i]=rt, rt=i;
		else lh[i]=rh[st.top()], rh[st.top()]=i;
		st.emplace(i);
	}
	for(int i=0;i<N;++i){
		if(lh[i]!=-1) adj[i].eb(lh[i]);
		if(rh[i]!=-1) adj[i].eb(rh[i]);
	}
	dfs(rt,-1);
	decomp(rt,rt);
	t_red.build(1,id), t_blue.build(1,id);
	for(int i=0;i<N;++i){
		if(C[i]==1) add_red(i,1);
		else if(C[i]==2) add_blue(i,1);
	}
	// Fill your code here
}

long long race_cost(int S, int X) {
	if(C[X]==1) add_red(X,-1);
	else if(C[X]==2) add_blue(X,-1);
	if(S==1) add_red(X,1);
	else if(S==2) add_blue(X,1);
	C[X]=S;
	return cost;
	// Fill your code here
}

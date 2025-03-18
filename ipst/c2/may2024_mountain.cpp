#include "mountain.h"
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using pii=pair<int,int>;
#define f first
#define s second
#define eb emplace_back
#define sz(x) (int)x.size()
#define add(x,y) ((x+y)%md)
#define Add(x,y) (x=add(x,y))
#define mul(x,y) ((x*y)%md)
#define Mul(x,y) (x=mul(x,y))
const int inf=1e9;
const ll linf=1e18;
const ll md=1e9+7;

struct Segment{
	ll a[1<<18],*qs;
	int lz[1<<18],l0,r0;
	void init(int l,int r,ll qs_[]){ l0=l,r0=r,qs=qs_; }
	void flush(int i,int il,int ir){
		if(!lz[i]) return;
		if(il!=ir) lz[i<<1]+=lz[i], lz[i<<1|1]+=lz[i];
		a[i]+=lz[i]*(qs[ir]-qs[il-1]);
		lz[i]=0;
	}
	void upd(int i,int il,int ir,int l,int r,int x){
		flush(i,il,ir);
		if(il>r||ir<l) return;
		if(l<=il&&ir<=r) return lz[i]+=x, flush(i,il,ir);
		int mid=il+ir>>1;
		upd(i<<1,il,mid,l,r,x), upd(i<<1|1,mid+1,ir,l,r,x);
		a[i]=a[i<<1]+a[i<<1|1];
	}
	void upd(int l,int r,int x){ upd(1,l0,r0,l,r,x); }
	ll qr(int i,int il,int ir,int l,int r){
		flush(i,il,ir);
		if(il>r||ir<l) return 0;
		if(l<=il&&ir<=r) return a[i];
		int mid=il+ir>>1;
		return qr(i<<1,il,mid,l,r) + qr(i<<1|1,mid+1,ir,l,r);
	}
	ll qr(int l,int r){ return qr(1,l0,r0,l,r); }
};

int tl[100005],tr[100005],rt;
struct HLD{
	int sz[100005],pa[100005],big[100005],op[100005],ed[100005],h[100005],id;
	ll qs[100005];
	Segment t[2];
	void dfs(int u,int p){
		big[u]=-1;
		sz[u]=1;
		pa[u]=p;
		for(auto &v:{tl[u],tr[u]})if(v!=-1){
			dfs(v,u);
			sz[u]+=sz[v];
			if(big[u]==-1 || sz[big[u]]<sz[v]) big[u]=v;
		}
	}
	void decomp(int u,int p){
		op[u]=++id;
		h[u]=p;
		if(big[u]!=-1) decomp(big[u],p);
		for(auto &v:{tl[u],tr[u]}) if(v!=-1 && v!=big[u]) decomp(v,v);
		ed[u]=id;
	}
	void init(int rt,vector<int> &A){
		dfs(rt,-1), decomp(rt,rt);
		t[0].init(1,id,qs), t[1].init(1,id,qs);
		for(int i=0;i<sz(A);++i) qs[op[i]]=A[i]-(pa[i]==-1? 0 : A[pa[i]]);
		for(int i=1;i<=id;++i) qs[i]+=qs[i-1];
	}
	void upd(int u,int c,ll x){
		t[c-1].upd(op[h[u]],op[u], x);
		if(pa[h[u]]!=-1) upd(pa[h[u]],c,x);
	}
	ll qr(int u,int c){
		if(pa[h[u]]!=-1) return t[c-1].qr(op[h[u]],op[u]) + qr(pa[h[u]],c);
		return t[c-1].qr(op[h[u]],op[u]);
	}
}hld;

int col[100005];
ll ans;
void set_color(int u,int c){
	if(col[u]==c) return;
	if(col[u]){
		hld.upd(u,col[u],-1);
		ans-=hld.qr(u,3-col[u]);
	}
	if(!(col[u]=c)) return;
	hld.upd(u,c,1);
	ans+=hld.qr(u,3-c);
}

void initialize(int N, std::vector<int> A, std::vector<int> C) {
	// Fill your code here
	stack<int> st;
	for(int i=0;i<N;++i){
		tl[i]=tr[i]=-1;
		while(!st.empty() && A[i]>A[st.top()]) tl[i]=st.top(), st.pop();
		if(st.empty()) rt=i;
		else tr[st.top()]=i;
		st.emplace(i);
	}
	hld.init(rt,A);
	for(int i=0;i<N;++i) set_color(i,C[i]);
	return ;
}

long long race_cost(int S, int X) {
	// Fill your code here
	set_color(X,S);
	return ans;
}

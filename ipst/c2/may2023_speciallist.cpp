#include "speciallist.h"
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
#define eb emplace_back
using pii=pair<int,int>;
#define f first
#define s second
const ll md=1e9+7;

struct segment{
	int cnt[1<<18],val[1<<18];
	int l0,r0;
	void init(int l,int r){l0=l,r0=r;}
	void upd(int i,int il,int ir,int id,int v){
		if(il==ir){
			cnt[i]+=v;
			val[i]=(val[i]+1LL*v*id*id)%md;
			return;
		}
		int im=il+ir>>1;
		if(id<=im) upd(i<<1,il,im,id,v);
		else upd(i<<1|1,im+1,ir,id,v);
		cnt[i]=cnt[i<<1]+cnt[i<<1|1];
		val[i]=(val[i<<1]+val[i<<1|1])%md;
	}
	void upd(int id,int v){upd(1,l0,r0,id,v);}
	pii qr(int i,int il,int ir,int l,int r){
		if(l>r) return {0,0};
		if(l<=il&&ir<=r) return {cnt[i],val[i]};
		if(ir<l||il>r) return {0,0};
		int im=il+ir>>1;
		pii L=qr(i<<1,il,im,l,r), R=qr(i<<1|1,im+1,ir,l,r);
		return {L.f+R.f, (L.s+R.s)%md};
	}
	pii qr(int l,int r){return qr(1,l0,r0,l,r);}
}t;

int big[100005],sz[100005],N;
vector<int> adj[100005],X,ans;

void dfs_add(int u,int val){
	t.upd(X[u],val);
	for(auto &v:adj[u]) dfs_add(v,val);
}
void dfs_ans(int u,int &val){
	auto [cnt0,val0]=t.qr(0,X[u]-1);
	auto [cnt1,val1]=t.qr(X[u]+1,100000);
	val=((val+1LL*cnt0*X[u]*X[u]-val0-1LL*cnt1*X[u]*X[u]+val1)%md+md)%md;
	for(auto &v:adj[u]) dfs_ans(v,val);
}
void dfs(int u){
	if(big[u]==-1) return void(t.upd(X[u],1));
	for(auto &v:adj[u]){
		if(v==big[u]) continue;
		dfs(v);
		dfs_add(v,-1);
	}
	dfs(big[u]);
	for(auto &v:adj[u]){
		if(v==big[u]) continue;
		ans[u]=(1LL*ans[u]+ans[v]-ans[N]+md)%md;
		dfs_ans(v,ans[u]);
		dfs_add(v,1);
	}
	ans[u]=(1LL*ans[u]+ans[big[u]]-ans[N]+md)%md;
	auto [cnt0,val0]=t.qr(0,X[u]-1);
	auto [cnt1,val1]=t.qr(X[u]+1,100000);
	ans[u]=((ans[u]+1LL*cnt0*X[u]*X[u]-val0-1LL*cnt1*X[u]*X[u]+val1)%md+md)%md;
	t.upd(X[u],1);
}

std::vector<int> compute_cost(int N,
			      int M,
			      std::vector<int> P,
			      std::vector<int> X,
			      std::vector<int> Z)
{
	::X=X, ::N=N;
	ans.assign(N+1,0);
	t.init(0,100000);
	t.upd(Z[0],1);
	for(int i=1;i<M;++i){
		auto [cnt0,val0]=t.qr(0,Z[i]-1);
		auto [cnt1,val1]=t.qr(Z[i]+1,100000);
		ans[N]=((ans[N]+1LL*cnt0*Z[i]*Z[i]-val0-1LL*cnt1*Z[i]*Z[i]+val1)%md+md)%md;
		t.upd(Z[i],1);
	}
	for(int i=0;i<N;++i){
		big[i]=-1;
		sz[i]=1;
		auto [cnt0,val0]=t.qr(0,X[i]-1);
		auto [cnt1,val1]=t.qr(X[i]+1,100000);
		ans[i]=((ans[N]+1LL*cnt0*X[i]*X[i]-val0-1LL*cnt1*X[i]*X[i]+val1)%md+md)%md;
	}
	for(int i=N-1;i>0;--i){
		adj[P[i]].eb(i);
		sz[P[i]]+=sz[i];
		if(big[P[i]]==-1||sz[i]>sz[big[P[i]]]) big[P[i]]=i;
	}
	for(auto &e:Z) t.upd(e,-1);
	dfs(0);
	ans.pop_back();
	return ans;
}

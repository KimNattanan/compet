#include "upanddown.h"
#include<bits/stdc++.h>
using namespace std;
using pii=pair<int,int>;
using ll=long long;
#define f first
#define s second
#define eb emplace_back

const ll md=1e9+7;

struct segment{
	ll a[1<<20];
	int l0,r0;
	void build(int l,int r){l0=l, r0=r;}
	void upd1(int i,int il,int ir,int id,ll v){
		if(il==ir) return void(a[i]=(a[i]+v)%md);
		int mid=il+ir>>1;
		if(id<=mid) upd1(i<<1,il,mid,id,v);
		else upd1(i<<1|1,mid+1,ir,id,v);
		a[i]=(a[i<<1]+a[i<<1|1])%md;
	}
	ll qr(int i,int il,int ir,int l,int r){
		if(l>r) return 0;
		if(l<=il&&ir<=r) return a[i];
		if(il>r||ir<l) return 0;
		int mid=il+ir>>1;
		return (qr(i<<1,il,mid,l,r)+qr(i<<1|1,mid+1,ir,l,r))%md;
	}
	void upd1(int id,ll v){upd1(1,l0,r0,id,v);}
	ll qr(int l,int r){return qr(1,l0,r0,l,r);}
}dp[4];

struct segment2{
	struct node{
		node *l,*r;
		int sum;
		node(int sum=0):sum(sum),l(nullptr),r(nullptr){}
	};
	using pnode=node*;
	pnode rt[200005];
	int l0,r0;
	void build(pnode &t,int il,int ir){
		t=new node();
		if(il==ir) return;
		int mid=il+ir>>1;
		build(t->l,il,mid), build(t->r,mid+1,ir);
	}
	void build(int l,int r){
		l0=l, r0=r;
		build(rt[0],l,r);
	}
	void upd(pnode t0,pnode &t1,int il,int ir,int id,int x){
		t1=new node(*t0);
		if(il==ir) return void(t1->sum+=x);
		int mid=il+ir>>1;
		if(id<=mid) upd(t0->l,t1->l,il,mid,id,x);
		else upd(t0->r,t1->r,mid+1,ir,id,x);
		t1->sum=(t1->l->sum)+(t1->r->sum);
	}
	void upd(int v0,int v1,int id,int x){upd(rt[v0],rt[v1],l0,r0,id,x);}
	int qr(pnode t0,pnode t1,int il,int ir,int l,int r){
		if(l<=il&&ir<=r) return t1->sum-t0->sum;
		if(il>r||ir<l) return 0;
		int mid=il+ir>>1;
		return qr(t0->l,t1->l,il,mid,l,r)+qr(t0->r,t1->r,mid+1,ir,l,r);
	}
	int qr(int v0,int v1,int l,int r){return l>r ? 0 : qr(rt[v0],rt[v1],l0,r0,l,r);}
}t;

ll add(const ll &x,const ll &y){ return ((x+y)%md+md)%md; }
vector<int> pos[200005];

long long upanddown(int N,
		    std::vector<int> X)
{
	vector<int> comp=X;
	sort(comp.begin(),comp.end());
	comp.erase(unique(comp.begin(),comp.end()),comp.end());
	for(auto &e:X) e=lower_bound(comp.begin(),comp.end(),e)-comp.begin()+1;
	int n=comp.size();

	for(int i=0;i<4;++i) dp[i].build(1,n);
	ll ans=0;
	for(int i=0;i<N;++i){
		ans=add(ans,dp[3].qr(X[i]+1,n));
		dp[3].upd1(X[i],dp[2].qr(X[i]+1,n));
		dp[2].upd1(X[i],dp[1].qr(1,X[i]-1));
		dp[1].upd1(X[i],dp[0].qr(1,X[i]-1));
		dp[0].upd1(X[i],1);
	}

	t.build(1,n);
	for(int i=1;i<=N;++i) t.upd(i-1,i,X[i-1],1), pos[X[i-1]].eb(i);
	for(int i=1;i<=n;++i){
		if(pos[i].size()<=1) continue;
		ll sum=0;

		vector<ll> u,d;
		d.eb(t.qr(0,pos[i][0],1,i-1)), u.eb(t.qr(0,pos[i][0],i+1,n));
		for(int j=1;j<pos[i].size();++j) d.eb(t.qr(pos[i][j-1],pos[i][j],1,i-1)), u.eb(t.qr(pos[i][j-1],pos[i][j],i+1,n));
		d.eb(t.qr(pos[i].back(),N,1,i-1)), u.eb(t.qr(pos[i].back(),N,i+1,n));

		ll b=(d[0]*u[1])%md,a=(2*d[0]+d[1])%md,c=d[0]+d[1],sumd=-d[0]-d[1];
		for(auto &e:d) sumd+=e;
		for(int j=2;j<=pos[i].size();++j){
			sum=add(sum,(b*sumd)%md);
			sumd-=d[j];
			b=(b+a*u[j])%md;
			c=c+d[j];
			a=(a+c)%md;
		}
		ans=add(ans,-sum);
	}

	return ans;
}

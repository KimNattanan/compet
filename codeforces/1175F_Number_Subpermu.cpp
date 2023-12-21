#include<bits/stdc++.h>
using namespace std;
using ll=long long;
#define eb emplace_back
using pii=pair<int,int>;
#define f first
#define s second

mt19937_64 rng(time(0));
ll rnd[300005],qsi[300005],qsa[300005],a[300005];
ll ans;
vector<ll> comp;

struct persist{
	vector<vector<pii>> vec;
	void init(int n){
		vec=vector<vector<pii>>(n,vector<pii>(1,pii(-1,0)));
	}
	void add(int i,int t,int x){
		vec[i].eb(t,x+vec[i].back().s);
	}
	int qr(int i,int t){
		int id=upper_bound(vec[i].begin(),vec[i].end(),pii(t,INT_MAX))-vec[i].begin()-1;
		return vec[i][id].s;
	}
}cnt;

struct segment{
	vector<segment> child;
	int l,r,mid,mx;
	segment(int l_=0,int r_=0):l(l_),r(r_),mid(l+(r-l>>1)){}
	void build(){
		if(l==r) return void(mx=l);
		child.eb(l,mid),child.eb(mid+1,r);
		child[0].build(),child[1].build();
		if(a[child[0].mx]>a[child[1].mx]) mx=child[0].mx;
		else mx=child[1].mx;
	}
	int qr(int l0,int r0){
		if(l0<=l&&r<=r0) return mx;
		if(l>r0||r<l0) return 0;
		int i0=child[0].qr(l0,r0),i1=child[1].qr(l0,r0);
		if(a[i0]>a[i1]) return i0;
		return i1;
	}
}t;

void play(int l,int r){
	if(l>r) return;
	int i=t.qr(l,r);
	if(r-i<i-l){
		for(int j=i;j<=r;++j){
			int id=lower_bound(comp.begin(),comp.end(),qsa[j]-qsi[a[i]])-comp.begin();
			if(id>=comp.size()||comp[id]!=(qsa[j]-qsi[a[i]])) continue;
			int x=cnt.qr(id,i-1);
			if(l>1) x-=cnt.qr(id,l-2);
			ans+=x;
		}
	}
	else{
		for(int j=l-1;j<i;++j){
			int id=lower_bound(comp.begin(),comp.end(),qsa[j]+qsi[a[i]])-comp.begin();
			if(id>=comp.size()||comp[id]!=(qsa[j]+qsi[a[i]])) continue;
			int x=cnt.qr(id,r)-cnt.qr(id,i-1);
			ans+=x;
		}
	}
	play(l,i-1),play(i+1,r);
}

int main(){
	ios::sync_with_stdio(false);cin.tie(0);
	
	int n; cin>>n;
	for(int i=1;i<=n;++i){
		rnd[i]=rng();
		qsi[i]=qsi[i-1]+rnd[i];
	}
	comp.eb(qsa[0]);
	for(int i=1;i<=n;++i){
		cin>>a[i];
		qsa[i]=qsa[i-1]+rnd[a[i]];
		comp.eb(qsa[i]);
	}
	sort(comp.begin(),comp.end());
	comp.erase(unique(comp.begin(),comp.end()),comp.end());

	cnt.init(comp.size()+5);
	cnt.add(lower_bound(comp.begin(),comp.end(),qsa[0])-comp.begin(),0,1);
	for(int i=1;i<=n;++i){
		cnt.add(lower_bound(comp.begin(),comp.end(),qsa[i])-comp.begin(),i,1);
	}

	t=segment(1,n);
	t.build();
	
	play(1,n);
	cout<<ans;

	return 0;
}

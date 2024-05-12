#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const ll md=1e9+7;
#define eb emplace_back

int a[200005];
vector<int> pos[1005];
ll ans[1005],b[1005];

struct segment{
	int mx[1<<19],l0,r0;
	void build(int i,int il,int ir){
		if(il==ir) return void(mx[i]=il);
		int mid=il+ir>>1;
		build(i<<1,il,mid), build(i<<1|1,mid+1,ir);
		mx[i] = a[mx[i<<1]]>a[mx[i<<1|1]] ? mx[i<<1] : mx[i<<1|1];
	}
	void build(int l,int r){ l0=l,r0=r, build(1,l,r); }
	int qr(int i,int il,int ir,int l,int r){
		if(l<=il&&ir<=r) return mx[i];
		if(il>r||ir<l) return 0;
		int mid=il+ir>>1;
		int vl=qr(i<<1,il,mid,l,r), vr=qr(i<<1|1,mid+1,ir,l,r);
		if(!vl||!vr) return vl?vl:vr;
		return a[vl]>a[vr] ? vl : vr;
	}
	int qr(int l,int r){return qr(1,l0,r0,l,r);}
}t;

void play(int l,int r){
	if(l>=r) return;
	int mx=t.qr(l,r);
	for(int i=l;i<mx;++i) ans[a[mx]]=(ans[a[mx]] + (upper_bound(pos[a[i]].begin(),pos[a[i]].end(),r)-upper_bound(pos[a[i]].begin(),pos[a[i]].end(),mx))*b[a[i]] )%md;
	play(l,mx-1), play(mx+1,r);
}

int main(){
	ios::sync_with_stdio(false); cin.tie(0);

	int Q; cin>>Q;
	while(Q--){
		int n,k; cin>>n>>k;
		for(int i=1;i<=n;++i) cin>>a[i], pos[a[i]].eb(i);
		for(int i=1;i<=k;++i) cin>>b[i];
		t.build(1,n);
		play(1,n);
		for(int i=1;i<=k;++i) cout<<ans[i]<<" \n"[i==k], ans[i]=0, pos[i].clear();
	}

	return 0;
}
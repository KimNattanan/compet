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
		if(il==ir) return void(mx[i]=a[il]);
		int mid=il+ir>>1;
		build(i<<1,il,mid), build(i<<1|1,mid+1,ir);
		mx[i]=max(mx[i<<1],mx[i<<1|1]);
	}
	void build(int l,int r){ l0=l,r0=r, build(1,l,r); }
	int qr(int i,int il,int ir,int l,int r){
		if(l<=il&&ir<=r) return mx[i];
		if(il>r||ir<l) return 0;
		int mid=il+ir>>1;
		return max(qr(i<<1,il,mid,l,r),qr(i<<1|1,mid+1,ir,l,r));
	}
	int qr(int l,int r){return qr(1,l0,r0,l,r);}
}t;

int main(){
	ios::sync_with_stdio(false); cin.tie(0);

	int Q; cin>>Q;
	while(Q--){
		int n,k; cin>>n>>k;
		for(int i=1;i<=n;++i) cin>>a[i], pos[a[i]].eb(i);
		for(int i=1;i<=k;++i) cin>>b[i];
		t.build(1,n);
		for(int i=1;i<=k;++i){
			int n=pos[i].size();
			for(int l=0;l<n;++l){
				for(int r=l+1;r<n;++r){
					int mx=t.qr(pos[i][l],pos[i][r]);
					if(mx!=i) ans[mx]=(ans[mx]+b[i])%md;
				}
			}
		}
		for(int i=1;i<=k;++i) cout<<ans[i]<<" \n"[i==k], ans[i]=0, pos[i].clear();
	}

    return 0;
}
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const ll md=1e9+7;
#define eb emplace_back

int a[200005],lh[200005],rh[200005];
vector<int> pos[1005];
ll ans[1005],b[1005];

void play(int mx,int l,int r){
	if(l>=r) return;
	if(mx-l < r-mx) for(int i=l;i<mx;++i) ans[a[mx]]=(ans[a[mx]] + (upper_bound(pos[a[i]].begin(),pos[a[i]].end(),r)-upper_bound(pos[a[i]].begin(),pos[a[i]].end(),mx))*b[a[i]] )%md;
	else for(int i=mx+1;i<=r;++i) ans[a[mx]]=(ans[a[mx]] + (lower_bound(pos[a[i]].begin(),pos[a[i]].end(),mx)-lower_bound(pos[a[i]].begin(),pos[a[i]].end(),l))*b[a[i]] )%md;
	play(lh[mx],l,mx-1), play(rh[mx],mx+1,r);
}

int main(){
	ios::sync_with_stdio(false); cin.tie(0);

	int Q; cin>>Q;
	while(Q--){
		int n,k; cin>>n>>k;
		for(int i=1;i<=n;++i) cin>>a[i], pos[a[i]].eb(i), lh[i]=rh[i]=0;
		for(int i=1;i<=k;++i) cin>>b[i];
		stack<int> st;
		st.emplace(0);
		for(int i=1;i<=n;++i){
			while(st.top()>0 && a[st.top()]<a[i]) st.pop();
			lh[i]=rh[st.top()];
			rh[st.top()]=i;
			st.emplace(i);
		}
		play(rh[0],1,n);
		for(int i=1;i<=k;++i) cout<<ans[i]<<" \n"[i==k], ans[i]=0, pos[i].clear();
	}

	return 0;
}
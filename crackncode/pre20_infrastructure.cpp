#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using db=double;
using ld=long double;
using pii=pair<int,int>;
#define f first
#define s second
#define eb emplace_back
#define sz(x) (int)(x).size()

vector<int> adj[100005], nds[100005];
ll a[100005], b[100005], mnb[100005], sumb, dp[100005];
int lv[100005],mxlv,qscnt[100005];
queue<int> q;
priority_queue<ll> pq;

int main(){
	ios::sync_with_stdio(false); cin.tie(0);

	int n,m,s,Q; cin>>n>>m>>s>>Q;
	for(int i=1;i<=n;++i) cin>>a[i];
	for(int i=0,u,v;i<m;++i) cin>>u>>v, adj[u].eb(v), adj[v].eb(u);
	q.emplace(s);
	while(!q.empty()){
		int u=q.front(); q.pop();
		nds[lv[u]].eb(u), mxlv=lv[u], ++qscnt[lv[u]];
		for(auto &v:adj[u]) if(v!=s&&!lv[v]) lv[v]=lv[u]+1, q.emplace(v);
	}

	for(int i=mxlv;i>=1;--i){
		for(auto &e:nds[i]) pq.emplace(a[e]);
		sumb+=(b[i]=pq.top()), pq.pop();
	}
	for(int i=1;i<=mxlv;++i) mnb[i]=(i==1?b[i]:min(mnb[i-1],b[i])), qscnt[i]+=qscnt[i-1];
	qscnt[mxlv+1]=qscnt[mxlv];
	mnb[mxlv+1]=0;
	for(int i=mxlv+1;i>=1;--i) dp[i]=dp[i+1]-mnb[i]*(qscnt[i-1]-(i==1?0:qscnt[i-2]));


	while(Q--){
		int t; cin>>t;
		if(t==1){
			int x,y; cin>>x>>y;
			int lvx=lv[x]+1;
			if(lvx>mxlv) cout<<sumb+y<<'\n';
			else if(mnb[lvx]<y) cout<<sumb-mnb[lvx]+y<<'\n';
			else cout<<sumb<<'\n';
		}
		else{
			ll y; cin>>y;
			int l=1,r=mxlv+1;
			while(l<r){
				int mid=l+r>>1;
				if(mnb[mid]<y) r=mid;
				else l=mid+1;
			}
			ll ans=(l==1?1LL*n*(sumb+y):1LL*qscnt[l-2]*sumb+1LL*(n-qscnt[l-2])*(sumb+y));
			cout<<ans+dp[l]<<'\n';
		}
	}

	return 0;
}

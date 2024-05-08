/*
	HA_Fuel_up
*/
#include<bits/stdc++.h>
using namespace std;
using pii=pair<int,int>;
#define f first
#define s second
#define eb emplace_back

using A=pair<pii,pii>;

vector<pii> adj[50005];
pii d[2][50005];
priority_queue<A,vector<A>,greater<A>> pq;

void dijk(int n, int mid){
	for(int i=0;i<n;++i) d[0][i]=d[1][i]={1e9,0};
	d[0][0]={0,0};
	pq.emplace(pii(0,0),pii(0,0));
	while(!pq.empty()){
		pii w=pq.top().f;
		int u=pq.top().s.f;
		int used=pq.top().s.s;
		pq.pop();
		for(auto &vw:adj[u]){
			if(!used && d[1][vw.f]>pii(w.f,mid)){
				d[1][vw.f]=pii(w.f,mid);
				pq.emplace(d[1][vw.f],pii(vw.f,1));
			}
			if(vw.s>mid) continue;
			pii w2={w.f,w.s+vw.s};
			if(w2.s>mid) w2={w2.f+1,vw.s};
			if(d[used][vw.f]>w2){
				d[used][vw.f]=w2;
				pq.emplace(w2,pii(vw.f,used));
			}
		}
	}
}

int main(){
	ios::sync_with_stdio(false); cin.tie(0);

	int n,m,t,q; cin>>n>>m>>t>>q;
	for(int i=0;i<m;++i){
		int u,v,w; cin>>u>>v>>w;
		adj[u].eb(v,w), adj[v].eb(u,w);
	}
	int l=0,r=1e9;
	while(l<r){
		int mid=l+r>>1;
		dijk(n,mid);
		if(d[q][n-1].f>t) l=mid+1;
		else r=mid;
	}
	cout<<l;

	return 0;
}

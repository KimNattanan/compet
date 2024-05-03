/*
	HS_Sadako
*/
#include<bits/stdc++.h>
using namespace std;
#define eb emplace_back
using ll=long long;
using pii=pair<int,int>;
#define f first
#define s second

pii dif[]={
{-1,0},
{-1,-1},
{-1,1},
{-2,0}
};

struct A{
	ll w;
	int w2;
	pii u;
	A(ll w,int w2,int x,int y):w(w),w2(w2),u(x,y){}
	A(ll w,int w2,pii u):w(w),w2(w2),u(u){}
	bool operator<(const A &o)const{
		return w>o.w;
	}
};
int a[1005][1005];
ll d[1005][1005];
priority_queue<A> pq;

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

	int n,m; cin>>n>>m;
	for(int i=0;i<n;++i){
		for(int j=0;j<m;++j){
			cin>>a[i][j];
			d[i][j]=1e18;
		}
	}
	ll ans=1e18;
	d[0][0]=0;
	pq.emplace(0,0,0,0);
	while(!pq.empty()){
		ll w=pq.top().w;
		int w2=pq.top().w2;
		pii u=pq.top().u;
		pq.pop();
		if(u.s==m-1){
			int x=((n-1-w2)%n+n)%n;
			ans=min(ans,w+(x-u.f+n)%n);
		}
		for(int i=0;i<4;++i){
			pii v={(u.f+dif[i].f+n)%n, u.s+dif[i].s};
			if(v.s<0||v.s>=m) continue;
			if(d[v.f][v.s]<=w+a[v.f][v.s]) continue;
			d[v.f][v.s]=w+a[v.f][v.s];
			pq.emplace(d[v.f][v.s], w2+1, v);
		}
	}
	cout<<ans;

    return 0;
}
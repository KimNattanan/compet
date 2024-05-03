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
int a[205][205];
ll d[205][205][205];
priority_queue<A> pq;

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

	int n,m; cin>>n>>m;
	for(int i=0;i<n;++i){
		for(int j=0;j<m;++j){
			cin>>a[i][j];
			for(int k=0;k<n;++k) d[i][j][k]=1e18;
		}
	}
	ll ans=1e18;
	d[0][0][0]=0;
	pq.emplace(0,0,0,0);
	while(!pq.empty()){
		ll w=pq.top().w;
		int w2=pq.top().w2;
		int w3=(w2+1)%n;
		pii u=pq.top().u;
		pq.pop();
		for(int i=0;i<4;++i){
			pii v={(u.f+dif[i].f+n)%n, u.s+dif[i].s};
			if(v.s<0||v.s>=m) continue;
			if(d[v.f][v.s][w3]<=w+a[v.f][v.s]) continue;
			d[v.f][v.s][w3]=w+a[v.f][v.s];
			pq.emplace(d[v.f][v.s][w3], w3, v);
		}
	}
	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j){
			ans=min(ans,d[i][m-1][j]+ (((n-1-j)%n+n)%n-i+n)%n );
		}
	}
	cout<<ans;

    return 0;
}
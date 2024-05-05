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

pii dif[]={
{1,0},
{0,-1},
{0,1},
{-1,0}
};

int a[1005][1005];
ll d[1005][1005];
using A=pair<ll,pii>;
priority_queue<A,vector<A>,greater<A>> pq;

int main(){
	ios::sync_with_stdio(false); cin.tie(0);

    int n,m,ci,cj; cin>>n>>m>>ci>>cj;
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j){
            cin>>a[i][j];
            d[i][j]=1e18;
        }
    }
    d[ci][cj]=a[ci][cj];
    pq.emplace(a[ci][cj],pii(ci,cj));
    while(!pq.empty()){
        ll w=pq.top().f;
        pii u=pq.top().s;
        pq.pop();
        if(d[u.f][u.s]!=w) continue;
        for(int i=0;i<4;++i){
            pii v(u.f+dif[i].f, u.s+dif[i].s);
            if(v.f<1||v.s<1||v.f>n||v.s>m) continue;
            if(d[v.f][v.s]<=w+a[v.f][v.s]) continue;
            d[v.f][v.s]=w+a[v.f][v.s];
            pq.emplace(d[v.f][v.s],v);
        }
    }
    ll mn=min({d[1][1],d[1][m],d[n][1],d[n][m]})-a[ci][cj];
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j) cout<<d[i][j]+mn<<" \n"[j==m];
    }

	return 0;
}

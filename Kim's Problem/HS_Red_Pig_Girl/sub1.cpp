/*
	HS_Red_Pig_Girl_sub1
*/
#include<bits/stdc++.h>
using namespace std;
#define eb emplace_back
using ll=long long;

const int N=200, N2=500000;

ll d[N+5][N+5];
int a[N2+5], b[N2+5];

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

	int n(N),m; cin>>n>>m;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j) d[i][j]=1e18;
		d[i][i]=0;
	}
	for(int i=0;i<m;++i){
		int u,v,w(1e9); cin>>u>>v>>w;
		d[u][v]=d[v][u]=min(d[u][v],(ll)w);
	}
	for(int k=1;k<=n;++k){
		for(int i=1;i<=n;++i){
			for(int j=1;j<=n;++j) d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
		}
	}
	
	int Q(5); cin>>Q;
	while(Q--){
		int n2(N2), S; cin>>n2>>S;
		ll sum=0;
		for(int i=1;i<=n2;++i) cin>>a[i];
		for(int i=1;i<=n2;++i) cin>>b[i];
		for(int i=1;i<=n2;++i) sum+=d[a[i]][b[i]];
		cout<<sum<<'\n';
	}

    return 0;
}
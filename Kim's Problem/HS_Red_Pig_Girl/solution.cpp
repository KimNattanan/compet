/*
	HS_Red_Pig_Girl
*/
#include<bits/stdc++.h>
using namespace std;
#define eb emplace_back
using ll=long long;

const int N=200, N2=500000;

ll d[N+5][N+5], mx[N+5][N+5];
int a[N2+5], b[N2+5];
bool ok[N+5][N+5];

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

	int n(N),m(100000); cin>>n>>m;
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
		for(int i=1;i<=n;++i){
			for(int j=1;j<=n;++j) mx[i][j]=-1e18, ok[i][j]=0;
		}
		int n2(N2), S; cin>>n2>>S;
		ll sum=0;
		for(int i=1;i<=n2;++i) cin>>a[i];
		for(int i=1;i<=n2;++i) cin>>b[i];
		for(int i=1;i<=n2;++i){
			sum+=d[a[i]][b[i]];
			ok[a[i]][b[i]]=1;
		}
		ll ans=sum;
		if(!S){
			cout<<ans<<'\n';
			continue;
		}
		for(int j=1;j<=n;++j){
			for(int x=1;x<=n;++x){
				if(!ok[j][x]) continue;
				for(int i=1;i<=n;++i) mx[i][j]=max(mx[i][j], d[i][x]-d[j][x]);
			}
		}
		for(int i=1;i<=n;++i){
			for(int k=1;k<=n;++k){
				if(!ok[i][k]) continue;
				for(int j=1;j<=n;++j) ans=max(ans, sum+d[j][k]-d[i][k]+mx[i][j]);
			}
		}
		cout<<ans<<'\n';
	}

    return 0;
}
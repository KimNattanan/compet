/*
	HS_Red_Pig_Girl_sub2
*/
#include<bits/stdc++.h>
using namespace std;
#define eb emplace_back
using ll=long long;

const int N=200, N2=500000;

ll d[N+5][N+5];
int a[N2+5], b[N2+5];
bool ok[N+5][N+5];

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
		for(int i=1;i<=n;++i){
			for(int j=1;j<=n;++j) ok[i][j]=0;
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
		for(int i=1;i<=n;++i){
			for(int j=1;j<=n;++j){
				if(!ok[i][j]) continue;
				for(int k=1;k<=n;++k){
					if(i==k) continue;
					for(int l=1;l<=n;++l){
						if(j==l) continue;
						if(!ok[k][l]) continue;
						ans=max(ans,sum-d[i][j]-d[k][l]+d[i][l]+d[k][j]);
					}
				}
			}
		}
		cout<<ans<<'\n';
	}

    return 0;
}
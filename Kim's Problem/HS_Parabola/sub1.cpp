/*
	HS_Parabola_Hill_sub1
*/
#include<bits/stdc++.h>
using namespace std;
using pii=pair<int,int>;
#define f first
#define s second

const int MXH=1000;

int a[100005], ans[1005];
bitset<1005> used;

int play(int u,int d,bool ok){
	int mx=0;
	for(int v=u-1;v>0;--v){
		if(a[v]-a[u]<=d&&a[v]!=a[u]&&(ok||a[v]-a[u]>0)) mx=max(mx,play(v,a[v]-a[u],ok|(a[v]-a[u]>0)));
	}
	if(mx==0&&d>=0) return -1e9;
	return mx+1;
}

int main(){
	ios::sync_with_stdio(false); cin.tie(0);

    int n,Q; cin>>n>>Q;
	for(int i=1;i<=n;++i) cin>>a[i];
	for(int i=n;i>=1;--i){
		if(used[a[i]]) continue;
		ans[a[i]]=max(0,play(i,1e9,0));
		used[a[i]]=1;
	}

	while(Q--){
		int x; cin>>x;
		cout<<ans[x]<<'\n';
	}

	return 0;
}

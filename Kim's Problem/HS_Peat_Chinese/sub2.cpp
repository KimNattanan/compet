#include<bits/stdc++.h>
using namespace std;
using ll=long long;

ll dist[100005],ans[100005];

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n,m,k; cin>>n>>m>>k;
    for(int i=1;i<=m;++i){
        int u,v,w; cin>>u>>v>>w;
        dist[i+1]=dist[i]+w;
    }
    ll mx=dist[k];
    for(int i=k+1;i<=n;++i){
        mx=max(mx,dist[i]-dist[i-k+1]);
        ans[i]=dist[i]-mx;
    }
    for(int i=1;i<=n;++i) cout<<ans[i]<<'\n';

}
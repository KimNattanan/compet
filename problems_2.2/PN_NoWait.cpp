#include<bits/stdc++.h>
using namespace std;
using ll=long long;

int V[500005],deg[500005];
ll val[500005],dp[500005];

void dfs(int u,int U){
    deg[u]=-1;
    int v=V[u];
    V[u]=U;
    if(u!=U) val[U]+=val[u];
    if(v!=U) dfs(v,U);
}

void solve(){
    int n; cin>>n;
    for(int i=1;i<=n;++i){
        cin>>V[i]>>val[i];
        ++deg[V[i]];
    }
    int k; cin>>k;

    /// find topo order
    queue<int> q;
    for(int i=1;i<=n;++i){
        if(deg[i]==0) q.emplace(i);
    }
    vector<int> topo;
    while(q.size()){
        int u=q.front(); q.pop();
        topo.emplace_back(u);
        if(--deg[V[u]]==0) q.emplace(V[u]);
    }
    
    /// compress cycle
    for(int i=1;i<=n;++i){
        if(deg[i]==1) dfs(i,i), topo.emplace_back(i);
    }
    for(int i=1;i<=n;++i){
        if(deg[i]==0&&deg[V[i]]==-1) V[i]=V[V[i]];
    }

    /// create dp in topo order
    priority_queue<ll> pq;
    for(auto &u:topo){
        dp[u]+=val[u];
        if(V[u]==u || dp[V[u]]>=dp[u]) pq.emplace(dp[u]);
        else pq.emplace(dp[V[u]]), dp[V[u]]=dp[u];
    }
    ++k;
    ll ans=0;
    while(pq.size()&&k--) ans+=pq.top(), pq.pop();
    cout<<ans<<'\n';
    
    for(int i=1;i<=n;++i) dp[i]=deg[i]=0;
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int Q; cin>>Q;
    while(Q--) solve();

    return 0;
}

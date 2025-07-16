#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll=long long;
using pii=pair<int,int>;
#define f first
#define s second
#define eb emplace_back

const int inf=1e9;

vector<int> adj[100005];
int mask[100005];
vector<int> edge;
int dp[1<<20];

void dfs(int u,int p){
    for(auto &v:adj[u]){
        if(v==p) continue;
        dfs(v,u);
        mask[u]^=mask[v];
        edge.eb(mask[v]);
    }
}

void solve(){
    int n; cin>>n;
    for(int i=1;i<=n;++i){
        adj[i].clear();
        mask[i]=0;
    }
    edge.clear();
    for(int i=1;i<n;++i){
        int u,v; cin>>u>>v;
        adj[u].eb(v),adj[v].eb(u);
    }
    int k; cin>>k;
    for(int i=0;i<k;++i){
        int u,v; cin>>u>>v;
        mask[u]^=(1<<i);
        mask[v]^=(1<<i);
    }
    dfs(1,1);
    sort(edge.begin(),edge.end());
    edge.erase(unique(edge.begin(),edge.end()),edge.end());
    int K=1<<k;
    dp[0]=0;
    for(int i=1;i<K;++i) dp[i]=inf;
    for(int i=0;i<K;++i){
        if(dp[i]==inf) continue;
        for(auto &e:edge){
            dp[i|e]=min(dp[i|e],dp[i]+1);
        }
    }
    cout<<dp[K-1]<<endl;
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int Q(1);
    cin>>Q;
    while(Q--){
        solve();
    }
}

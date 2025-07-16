#include<bits/stdc++.h>
using namespace std;
#define eb emplace_back

int n, k, dp[1000005][3];
vector<int> adj[1000005];

void dfs(int u,int lv){
    if(adj[u].empty()){
        dp[u][0] = lv-k;
        dp[u][1] = dp[u][2] = 1;
        return;
    }
    dp[u][0] = lv;
    for(auto &v:adj[u]){
        dfs(v,lv+1);
        if(dp[v][0]>lv) continue;
        dp[u][1] += dp[v][1];
        dp[u][0] = min(dp[u][0], dp[v][0]);
    }
    for(auto &v:adj[u]){
        if(dp[v][0]>lv) dp[u][2] = max(dp[u][2], dp[u][1]+dp[v][2]);
        else dp[u][2] = max(dp[u][2], dp[u][1]-dp[v][1]+dp[v][2]);
    }
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> n >> k;
    for(int i=2;i<=n;++i){
        int x; cin>>x;
        adj[x].eb(i);
    }
    dfs(1,1);
    cout << dp[1][2];
}

#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define ll long long
#define pii pair<int,int>
#define f first
#define s second
#define pb push_back

const int md=1e9+7;
const int inf=1e9+7;

vector<int> adj[100005];
ll dp[100005][3],ans;
int n;

void dfs(int u,int p){
    dp[u][0]=1;
    dp[u][1]=dp[u][2]=-1;
    for(auto &v:adj[u]){
        if(v!=p){
            dfs(v,u);
            dp[u][0]+=dp[v][0];
            if(dp[u][2]==-1||dp[dp[u][2]][0]<dp[v][0]) dp[u][2]=v;
            if(dp[u][1]==-1||dp[dp[u][2]][0]>dp[dp[u][1]][0]) swap(dp[u][1],dp[u][2]);
        }
    }
    ll sz0=n-dp[u][0];
    for(auto &v:adj[u]){
        if(v==p||dp[v][1]==-1) continue;
        ans=max(ans,dp[dp[v][1]][0]*sz0);
        if(v!=dp[u][1]) ans=max(ans,dp[dp[v][1]][0]*dp[dp[u][1]][0]);
        else if(dp[u][2]!=-1) ans=max(ans,dp[dp[v][1]][0]*dp[dp[u][2]][0]);
    }
}

int32_t main(){
    ios::sync_with_stdio(false); cin.tie(0);

    cin>>n;
    for(int i=0;i<n-1;++i){
        int u,v; cin>>u>>v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    dfs(1,1);
    cout<<ans<<endl;

    return 0;
}

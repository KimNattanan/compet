#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define ll long long
#define pii pair<int,int>
#define f first
#define s second
#define pb push_back

//#define int ll

int n,k;
vector<int> adj[100005];
int C[100005];
int dp[100005][25];
int dp2[100005][25];

void dfs1(int u,int p){
    for(int i=0;i<=k;i++){
        dp[u][i]=C[u];
    }
    for(auto v:adj[u]){
        if(v!=p){
            dfs1(v,u);
            for(int i=1;i<=k;i++) dp[u][i]+=dp[v][i-1];
        }
    }
}
void dfs2(int u,int p){
    for(auto v:adj[u]){
        if(v!=p){
            for(int i=1;i<=k;i++){
                dp2[v][i]=dp[u][i-1]+dp2[u][i-1];
                if(i>1) dp2[v][i]-=dp[v][i-2];
            }
            dfs2(v,u);
        }
    }
}

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0);

    cin>>n>>k;
    for(int i=0;i<n-1;i++){
        int u,v; cin>>u>>v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    for(int i=1;i<=n;i++){
        cin>>C[i];
    }

    dfs1(1,1);
    dfs2(1,1);
    for(int u=1;u<=n;u++){
        cout<<dp2[u][k]+dp[u][k]<<endl;
    }

    return 0;
}
/**
5 3
1 2
2 5
2 3
3 4
1
1
1
1
1
*/

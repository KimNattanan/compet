#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll=long long;
using pii=pair<int,int>;
#define f first
#define s second
#define eb emplace_back

vector<int> adj[200005];
int dp[200005],sz[200005];

void dfs(int u){
    sz[u]=1;
    dp[u]=0;
    pii mx(-1,0);
    int sum=0;
    for(auto &v:adj[u]){
        dfs(v);
        sz[u]+=sz[v];
        dp[u]+=dp[v];
        mx=max(mx,pii(sz[v]-(dp[v]<<1),v));
        sum+=sz[v]-(dp[v]<<1);
    }
    if(mx.f==-1) return;
    if(mx.f<=(sum>>1)) dp[u]+=(sum>>1);
    else{
        int x=sum-mx.f;
        mx.f-=sum-mx.f;
        dp[u]+=x+min(mx.f>>1,dp[u]-dp[mx.s]);
    }
}

void solve(){

    int n; cin>>n;
    for(int i=1;i<=n;++i) adj[i].clear();
    for(int i=2;i<=n;++i){
        int x; cin>>x;
        adj[x].eb(i);
    }
    dfs(1);
    cout<<dp[1]<<endl;

}

int32_t main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int Q(1);
    cin>>Q;
    while(Q--){
        solve();
    }

    return 0;
}

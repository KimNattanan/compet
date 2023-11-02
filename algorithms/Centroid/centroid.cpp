#include<bits/stdc++.h>
using namespace std;
#define pb push_back


vector<int> adj[200005];
int ans[200005];
int sz[200005];
bool vis[200005];

void dfs_sz(int u,int p){
    sz[u]=1;
    for(auto &v:adj[u]){
        if(v!=p&&!vis[v]){
            dfs_sz(v,u);
            sz[u]+=sz[v];
        }
    }
}
int centroid(int u,int p,int n){
    for(auto &v:adj[u]){
        if(v!=p&&!vis[v]&&sz[v]>(n>>1)) return centroid(v,u,n);
    }
    return u;
}

void decomp(int u,int p){
    dfs_sz(u,u);
    int c=centroid(u,u,sz[u]);
    vis[c]=1;

    // ...

    for(auto &v:adj[c]){
        if(!vis[v]){
            decomp(v,c);
        }
    }
}


int32_t main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n; cin>>n;
    for(int i=0;i<n-1;++i){
        int u,v; cin>>u>>v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    memset(ans,0x3f,sizeof ans);

    decomp(1,-1);

    // ...

    return 0;
}

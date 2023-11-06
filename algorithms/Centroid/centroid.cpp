#include<bits/stdc++.h>
using namespace std;
#define pb push_back

vector<int> adj[100005];
bool vis[100005];
int sz[100005];

int dfs_sz(int u,int p){
    sz[u]=1;
    for(auto &v:adj[u]){
        if(v!=p&&!vis[v]) sz[u]+=dfs_sz(v,u);
    }
    return sz[u];
}

int centroid(int u,int p,int n){
    for(auto &v:adj[u]){
        if(v!=p&&!vis[v]&&sz[v]>n) return centroid(v,u,n);
    }
    return u;
}

void decomp(int u,int p){
    int c=centroid(u,u,dfs_sz(u,u)>>1);
    vis[c]=1;

    //...

    for(auto &v:adj[u]){
        if(!vis[v]) decomp(v,c);
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

    decomp(1,-1);

    return 0;
}

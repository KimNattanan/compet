#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define ll long long
#define pii pair<int,int>
#define f first
#define s second
#define pb push_back

const int inf=1e9+7;

int k;
vector<pii> adj[200005];
int sz[200005];
bool vis[200005];
int have[1000005];
int ans=inf;
void dfs_sz(int u,int p){
    sz[u]=1;
    for(auto &vw:adj[u]){
        if(vw.f!=p&&!vis[vw.f]){
            dfs_sz(vw.f,u);
            sz[u]+=sz[vw.f];
        }
    }
}
int centroid(int u,int p,int n){
    for(auto &vw:adj[u]){
        if(vw.f!=p&&!vis[vw.f]&&sz[vw.f]>(n>>1)) return centroid(vw.f,u,n);
    }
    return u;
}
int tempp;
void dfs_ans(int u,int p,int d,int w,bool z){
    if(z){
        tempp=max(tempp,w);
        if(have[w]==-1) have[w]=d;
        else have[w]=min(have[w],d);
    }
    else{
        if(have[k-w]!=-1){
            ans=min(ans,d+have[k-w]);
        }
    }
    if(d>=ans) return;
    for(auto &vw:adj[u]){
        if(vw.f!=p&&!vis[vw.f]&&w+vw.s<=k) dfs_ans(vw.f,u,d+1,w+vw.s,z);
    }
}
void decomp(int u,int p){
    dfs_sz(u,u);
    int c=centroid(u,u,sz[u]);
    vis[c]=1;

    tempp=1;
    for(auto &vw:adj[c]){
        if(!vis[vw.f]&&vw.s<=k){
            dfs_ans(vw.f,c,1,vw.s,0);
            dfs_ans(vw.f,c,1,vw.s,1);
        }
    }
    fill(have+1,have+tempp+2,-1);

    for(auto &vw:adj[c]){
        if(!vis[vw.f]) decomp(vw.f,c);
    }
}

int32_t main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n; cin>>n>>k;
    for(int i=0;i<n-1;++i){
        int u,v,w; cin>>u>>v>>w; ++u,++v;
        adj[u].pb({v,w});
        adj[v].pb({u,w});
    }
    memset(have,-1,sizeof have);
    have[0]=0;
    decomp(1,-1);
    if(ans>=inf) cout<<-1;
    else cout<<ans;

    return 0;
}

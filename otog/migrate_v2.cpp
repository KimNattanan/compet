#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define pii pair<int,int>
#define f first
#define s second
#define pb push_back
#define ll long long

#define int ll

const int md=1e9+7;

vector<int> adj[100005];
int W[100005];
bool vis[100005];
int sz[100005];
int ans[100005];
vector<int> vec[100005];
int cnt[100005];
int k;

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
int mx;
void dfs_ans(int u,int p,int d,vector<int> &vec,bool z){
    if(z){
        bool ok=0;
        if(vec.size()<=d) vec.pb(W[u]),ok=1;
        else vec[d]+=W[u];
    }
    else{
        ans[u]+=cnt[min(mx,k-d)];
        ans[u]-=vec[min((int)(vec.size())-1,k-d)];
    }
    if(d>=k) return;
    for(auto &v:adj[u]){
        if(v!=p&&!vis[v]){
            dfs_ans(v,u,d+1,vec,z);
        }
    }
}
void dfs_sub(int u,int p,int d,int U){
    ans[U]+=W[u];
    if(d>=k) return;
    for(auto &v:adj[u]){
        if(v!=p&&!vis[v]) dfs_sub(v,u,d+1,U);
    }
}
void decomp(int u,int p){
    dfs_sz(u,u);
    int c=centroid(u,u,sz[u]);
    vis[c]=1;

    int idx=0;
    for(auto &v:adj[c]){
        if(!vis[v]){
            vec[idx].pb(0);
            dfs_ans(v,c,1,vec[idx++],1);
        }
    }
    mx=-1;
    for(int i=0;i<idx;++i){
        for(int j=1;j<vec[i].size();++j){
            cnt[j]+=vec[i][j];
            vec[i][j]+=vec[i][j-1];
            mx=max(mx,j);
        }
    }
    cnt[0]=W[c];
    for(int j=1;j<=mx;++j) cnt[j]+=cnt[j-1];
    idx=0;
    for(auto &v:adj[c]){
        if(!vis[v]){
            dfs_ans(v,c,1,vec[idx++],0);
        }
    }
    dfs_sub(c,c,0,c);
    for(int i=0;i<idx;++i) vec[i].clear();
    for(int i=1;i<=mx;++i) cnt[i]=0;

    for(auto &v:adj[c]){
        if(!vis[v]) decomp(v,c);
    }
}

int32_t main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n; cin>>n>>k;
    for(int i=0;i<n-1;++i){
        int u,v; cin>>u>>v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    for(int i=1;i<=n;++i) cin>>W[i];
    decomp(1,-1);
    for(int i=1;i<=n;++i) cout<<ans[i]<<endl;

    return 0;
}
/**

9 4
1 2
2 3
3 4
4 5
5 6
6 7
7 8
8 9
1 1 1 1 1
1 1 1 1

15 4
1 2 2 3 3 4 4 5
5 6 6 7 7 8 8 9
9 10 10 11 11 12
12 13 13 14 14 15
1 1 1 1 1
1 1 1 1 1
1 1 1 1 1


*/

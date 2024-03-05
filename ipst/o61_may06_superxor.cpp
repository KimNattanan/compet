#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll=long long;
#define eb emplace_back

vector<pair<int,ll>> adj[100005];
ll qx[100005];
bitset<100005> vis;
vector<ll> cycle;
ll M[65];
void dfs(int u){
    vis[u]=1;
    for(auto &[v,w]:adj[u]){
        if(qx[v]==-1){
            qx[v]=qx[u]^w;
            dfs(v);
        }
        else if(vis[v]) cycle.eb(qx[v]^qx[u]^w);
    }
    vis[u]=0;
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n,m,Q; cin>>n>>m>>Q;
    for(int i=0;i<m;++i){
        int u,v; cin>>u>>v;
        ll w; cin>>w;
        adj[u].eb(v,w),adj[v].eb(u,w);
    }
    for(int i=2;i<=n;++i) qx[i]=-1;
    dfs(1);
    for(auto &e:cycle){
        for(ll i=62,j=1LL<<62;i>=0;--i,j>>=1){
            if(~e&j) continue;
            if(!M[i]){
                M[i]=e;
                break;
            }
            e^=M[i];
        }
    }
    while(Q--){
        int u,v; cin>>u>>v;
        ll ans=qx[u]^qx[v];
        for(ll i=62,j=1LL<<62;i>=0;--i,j>>=1){
            if(ans&j) continue;
            ans^=M[i];
        }
        cout<<ans<<endl;
    }

    return 0;
}

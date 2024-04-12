#include<bits/stdc++.h>
#include "islandparty.h"
using namespace std;
using ll=long long;
#define eb emplace_back
#define f first
#define s second

int n,sz[100005],p[100005],lv[100005];
ll a[100005],qx[100005][20];
vector<int> adj[100005],nds[100005];
bitset<100005> vis;
vector<pair<ll,ll>> qx2[100005];

void dfs_sz(int u,int p){
    sz[u]=1;
    for(auto &v:adj[u]){
        if(v==p||vis[v]) continue;
        dfs_sz(v,u);
        sz[u]+=sz[v];
    }
}
int centroid(int u,int p,int n){
    for(auto &v:adj[u]){
        if(v!=p&&!vis[v]&&sz[v]>n) return centroid(v,u,n);
    }
    return u;
}
void dfs1(int u,int p,int id,ll val,vector<int> &nds){
    nds.eb(u);
    qx[u][id]=val;
    for(auto &v:adj[u]){
        if(v!=p&&!vis[v]) dfs1(v,u,id,val^a[v],nds);
    }
}
void decomp(int u,int p){
    dfs_sz(u,u);
    int c=centroid(u,u,sz[u]>>1);
    ::p[c]=p;
    lv[c]=lv[p]+1;
    vis[c]=1;

    nds[c].eb(0);
    dfs1(c,c,lv[c],a[c],nds[c]);
    sort(nds[c].begin(),nds[c].end());
    qx2[c].eb(0,0);
    for(int i=1;i<nds[c].size();++i) qx2[c].eb(qx[nds[c][i]][lv[p]]^qx2[c][i-1].f,qx[nds[c][i]][lv[c]]^qx2[c][i-1].s);

    for(auto &v:adj[c]){
        if(!vis[v]) decomp(v,c);
    }
}

void init(int N, int T, std::vector<long long> A, std::vector<int> U, std::vector<int> V) {
    n=N;
    for(int i=0;i<n-1;++i) adj[U[i]+1].eb(V[i]+1), adj[V[i]+1].eb(U[i]+1);
    for(int i=0;i<N;++i) a[i+1]=A[i];
    decomp(1,0);
}

pair<ll,int> play(int X0,int X,int L,int R){
    if(X==0) return{0,0};
    int l=lower_bound(nds[X].begin(),nds[X].end(),L)-nds[X].begin()-1;
    int r=upper_bound(nds[X].begin(),nds[X].end(),R)-nds[X].begin()-1;
    auto [ret,n1]=play(X0,p[X],L,R);
    int n2=r-l;
    n1-=n2;
    if(n1&1) ret^=qx[X0][lv[X]-1]^a[p[X]];
    ret^=qx2[X][r].f^qx2[X][r].s^qx2[X][l].f^qx2[X][l].s;
    return {ret,n2};
}
long long find_drunkenness(int L, int R, int X) {
    ++L,++R,++X;
    return play(X,X,L,R).f;
}

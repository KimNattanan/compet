#include "snow.h"
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define ll long long
#define pii pair<int,int>
#define f first
#define s second
#define pb push_back

vector<bool> temp;
int N,M;

vector<pii> adj[100005],vec;
bool vis[100005];

void dfs(int u){
    vis[u]=1;
    for(auto &vi:adj[u]){
        if(!vis[vi.f]) vec.pb(vi),dfs(vi.f);
    }
}

int play(int u){
    memset(vis,0,sizeof vis);
    vec.clear();
    dfs(u);
    int l=0,r=N-2;
    while(l<r){
        int mid=l+(r-l>>1);
        for(int i=0;i<M;++i) temp[i]=0;
        for(int i=0;i<=mid;++i) temp[vec[i].s]=1;
        if(road_salt(temp)) r=mid;
        else l=mid+1;
    }
    return vec[l].f;
}

vector<int> find_pair(int N, int M, vector<int> U, vector<int> V){
    ::N=N,::M=M;
    temp.resize(M);
    for(int i=0;i<N;++i) adj[i].clear();
    for(int i=0;i<M;++i){
        adj[U[i]].pb({V[i],i});
        adj[V[i]].pb({U[i],i});
    }
    int a=play(0),b=play(a);
    return {a,b};
}

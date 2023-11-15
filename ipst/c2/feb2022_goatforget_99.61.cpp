#include "goatforget.h"
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using pii=pair<int,int>;
#define f first
#define s second
#define eb emplace_back

// int talk_tae(int x);

mt19937 rng(time(0));

int N,M,mn0,mx0;
bool vis[105];
vector<int> adj[105];
set<pii> ss;
int dp[105][105];

void add(int u,int v){
    if(u>v) swap(u,v);
    if(ss.count(pii(u,v))) return;
    ss.emplace(u,v);
    adj[u].eb(v),adj[v].eb(u);
}

int talk(int u,int v){
    if(dp[u][v]!=-1) return dp[u][v];
    int x=talk_tae(v);
    add(u,x);
    if(ss.size()==M) return x;
    talk_tae(u);
    for(int i=min(x,v);i<=max(x,v);++i) dp[u][i]=x;
    dp[x][u]=u;
    return x;
}

void play(int u,int l,int r){
    if(ss.size()==M) return;
    while(l<r&&vis[l+1]) ++l;
    while(l<r&&vis[r-1]) --r;
    if(r-l<=1) return;
    int mid=l+(r-l+1>>1);

    int v=talk(u,mid);
    if(ss.size()==M) return;
    if(v<=l||v>=r) return;

    if(v<mid){
        play(u,l,v),play(u,mid+mid-v-1,r);
    }
    else{
        play(u,v,r),play(u,l,mid-(v-mid));
    }
}

void dfs(int u){
    vis[u]=1;
    while(vis[mn0]) ++mn0;
    while(vis[mx0]) --mx0;
    if(ss.size()==M) return;

    int mn=N,mx=-1;
    vector<int> vec;
    for(auto &v:adj[u]){
        mn=min(mn,v),mx=max(mx,v);
        if(v>=mn0&&v<=mx0) vec.eb(v);
    }
    if(mn<mn0) mn=mn0-1;
    else{
        mn=talk(u,mn0);
        if(ss.size()==M) return;
        mn=max(mn,mn0);
    }
    if(mx>mx0) mx=mx0+1;
    else{
        mx=talk(u,mx0);
        if(ss.size()==M) return;
        mx=min(mx,mx0);
    }

    while(mn<mx&&vis[mn+1]) ++mn;
    while(mn<mx&&vis[mx-1]) --mx;
    play(u,mn,mx);
    if(ss.size()==M) return;

    // shuffle(adj[u].begin(),adj[u].end(),rng);
    for(auto &v:adj[u]){
        if(!vis[v]){
            talk_tae(v),dfs(v);
            if(ss.size()==M) return;
            talk_tae(u);
        }
    }
}

vector<vector<int>> recover_map(int N, int M, int Q){
    ::N=N,::M=M;
    for(int i=0;i<N;++i){
        for(int j=0;j<N;++j) dp[i][j]=-1;
    }
    mn0=0,mx0=N-1;
    dfs(0);
    vector<vector<int>> ans;
    for(auto &e:ss){
        ans.push_back({e.f,e.s});
    }
    return ans;
}

/*
4 3 500000
3 0
0 1
1 2
*/

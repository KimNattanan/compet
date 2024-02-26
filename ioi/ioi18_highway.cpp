#include "highway.h"
#include<bits/stdc++.h>
using namespace std;
#define eb emplace_back
using ll=long long;
using pii=pair<int,int>;
#define f first
#define s second
 
int n,m;
pii edge[130005];
vector<pii> graph[90005];
vector<int> tmp,ans;
ll mn_ask,dist;
bitset<90005> vis;
int tour[90005],parent[90005];
 
int solve1(int U){
    int id=0;
    queue<int> q;
    q.emplace(U);
    vis=0;
    vis[U]=1;
    tour[U]=0;
    while(q.size()){
        int u=q.front(); q.pop();
        for(auto &[v,i]:graph[u]){
            if(vis[v]) continue;
            vis[v]=1;
            q.emplace(v);
            tour[v]=++id;
        }
    }
    int l=dist,r=id;
    while(l<r){
        int mid=l+r>>1;
        for(int i=0;i<m;++i){
            auto &[u,v]=edge[i];
            if(tour[u]<=mid&&tour[v]<=mid) tmp[i]=0;
            else tmp[i]=1;
        }
        if(ask(tmp)==mn_ask) r=mid;
        else l=mid+1;
    }
    for(int i=0;i<n;++i){
        if(tour[i]==l){
            ans.eb(i);
            return i;
        }
    }
}
int solve2(int U){
    int id=0;
    queue<int> q;
    q.emplace(U);
    vis=0;
    vis[U]=1;
    tour[U]=0;
    parent[U]=U;
    while(q.size()){
        int u=q.front(); q.pop();
        for(auto &[v,i]:graph[u]){
            if(vis[v]) continue;
            vis[v]=1;
            q.emplace(v);
            tour[v]=++id;
            parent[v]=u;
        }
    }
    int l=dist,r=id;
    while(l<r){
        int mid=l+r>>1;
        for(int i=0;i<m;++i){
            auto &[u,v]=edge[i];
            if(tour[u]<=mid&&tour[v]<=mid) tmp[i]=0;
            else tmp[i]=1;
        }
        if(ask(tmp)==mn_ask) r=mid;
        else l=mid+1;
    }
    int x;
    for(int i=0;i<n;++i){
        graph[i].clear();
        if(tour[i]==l) ans.eb(i),x=i;
    }
    while(parent[x]!=U){
        vis[x]=0;
        x=parent[x];
    }
    vis[x]=0;
    int i0;
    for(int i=0;i<m;++i){
        auto &[u,v]=edge[i];
        if(tour[u]<=l&&tour[v]<=l && vis[u]==vis[v]) graph[u].eb(v,i),graph[v].eb(u,i);
        if(u==x&&v==U||u==U&&v==x) i0=i;
    }
    graph[x].eb(U,i0);
    return ans.back();
}
void solve3(int U){
    queue<pii> q;
    q.emplace(U,0);
    vis=0;
    vis[U]=1;
    vector<int> tmp2(tmp.size(),1);
    vector<pii> vec;
    while(q.size()){
        auto [u,d]=q.front(); q.pop();
        for(auto &[v,id]:graph[u]){
            if(vis[v]) continue;
            if(d+1<dist) q.emplace(v,d+1), tmp2[id]=0;
            else if(d+1==dist) vec.eb(v,id);
            vis[v]=1;
        }
    }
    int l=0,r=vec.size();
    while(l<r){
        int mid=l+r>>1;
        tmp=tmp2;
        for(int i=0;i<=mid;++i) tmp[vec[i].s]=0;
        if(ask(tmp)==mn_ask) r=mid;
        else l=mid+1;
    }
    ans.eb(vec[l].f);
}
 
void find_pair(int N, std::vector<int> U, std::vector<int> V, int A, int B) {
    n=N,m=U.size();
    for(int i=0;i<m;++i){
        edge[i]={U[i],V[i]};
        graph[U[i]].eb(V[i],i);
        graph[V[i]].eb(U[i],i);
    }
    tmp.assign(m,0);
    mn_ask=ask(tmp), dist=mn_ask/A;
    solve3(solve2(solve1(0)));
    answer(ans[1],ans[2]);
}
/*
15 15  99 100  9 10
0 1
1 3
3 5
5 7
7 9
9 11
11 13
13 14
14 12
12 10
10 8
8 6
6 4
4 2
2 0
*/

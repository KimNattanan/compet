#include "medal.h"
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using pii=pair<int,int>;
#define f first
#define s second
#define eb emplace_back

vector<int> adj[100005];
vector<ll> W;
ll dp[100005][25];

int heavy[100005],p0[100005],head[100005],tour[100005],id0;
ll qs[100005];

struct segment{
    vector<segment> child;
    int l,r,mid;
    vector<ll> mx;
    segment(int l_=0,int r_=0):l(l_),r(r_),mid(l+(r-l>>1)),mx(vector<ll>(11)){}
    void build(){
        if(l==r){
            for(int i=0;i<=10;++i) mx[i]=dp[l][i<<1];
            return;
        }
        child.eb(l,mid),child.eb(mid+1,r);
        child[0].build(),child[1].build();
        for(int i=0;i<=10;++i) mx[i]=max(child[0].mx[i],child[1].mx[i]);
    }
    ll qr(int l0,int r0,int i){
        if(l0<=l&&r<=r0) return mx[i];
        if(l>r0||r<l0) return 0;
        return max(child[0].qr(l0,r0,i),child[1].qr(l0,r0,i));
    }
}t;

int dfs(int u,int p){
    p0[u]=p;
    qs[u]=qs[p]+W[u];
    int sz=1;
    pii best(0,-1);
    for(auto &v:adj[u]){
        if(v!=p){
            int x=dfs(v,u);
            best=max(best,pii(x,v));
            sz+=x;
        }
    }
    heavy[u]=best.s;
    return sz;
}
void decomp(int u,int p){
    tour[u]=++id0;
    head[u]=p;
    if(heavy[u]!=-1) decomp(heavy[u],p);
    for(auto &v:adj[u]){
        if(v!=p0[u]&&v!=heavy[u]) decomp(v,v);
    }
}
ll qr(int u,int v,int x){
    ll mx=0,ans=qs[u]+qs[v];
    while(head[u]!=head[v]){
        if(tour[u]>tour[v]) swap(u,v);
        if(x) mx=max(mx,t.qr(tour[head[v]],tour[v],x));
        v=p0[head[v]];
    }
    if(tour[u]>tour[v]) swap(u,v);
    if(x) mx=max(mx,t.qr(tour[u],tour[v],x));
    ans+=W[u]-(qs[u]<<1);
    return ans+mx;
}

void initialize(int N, int Q, std::vector<int> W_, std::vector<std::pair<int,int> > R)
{
    W=vector<ll>(W_.size()+5);
    for(int i=1;i<=N;++i) W[i]=W_[i-1];
    for(auto &e:R) adj[e.f+1].eb(e.s+1),adj[e.s+1].eb(e.f+1);
    dfs(1,1);
    decomp(1,1);
    for(int i=2;i<=20;i+=2){
        for(int u=1;u<=N;++u){
            for(auto &v:adj[u]) dp[tour[u]][i]=max(dp[tour[u]][i],W[u]+W[v]+dp[tour[v]][i-2]);
        }
    }
    t=segment(1,id0);
    t.build();

    return;
}
long long query(int A, int B, int X)
{
    ++A,++B;
    return qr(A,B,X>>1);
}

/*

8 2
1 5 1 2 1 11 1 1
0 2 2 1 2 3 3 4 3 7 5 4 5 6
0 7 5
6 2 2

*/
